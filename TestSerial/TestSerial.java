import java.io.IOException;
import java.io.*;

import net.tinyos.message.*;
import net.tinyos.packet.*;
import net.tinyos.util.*;

public class TestSerial implements MessageListener {

  private MoteIF moteIF;

  private final int MOTEID = 2401;

  static int optimal_photo_light;
  static int optimal_temperature;
  static int optimal_humidity;
  static int optimal_full_light;

  public TestSerial(MoteIF moteIF) {
    this.moteIF = moteIF;
    this.moteIF.registerListener(new SensorReportMsg(), this);
  }

  public void sendPackets() {
    int counter = 0;
    SensorRequestMsg payload = new SensorRequestMsg();
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    String buf;

    try {
      while (true) {
        buf = in.readLine();

        if (buf.replace("\n", "").equalsIgnoreCase("r")) {
            System.out.println("Sending packet " + counter);

            // prepare the messages
            payload.set_counter(counter);
            payload.set_moteId(MOTEID);
            payload.set_avg(8);
            payload.set_period(5);
            System.out.println(payload);
            System.out.println("\n");

            // send the message (broadcast to all)
            moteIF.send(MoteIF.TOS_BCAST_ADDR, payload);
            counter++;
        } else {
            System.out.println("Unknown command: " + buf + "\n");
        }
      }
    }
    catch (IOException exception) {
      System.err.println("Exception thrown when sending packets. Exiting.");
      System.err.println(exception);
    }
  }

  public void messageReceived(int to, Message message) {
    SensorReportMsg msg = (SensorReportMsg)message;
    System.out.println("Received packet sequence number " + msg.get_counter());
    if (msg.get_moteId() > 2400 && msg.get_moteId() < 2499) {
      boolean errors_present = false;
      // test optimal temperature
      if ((msg.get_temperatureValue())-10 > optimal_temperature) {
        System.out.println("Tomatoes are feeling hot.");
        errors_present = true;
      }
      if (msg.get_temperatureValue()+10 < optimal_temperature) {
        System.out.println("Tomatoes are feeling cold.");
        errors_present = true;
      }

      // test optimal humidity
      if (msg.get_humidityValue()-10 > optimal_humidity) {
        System.out.println("Tomatoes are feeling quite moist.");
        errors_present = true;
      }
      if (msg.get_humidityValue()+10 < optimal_humidity) {
        System.out.println("Tomatoes are feeling quite dry.");
        errors_present = true;
      }

      // test optimal full light
      if (msg.get_fullLightValue()-10 > optimal_full_light) {
        System.out.println("Tomatoes are in too much of a full spotlight.");
        errors_present = true;
      }
      if (msg.get_fullLightValue()+10 < optimal_full_light) {
        System.out.println("Tomatoes are in complete darkness.");
        errors_present = true;
      }

      // test optimal photosensitive light
      if (msg.get_photoLightValue()-10 > optimal_photo_light) {
        System.out.println("Tomatoes are getting way too much 'yum' light.");
        errors_present = true;
      }
      if (msg.get_photoLightValue()+10 < optimal_humidity) {
        System.out.println("Tomatoes are hungry.");
        errors_present = true;
      }
    }
  }

  private static void usage() {
    System.err.println("usage: TestSerial [-comm <source>]");
  }

  private static void help() throws Exception {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("The program will print received messages automatically.");
    System.out.println("To send a message, press 'R' followed by Enter.\n");
    System.out.println("Press Enter to start.");
    in.readLine();
  }

  private static void set_variables() throws Exception {
    String buf = "";
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("The program will now ask you to set optimal variable values. If values will not comply to numeric format, default value of 42 will be used.");
    System.out.println("Please enter optimal humidity value followed by Enter:\n");
    buf = in.readLine();
    optimal_humidity = isInteger(buf) ? Integer.parseInt(buf) : 42;
    System.out.println("Please enter optimal temperature value followed by Enter:\n");
    buf = in.readLine();
    optimal_temperature = isInteger(buf) ? Integer.parseInt(buf) : 42;
    System.out.println("Please enter optimal full light value followed by Enter:\n");
    buf = in.readLine();
    optimal_full_light = isInteger(buf) ? Integer.parseInt(buf) : 42;
    System.out.println("Please enter optimal photosynthetic light value followed by Enter:\n");
    buf = in.readLine();
    optimal_photo_light = isInteger(buf) ? Integer.parseInt(buf) : 42;
  }

  public static boolean isInteger(String s) {
      try {
          Integer.parseInt(s);
      } catch(NumberFormatException e) {
          return false;
      }
      // only got here if we didn't return false
      return true;
  }

  public static void main(String[] args) throws Exception {
    String source = null;
    if (args.length == 2) {
      if (!args[0].equals("-comm")) {
        usage();
        System.exit(1);
      }
      source = args[1];
    }
    else if (args.length != 0) {
      usage();
      System.exit(1);
    }

    help();

    PhoenixSource phoenix;

    if (source == null) {
      phoenix = BuildSource.makePhoenix(PrintStreamMessenger.err);
    }
    else {
      phoenix = BuildSource.makePhoenix(source, PrintStreamMessenger.err);
    }

    MoteIF mif = new MoteIF(phoenix);
    TestSerial serial = new TestSerial(mif);


    set_variables();

    serial.sendPackets();
  }


}
