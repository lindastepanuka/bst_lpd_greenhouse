/**
 * Application to test that the TinyOS java toolchain can communicate
 * with motes over the serial port.
 *
 *  @author Gilman Tolle
 *  @author Philip Levis
 *
 *  @date   Aug 12 2005
 *
 **/

#include "Timer.h"
#include "TestSerial.h"

module TestSerialC {
  uses {
    interface SplitControl as Control;
    interface SplitControl as RadioControl;

    interface Leds;
    interface Boot;

    interface Receive as SerialReceive;
    interface AMSend as SerialSend;

    interface Receive as RadioReceive;
    interface AMSend as RadioSend;    

    interface Packet;
    interface Packet as RadioPacket;
  }
}
implementation {

  message_t packet;
  message_t packet_radio;

  sensor_request_msg_t* send_message;
  sensor_report_msg_t* radio_received_message;
  sensor_report_msg_t* srpm;
  sensor_request_msg_t* srm;
  
  bool locked = FALSE;
  bool locked_radio = FALSE;
  uint16_t counter = 0;
  uint16_t counter_radio = 0;
  uint16_t mote_id;

  enum {
    NETWORK_ID = 24,

    // Pieņemsim, ka tīklā nebūs vairāk par 100 motēm
    MOTE_ID_START = NETWORK_ID*100,
    MOTE_ID_END = MOTE_ID_START + 99
  };


  event void Boot.booted() {
    call Control.start();
    call RadioControl.start();
    //call Leds.led1On();
  }

  // Saņemam sensor request ziņojumu pa seriālo portu un pārsūtam pa radio
  event message_t* SerialReceive.receive(message_t* bufPtr, void* payload, uint8_t len) {
    srm = (sensor_request_msg_t*)payload;

    call Leds.led0On();
    if (len != sizeof(sensor_request_msg_t)) {return bufPtr;}
    else {
      if (locked_radio) { return bufPtr;}
      else {
        call Leds.led1On();      
        send_message = (sensor_request_msg_t*)call RadioPacket.getPayload(&packet_radio, sizeof(sensor_request_msg_t));
        if (send_message == NULL) {
          return bufPtr;
        }
        send_message->counter  = counter_radio;
        send_message->moteId   = srm->moteId;
        send_message->sensorId = srm->sensorId;
        send_message->period   = srm->period;
        send_message->avg      = srm->avg;
        

        if (call RadioSend.send(AM_BROADCAST_ADDR, &packet_radio, sizeof(sensor_request_msg_t)) == SUCCESS) {
          //call Leds.led1On();
          locked_radio = TRUE;
          call Leds.led1Off(); 
        }
        return bufPtr;
      }
    }
  }

  event void RadioSend.sendDone(message_t* bufPtr, error_t error) {
    if (&packet_radio == bufPtr) {
      locked_radio = FALSE;
      counter_radio++;
      call Leds.led0Off();
    }
  }

  // Saņemam ziņojumu pa radio, uzbūvējam ziņojumu un nosūtam uz seriālo portu
  event message_t* RadioReceive.receive(message_t* bufPtr, void* payload, uint8_t len) {
    call Leds.led1On();
    radio_received_message = (sensor_report_msg_t*)payload;
    mote_id = radio_received_message->moteId;
    if (len == sizeof(sensor_report_msg_t)) {
      if (mote_id > MOTE_ID_START && mote_id < MOTE_ID_END) {
        if(locked) {
        
          return bufPtr;
        }
        else {
          srpm = (sensor_report_msg_t*)call Packet.getPayload(&packet, sizeof(sensor_report_msg_t));
          if (srpm == NULL) {return bufPtr;}
          call Leds.led1Off();
          srpm->counter  = radio_received_message -> counter;
          srpm->moteId   = radio_received_message -> moteId;
          srpm->sensorId = radio_received_message -> sensorId;
          srpm->value    = radio_received_message -> value;
          srpm->counter  = radio_received_message -> counter;
          if (call SerialSend.send(AM_BROADCAST_ADDR, &packet, sizeof(sensor_report_msg_t)) == SUCCESS) {
            locked = TRUE;
            call Leds.led2On();
          }
        }
      }
    }
    return 0;
  }

  event void SerialSend.sendDone(message_t* bufPtr, error_t error) {
    if (&packet == bufPtr) {
      locked = FALSE;
      counter++;
      //call Leds.led2Off();
    }
  }


  event void Control.startDone(error_t err) {
    if (err == SUCCESS) {
      // call MilliTimer.startPeriodic(1000);
    }
  }
  event void Control.stopDone(error_t err) {}
  
  
  event void RadioControl.startDone(error_t err) {
    if (err == SUCCESS) {
      // call MilliTimer.startPeriodic(1000);
    }
  }
  event void RadioControl.stopDone(error_t err) {}
}




