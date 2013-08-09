/*
 * sgbd_conector.cpp
 *
 *  Created on: 27/12/2012
 *      Author: Borja
 */

#include "sgbd_conector.h"
/*
sgbd_conector::sgbd_conector() {}

sgbd_conector::~sgbd_conector() {}
*/

sgbd_conector::sgbd_conector() : sgbd_baseConector() {}

int sgbd_conector::setCredentials(string user,string pass){
	this->username = user;
	this->pass = pass;

	if (!this->conect()){
		this->desconect();
		push_Error("\nsgbd_conector::setCredentials.\n Error en la conexión."+(string)mysql_error(this->myData) );
		this->msgSP = mysql_error(this->myData);
		return 0;
	}
	return 1;
}