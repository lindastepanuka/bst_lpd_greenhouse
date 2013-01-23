
#include "SenseToRadio.h"

/**
 * Configuration for the RadioSenseToLeds application.  RadioSenseToLeds samples
 * a platform's default sensor at 4Hz and broadcasts this value in an AM packet.
 * A RadioSenseToLeds node that hears a broadcast displays the bottom three bits
 * of the value it has received. This application is a useful test to show that
 * basic AM communication, timers, and the default sensor work.
 *
 * @author Philip Levis
 * @date   June 6 2005
 */

configuration SenseToRadioAppC {}
implementation {
  components PrintfC;
  components SerialStartC;

  components MainC, SenseToRadioC as App, LedsC, new DemoSensorC();
  components ActiveMessageC;
  components new AMSenderC(AM_SENSOR_REPORT_MSG) as Sender;
  components new AMReceiverC(AM_SENSOR_REQUEST_MSG) as Receiver;
  components new TimerMilliC();
  components new SensirionSht11C() as TempAndHumid,
    new HamamatsuS1087ParC() as PhotoPar,
    new HamamatsuS10871TsrC() as PhotoTsr,
    new Msp430InternalVoltageC() as InternalVoltage,
    new Msp430InternalTemperatureC() as InternalTemperature;

  App.Boot -> MainC.Boot;

  App.Temperature -> TempAndHumid.Temperature;
  App.Humidity -> TempAndHumid.Humidity;
  App.PhotoLight -> PhotoPar;
  App.FullLight -> PhotoTsr;

  App.Receive -> Receiver;
  App.AMSend -> Sender;
  App.RadioControl -> ActiveMessageC;
  App.Leds -> LedsC;
  App.MilliTimer -> TimerMilliC;
  App.Packet -> Sender;
}
