
#include "Timer.h"
#include "SenseToRadio.h"

#define NEW_PRINTF_SEMANTICS
#include "printf.h"

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
  uint16_t accumulated_reading = 0;
  uint16_t counter = 0;


  uint16_t accumulated_temperature = 0;
  uint16_t accumulated_humidity = 0;
  uint16_t accumulated_real_light = 0;
  uint16_t accumulated_photo_light = 0;


  enum {
    NETWORK_ID = 24,
    MOTE_ID_START = NETWORK_ID*100,
    MOTE_ID = MOTE_ID_START + 1
  };

  // tad kad, esam iebūtojušies, sākam radio
  event void Boot.booted() {
    printf("booted up, ready to go!\n");
    printfflush();
    call RadioControl.start();
  }

  event void RadioControl.startDone(error_t err) {
    if (err == SUCCESS) {

    }
  }
  event void RadioControl.stopDone(error_t err) { call Leds.led1On();}

  void read_sensors() {
    //Apskatam, vai aktīvais current_sensor
    if (read_count > avg_mote) {
      current_sensor++;
      if current_sensor != 4
        read_count = 0;
    }
    switch(current_sensor)
    // switch(sensorId_mote) {
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
    printf("[check_counters] entering\n");
    printfflush();
    // ja nolasīts pietiekami daudz skaitu reižu, sūtam atpakaļ
    if(current_sensor<4 && read_count>= avg_mote){
      printf("sūtam ziņas\n");

      if (locked) { return; }
      else {
        send_message = (sensor_report_msg_t*)call Packet.getPayload(&report_packet, sizeof(sensor_report_msg_t));
        if (send_message == NULL) {
          return;
        }
        send_message->counter = counter;
        send_message->moteId = moteId_mote;
        send_message->temperatureValue = accumulated_temperature/read_count;
        send_message->humidityValue = accumulated_humidity/read_count;
        send_message->photoLightValue = accumulated_photo_light/read_count;
        send_message->fullLightValue = accumulated_full_light/read_count;
        if (call AMSend.send(AM_BROADCAST_ADDR, &report_packet, sizeof(sensor_report_msg_t)) == SUCCESS) {
          call Leds.led0Off();
          locked = TRUE;
        }
      }
    }
    else
      // lasam sensorus
      read_sensors();
    printf("[check_counters] exiting\n");
    printfflush();
  }

  event void MilliTimer.fired() {
    // call Leds.led0Toggle();
    // read_sensors();
    printf("[MilliTimer.fired] entering\n");
    printfflush();
    if (period_mote != 0)
      check_counters();
  }

  // Saņemam ziņojumu un ieliekam visu informāciju lokālajos mainīgajos
  event message_t* Receive.receive(message_t* bufPtr, void* payload, uint8_t len) {
    printf("Message received\n");
    printfflush();
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
        call MilliTimer.startOneShot(period_mote);
        read_sensors();
      }
	}
	printf("[Receive] finished\n");
    printfflush();
	return bufPtr;;
  }

  // SENSORU LASĪŠANA
  // Kad tiek pabeigts lasīt pilnas gaismas sensoru
  event void FullLight.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    printf("[readfulllightdone] entering\n");
    if (result != SUCCESS) {
      data = 0xffff;

      // report_problem();
    }
    else {
      accumulated_full_light = accumulated_full_light+data;
      read_count++;
    }
    printf("[readfulllightdone] exiting\n");
    check_counters();
  }

  event void PhotoLight.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    printf("full light read start \n");
    if (result != SUCCESS) {
      data = 0xffff;
      // report_problem();
    }
    else {
      accumulated_photo_light = accumulated_photo_light+data;
      read_count++;
    }
    printf("full light read start \n");
    check_counters();
  }

  event void Temperature.readDone(error_t result, uint16_t data) {
    call Leds.led1Toggle();
    if (result != SUCCESS) {
      data = 0xffff;
      // report_problem();
    }
    else {
      accumulated_temperature = accumulated_temperature+data;
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
      accumulated_humidity = accumulated_humidity+data;
      read_count++;
    }
    check_counters();
  }

  // kad nosūtīta paka, notīram mainīgos.
  event void AMSend.sendDone(message_t* bufPtr, error_t error) {
    printf("packet send done start\n");
    if (&report_packet == bufPtr) {
      printf("yo\n");
      locked = FALSE;
      counter++;
      read_count = 0;
      accumulated_temperature = 0;
      accumulated_humidity = 0;
      accumulated_real_light = 0;
      accumulated_photo_light = 0;
      current_sensor = 1;
      call MilliTimer.startOneShot(period_mote);
    }
    printf("packet send done end\n");
  }

}
