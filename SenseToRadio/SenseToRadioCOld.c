
#include "Timer.h"
#include "SenseToRadio.h"

/**
 * Implementation of the RadioSenseToLeds application.  RadioSenseToLeds samples
 * a platform's default sensor at 4Hz and broadcasts this value in an AM packet.
 * A RadioSenseToLeds node that hears a broadcast displays the bottom three bits
 * of the value it has received. This application is a useful test to show that
 * basic AM communication, timers, and the default sensor work.
 *
 * @author Philip Levis
 * @date   June 6 2005
 */

module SenseToRadioC @safe(){
  uses {
    interface Leds;
    interface Boot;
    interface Receive;
    interface AMSend;
    interface Timer<TMilli> as MilliTimer;
    interface Packet;
    interface SplitControl as RadioControl;

    interface Read<uint16_t> as Temperature;
    interface Read<uint16_t> as Humidity;
    interface Read<uint16_t> as PhotoLight;
    interface Read<uint16_t> as FullLight;
  }
}
implementation {

  message_t packet; //tajā dzīvos saņemtie dati
  message_t report_packet; //tajā dzīvos nosūtāmie dati
  bool locked = FALSE; //vai šobrīd kaut ko sūta vai nodarbojas pats ar sevi
  // no sensoru ziņas izvilktie mainīgie
  uint16_t counter_mote;
  uint16_t moteId_mote;
  uint16_t sensorId_mote;
  uint16_t period_mote;
  uint16_t avg_mote;
  sensor_report_msg_t* send_message;
  sensor_request_msg_t* rsm;

  // lokālie mainīgie
  uint16_t read_count = 0;
  uint16_t read_value = 0;
  uint16_t accumulated_reading = 0;
  uint16_t average_value = 0;
  uint16_t counter = 0;


  enum {
    NETWORK_ID = 24,
    MOTE_ID_START = NETWORK_ID*100,
    MOTE_ID = MOTE_ID_START + 1
  };

  // tad kad, esam iebūtojušies, sākam radio
  event void Boot.booted() {
    call RadioControl.start();
  }

  event void RadioControl.startDone(error_t err) {
    if (err == SUCCESS) {

    }
  }
  event void RadioControl.stopDone(error_t err) { call Leds.led1On();}

  void read_sensors() {
    //Nolasam sensorus atkarībā no saņemtā sensora ID
    call Leds.led0Toggle();
    switch(sensorId_mote) {
      case 1:
        call FullLight.read();
        break;
      case 2:
        call PhotoLight.read();
        break;
      case 3:
        call Temperature.read();
        break;
      case 4:
        call Humidity.read();
        break;
    }
  }

  void check_counters() {
    call Leds.led0Toggle();
    // ja nolasīts pietiekami daudz skaitu reižu, sūtam atpakaļ
    if(read_count>= avg_mote){
      average_value = accumulated_reading/read_count;

     // pagaidām izņemam locked flagus, lai pārbaudītu vērtības
     if (locked) { return; }
     else {
        send_message = (sensor_report_msg_t*)call Packet.getPayload(&report_packet, sizeof(sensor_report_msg_t));
        if (send_message == NULL) {
          return;
        }
        send_message->counter = counter;
        send_message->moteId = moteId_mote;
        send_message->sensorId = sensorId_mote;
        send_message->value = average_value;
        if (call AMSend.send(AM_BROADCAST_ADDR, &report_packet, sizeof(sensor_report_msg_t)) == SUCCESS) {
          call Leds.led0Off();
          locked = TRUE;
        }
      }

    }
    else
      //izsaucam taimeri, lai lasītu nākamās reizes
      call MilliTimer.startOneShot(period_mote);
  }

  event void MilliTimer.fired() {
    call Leds.led0Toggle();
    read_sensors();
  }

  // Saņemam ziņojumu un ieliekam visu informāciju lokālajos mainīgajos
  event message_t* Receive.receive(message_t* bufPtr, void* payload, uint8_t len) {
    call Leds.led2Off();
    call Leds.led1Off();
    call Leds.led0Off();
    rsm = (sensor_request_msg_t*)payload;
    if (len != sizeof(sensor_request_msg_t)) {return bufPtr;}
    else {
      // ielasam no ziņas visu mainīgajos
      counter_mote = rsm->counter;
  	  moteId_mote = rsm->moteId;
  	  sensorId_mote = rsm->sensorId;
  	  period_mote = rsm->period;
      period_mote = period_mote*1000;
  	  avg_mote = rsm->avg;

      if(moteId_mote == MOTE_ID) {
        read_sensors();
      }
	  }
	  return 0;
  }

  // SENSORU LASĪŠANA
  // Kad tiek pabeigts lasīt pilnas gaismas sensoru
  event void FullLight.readDone(error_t result, uint16_t data) {
        call Leds.led1Toggle();
    if (result != SUCCESS) {
      data = 0xffff;

      // report_problem();
    }
    else {
      accumulated_reading = accumulated_reading+data;
      read_count++;
      check_counters();
    }
  }

  event void PhotoLight.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    if (result != SUCCESS) {
      data = 0xffff;
      // report_problem();
    }
    else {
      accumulated_reading = accumulated_reading+data;
      read_count++;
    }
    check_counters();
  }

  event void Temperature.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    if (result != SUCCESS) {
      data = 0xffff;
      // report_problem();
    }
    else {
      accumulated_reading = accumulated_reading+data;
      read_count++;
    }
    check_counters();
  }

  event void Humidity.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    if (result != SUCCESS) {
      data = 0xffff;
      // report_problem();
    }
    else {
      accumulated_reading = accumulated_reading+data;
      read_count++;
    }
    check_counters();
  }

  // kad nosūtīta paka, notīram mainīgos.
  event void AMSend.sendDone(message_t* bufPtr, error_t error) {
    if (&report_packet == bufPtr) {
      locked = FALSE;
      counter++;
      call Leds.led2On();
      call Leds.led0Off();
      call Leds.led1Off();
      read_count = 0;
      read_value = 0;
      accumulated_reading = 0;
      average_value = 0;
    }
  }

}
