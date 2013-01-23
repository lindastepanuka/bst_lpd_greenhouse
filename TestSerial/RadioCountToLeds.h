/*
 * Copyright (c) 2004-2005 The Regents of the University  of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the University of California nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Copyright (c) 2002-2003 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA,
 * 94704.  Attention:  Intel License Inquiry.
 */

#ifndef RADIO_COUNT_TO_LEDS_H
#define RADIO_COUNT_TO_LEDS_H

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
