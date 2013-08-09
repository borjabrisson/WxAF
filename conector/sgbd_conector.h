/*
 * sgbd_conector.h
 *
 *  Created on: 27/12/2012
 *      Author: Borja
 */

#ifndef SGBD_CONECTOR_H_
#define SGBD_CONECTOR_H_

#include "sgbd_baseConector.h"

// ### DATAS!!!

class sgbd_conector : public sgbd_baseConector {
	
public:	
	sgbd_conector();
	int setCredentials(string user,string pass);

};
//	g++ -I/usr/include/mysql -O0 -g3 -Wall -DBIG_JOINS=1  -fno-strict-aliasing  -g -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"main.d" -L '/usr/lib/i386-linux-gnu' -lmysqlclient -lpthread -lz -lm -lrt -ldl -o "main.o" "main.cpp"
//	g++ -I/usr/include/mysql -O0 -g3 -Wall -DBIG_JOINS=1  -fno-strict-aliasing  -g -c -fmessage-length=0 -MMD -MP -MF"sgbd_conector.d" -MT"sgbd_conector.d" -L '/usr/lib/i386-linux-gnu' -lmysqlclient -lpthread -lz -lm -lrt -ldl -o "sgbd_conector.o" sgbd_conector.cpp
//  g++  -L '/usr/lib/i386-linux-gnu' -lmysqlclient -lpthread -lz -lm -lrt -ldl -o "conector" ./main.o ./sgbd_conector.o
#endif /* SGBD_CONECTOR_H_ */
