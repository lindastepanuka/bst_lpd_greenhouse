# SensorRequestMsg
# SensorReportMsg
# NetworkScanMsg

COMPONENT=BaseStationP
CFLAGS += -DCC2420_NO_ACKNOWLEDGEMENTS
CFLAGS += -DCC2420_NO_ADDRESS_RECOGNITION
CFLAGS += -DTASKLET_IS_TASK


BUILD_EXTRA_DEPS = SensorRequestMsg.py SensorRequestMsg.class SensorReportMsg.py SensorReportMsg.class NetworkScanMsg.py NetworkScanMsg.class TestSerial.class

CLEAN_EXTRA = SensorRequestMsg.py SensorRequestMsg.class SensorRequestMsg.java SensorReportMsg.py SensorReportMsg.class SensorReportMsg.java NetworkScanMsg.py NetworkScanMsg.class NetworkScanMsg.java TestSerial.class

TestSerial.class: TestSerial.java
	javac TestSerial.java

SensorRequestMsg.py: RadioCountToLeds.h
	mig python -target=$(PLATFORM) $(CFLAGS) -python-classname=SensorRequestMsg RadioCountToLeds.h sensor_request_msg -o $@

SensorRequestMsg.class: SensorRequestMsg.java
	javac SensorRequestMsg.java

SensorRequestMsg.java: RadioCountToLeds.h
	mig java -target=$(PLATFORM) $(CFLAGS) -java-classname=SensorRequestMsg RadioCountToLeds.h sensor_request_msg -o $@

SensorReportMsg.py: RadioCountToLeds.h
	mig python -target=$(PLATFORM) $(CFLAGS) -python-classname=SensorReportMsg RadioCountToLeds.h sensor_report_msg -o $@

SensorReportMsg.class: SensorReportMsg.java
	javac SensorReportMsg.java

SensorReportMsg.java: RadioCountToLeds.h
	mig java -target=$(PLATFORM) $(CFLAGS) -java-classname=SensorReportMsg RadioCountToLeds.h sensor_report_msg -o $@

NetworkScanMsg.py: RadioCountToLeds.h
	mig python -target=$(PLATFORM) $(CFLAGS) -python-classname=NetworkScanMsg RadioCountToLeds.h network_scan_msg -o $@

NetworkScanMsg.class: NetworkScanMsg.java
	javac NetworkScanMsg.java

NetworkScanMsg.java: RadioCountToLeds.h
	mig java -target=$(PLATFORM) $(CFLAGS) -java-classname=NetworkScanMsg RadioCountToLeds.h network_scan_msg -o $@

include $(MAKERULES)

