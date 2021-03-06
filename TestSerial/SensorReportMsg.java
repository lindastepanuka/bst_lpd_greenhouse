/**
 * This class is automatically generated by mig. DO NOT EDIT THIS FILE.
 * This class implements a Java interface to the 'SensorReportMsg'
 * message type.
 */

public class SensorReportMsg extends net.tinyos.message.Message {

    /** The default size of this message type in bytes. */
    public static final int DEFAULT_MESSAGE_SIZE = 12;

    /** The Active Message type associated with this message. */
    public static final int AM_TYPE = 2;

    /** Create a new SensorReportMsg of size 12. */
    public SensorReportMsg() {
        super(DEFAULT_MESSAGE_SIZE);
        amTypeSet(AM_TYPE);
    }

    /** Create a new SensorReportMsg of the given data_length. */
    public SensorReportMsg(int data_length) {
        super(data_length);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg with the given data_length
     * and base offset.
     */
    public SensorReportMsg(int data_length, int base_offset) {
        super(data_length, base_offset);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg using the given byte array
     * as backing store.
     */
    public SensorReportMsg(byte[] data) {
        super(data);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg using the given byte array
     * as backing store, with the given base offset.
     */
    public SensorReportMsg(byte[] data, int base_offset) {
        super(data, base_offset);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg using the given byte array
     * as backing store, with the given base offset and data length.
     */
    public SensorReportMsg(byte[] data, int base_offset, int data_length) {
        super(data, base_offset, data_length);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg embedded in the given message
     * at the given base offset.
     */
    public SensorReportMsg(net.tinyos.message.Message msg, int base_offset) {
        super(msg, base_offset, DEFAULT_MESSAGE_SIZE);
        amTypeSet(AM_TYPE);
    }

    /**
     * Create a new SensorReportMsg embedded in the given message
     * at the given base offset and length.
     */
    public SensorReportMsg(net.tinyos.message.Message msg, int base_offset, int data_length) {
        super(msg, base_offset, data_length);
        amTypeSet(AM_TYPE);
    }

    /**
    /* Return a String representation of this message. Includes the
     * message type name and the non-indexed field values.
     */
    public String toString() {
      String s = "Message <SensorReportMsg> \n";
      try {
        s += "  [counter=0x"+Long.toHexString(get_counter())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [moteId=0x"+Long.toHexString(get_moteId())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [temperatureValue=0x"+Long.toHexString(get_temperatureValue())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [humidityValue=0x"+Long.toHexString(get_humidityValue())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [photoLightValue=0x"+Long.toHexString(get_photoLightValue())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      try {
        s += "  [fullLightValue=0x"+Long.toHexString(get_fullLightValue())+"]\n";
      } catch (ArrayIndexOutOfBoundsException aioobe) { /* Skip field */ }
      return s;
    }

    // Message-type-specific access methods appear below.

    /////////////////////////////////////////////////////////
    // Accessor methods for field: counter
    //   Field type: int, unsigned
    //   Offset (bits): 0
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'counter' is signed (false).
     */
    public static boolean isSigned_counter() {
        return false;
    }

    /**
     * Return whether the field 'counter' is an array (false).
     */
    public static boolean isArray_counter() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'counter'
     */
    public static int offset_counter() {
        return (0 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'counter'
     */
    public static int offsetBits_counter() {
        return 0;
    }

    /**
     * Return the value (as a int) of the field 'counter'
     */
    public int get_counter() {
        return (int)getUIntBEElement(offsetBits_counter(), 16);
    }

    /**
     * Set the value of the field 'counter'
     */
    public void set_counter(int value) {
        setUIntBEElement(offsetBits_counter(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'counter'
     */
    public static int size_counter() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'counter'
     */
    public static int sizeBits_counter() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: moteId
    //   Field type: int, unsigned
    //   Offset (bits): 16
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'moteId' is signed (false).
     */
    public static boolean isSigned_moteId() {
        return false;
    }

    /**
     * Return whether the field 'moteId' is an array (false).
     */
    public static boolean isArray_moteId() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'moteId'
     */
    public static int offset_moteId() {
        return (16 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'moteId'
     */
    public static int offsetBits_moteId() {
        return 16;
    }

    /**
     * Return the value (as a int) of the field 'moteId'
     */
    public int get_moteId() {
        return (int)getUIntBEElement(offsetBits_moteId(), 16);
    }

    /**
     * Set the value of the field 'moteId'
     */
    public void set_moteId(int value) {
        setUIntBEElement(offsetBits_moteId(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'moteId'
     */
    public static int size_moteId() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'moteId'
     */
    public static int sizeBits_moteId() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: temperatureValue
    //   Field type: int, unsigned
    //   Offset (bits): 32
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'temperatureValue' is signed (false).
     */
    public static boolean isSigned_temperatureValue() {
        return false;
    }

    /**
     * Return whether the field 'temperatureValue' is an array (false).
     */
    public static boolean isArray_temperatureValue() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'temperatureValue'
     */
    public static int offset_temperatureValue() {
        return (32 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'temperatureValue'
     */
    public static int offsetBits_temperatureValue() {
        return 32;
    }

    /**
     * Return the value (as a int) of the field 'temperatureValue'
     */
    public int get_temperatureValue() {
        return (int)getUIntBEElement(offsetBits_temperatureValue(), 16);
    }

    /**
     * Set the value of the field 'temperatureValue'
     */
    public void set_temperatureValue(int value) {
        setUIntBEElement(offsetBits_temperatureValue(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'temperatureValue'
     */
    public static int size_temperatureValue() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'temperatureValue'
     */
    public static int sizeBits_temperatureValue() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: humidityValue
    //   Field type: int, unsigned
    //   Offset (bits): 48
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'humidityValue' is signed (false).
     */
    public static boolean isSigned_humidityValue() {
        return false;
    }

    /**
     * Return whether the field 'humidityValue' is an array (false).
     */
    public static boolean isArray_humidityValue() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'humidityValue'
     */
    public static int offset_humidityValue() {
        return (48 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'humidityValue'
     */
    public static int offsetBits_humidityValue() {
        return 48;
    }

    /**
     * Return the value (as a int) of the field 'humidityValue'
     */
    public int get_humidityValue() {
        return (int)getUIntBEElement(offsetBits_humidityValue(), 16);
    }

    /**
     * Set the value of the field 'humidityValue'
     */
    public void set_humidityValue(int value) {
        setUIntBEElement(offsetBits_humidityValue(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'humidityValue'
     */
    public static int size_humidityValue() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'humidityValue'
     */
    public static int sizeBits_humidityValue() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: photoLightValue
    //   Field type: int, unsigned
    //   Offset (bits): 64
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'photoLightValue' is signed (false).
     */
    public static boolean isSigned_photoLightValue() {
        return false;
    }

    /**
     * Return whether the field 'photoLightValue' is an array (false).
     */
    public static boolean isArray_photoLightValue() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'photoLightValue'
     */
    public static int offset_photoLightValue() {
        return (64 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'photoLightValue'
     */
    public static int offsetBits_photoLightValue() {
        return 64;
    }

    /**
     * Return the value (as a int) of the field 'photoLightValue'
     */
    public int get_photoLightValue() {
        return (int)getUIntBEElement(offsetBits_photoLightValue(), 16);
    }

    /**
     * Set the value of the field 'photoLightValue'
     */
    public void set_photoLightValue(int value) {
        setUIntBEElement(offsetBits_photoLightValue(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'photoLightValue'
     */
    public static int size_photoLightValue() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'photoLightValue'
     */
    public static int sizeBits_photoLightValue() {
        return 16;
    }

    /////////////////////////////////////////////////////////
    // Accessor methods for field: fullLightValue
    //   Field type: int, unsigned
    //   Offset (bits): 80
    //   Size (bits): 16
    /////////////////////////////////////////////////////////

    /**
     * Return whether the field 'fullLightValue' is signed (false).
     */
    public static boolean isSigned_fullLightValue() {
        return false;
    }

    /**
     * Return whether the field 'fullLightValue' is an array (false).
     */
    public static boolean isArray_fullLightValue() {
        return false;
    }

    /**
     * Return the offset (in bytes) of the field 'fullLightValue'
     */
    public static int offset_fullLightValue() {
        return (80 / 8);
    }

    /**
     * Return the offset (in bits) of the field 'fullLightValue'
     */
    public static int offsetBits_fullLightValue() {
        return 80;
    }

    /**
     * Return the value (as a int) of the field 'fullLightValue'
     */
    public int get_fullLightValue() {
        return (int)getUIntBEElement(offsetBits_fullLightValue(), 16);
    }

    /**
     * Set the value of the field 'fullLightValue'
     */
    public void set_fullLightValue(int value) {
        setUIntBEElement(offsetBits_fullLightValue(), 16, value);
    }

    /**
     * Return the size, in bytes, of the field 'fullLightValue'
     */
    public static int size_fullLightValue() {
        return (16 / 8);
    }

    /**
     * Return the size, in bits, of the field 'fullLightValue'
     */
    public static int sizeBits_fullLightValue() {
        return 16;
    }

}
