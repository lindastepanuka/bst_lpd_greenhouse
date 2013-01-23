/**
 * Application to test that the TinyOS java toolchain can communicate
 * with motes over the serial port. The application sends packets to
 * the serial port at 1Hz: the packet contains an incrementing
 * counter. When the application receives a counter packet, it
 * displays the bottom three bits on its LEDs. This application is
 * very similar to RadioCountToLeds, except that it operates over the
 * serial port. There is Java application for testing the mote
 * application: run TestSerial to print out the received packets and
 * send packets to the mote.
 *
 *  @author Gilman Tolle
 *  @author Philip Levis
 *
 *  @date   Aug 12 2005
 *
 **/

#include "TestSerial.h"

configuration TestSerialAppC {}
implementation {
  components TestSerialC as App, LedsC, MainC;
  
  // Radio sender and receiver
  components new AMSenderC(AM_SENSOR_REQUEST_MSG) as RadioSender;
  components new AMReceiverC(AM_SENSOR_REPORT_MSG) as RadioReceiver;
  components ActiveMessageC;

  // Serial active message, which provides sender and receiver interfaces
  components SerialActiveMessageC as AM;

  // Serial interfaces
  App.SerialReceive -> AM.Receive[AM_SENSOR_REQUEST_MSG];
  App.SerialSend -> AM.AMSend[AM_SENSOR_REPORT_MSG];
  App.Control -> AM;

  App.Boot -> MainC.Boot;
  App.Leds -> LedsC;
  App.Packet -> AM;

  //Radio interfaces
  App.RadioReceive -> RadioReceiver;
  App.RadioSend   -> RadioSender;
  App.RadioControl  -> ActiveMessageC;
  App.RadioPacket -> ActiveMessageC;
}


