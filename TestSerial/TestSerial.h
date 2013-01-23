#ifndef TEST_SERIAL_H
#define TEST_SERIAL_H

 typedef nx_struct sensor_request_msg {
    // SensorRequestMsg (packetType = 1, dataLen = 7)

    // skaitîtâjs paku dublikâtu identificçðanai
    nx_uint16_t counter;
    // sensoru mezgla id
    nx_uint16_t moteId;
    // kuru sensoru lasît: 1 = pilnâ gaisma, 2 = fotosintçtiskâ gaisma, 3 = temperatûra, 4 = mitrums
    nx_uint16_t sensorId;
    // ik pa cik sekundçm lasît un sûtît ðî sensora lasîjumus, (0 nozîmç "nolasît tikai vienreiz")
    nx_uint16_t period;
    // no cik lasîjumiem vilkt vidçjo vçrtîbu (min = 1, max = 100)
    nx_uint16_t avg;
 } sensor_request_msg_t;

 typedef nx_struct sensor_report_msg {
    // SensorReportMsg (packetType = 2, dataLen = 7)

    // skaitîtâjs paku dublikâtu identificçðanai
    nx_uint16_t counter;
    // sensoru mezgla id
    nx_uint16_t moteId;
    nx_uint16_t temperatureValue;
    nx_uint16_t humidityValue;
    nx_uint16_t photoLightValue;
    nx_uint16_t fullLightValue;
 } sensor_report_msg_t;

 typedef nx_struct network_scan_msg {
    // NeworkScanMsg (packetType = 3, dataLen = 2)

    // skaitîtâjs paku dublikâtu identificçðanai
    nx_uint16_t counter;
 } network_scan_msg_t;

enum {
   AM_SENSOR_REQUEST_MSG = 1,
   AM_SENSOR_REPORT_MSG = 2,
   AM_NETWORK_SCAN_MSG = 3,
 };

#endif
