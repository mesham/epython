/*
 * host-functions.h
 *
 *  Created on: 8 Apr 2015
 *      Author: nick
 */

#ifndef HOST_FUNCTIONS_H_
#define HOST_FUNCTIONS_H_

#if defined(EPIPHANY_TARGET)
#include "epiphany-shared.h"
#elif defined(HOST_STANDALONE)
#include "host-shared.h"
#endif

void initHostCommunicationData(int, struct shared_basic*, int);
void sendData(struct value_defn, int, char, int, int);
struct value_defn recvData(int, int, int);
struct value_defn sendRecvData(struct value_defn, int, int, int);
struct value_defn bcastData(struct value_defn, int, int, int, int);
struct value_defn reduceData(struct value_defn, int, int, int, int);
struct value_defn probeForMessage(int, int, int);

#endif /* HOST_FUNCTIONS_H_ */
