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
	push_Debug("sgbd_conector::setCredentials: "+user+" -- "+pass);
	this->username = user;
	this->pass = pass;
	int ret = 1;
	if (this->conect() != 0){ // usuario y/o contraseña incorrectos.
		this->clearCredential();
		push_Error("\nsgbd_conector::setCredentials.\n Error en la conexión."+(string)mysql_error(this->myData) );
		this->msgSP = mysql_error(this->myData);
		return 1;
	}
	else{
		this->desconect();
		int value = this->procedure(this->generalDB,"CheckCredentials()");
		if (value != 1){ // El usuario no tiene acceso al sistema Agosal.
			push_Debug("El usuario no tiene acceso al sistema agosal");
			this->clearCredential();
		}
		else{ // obtenemos el valor de la BD del usuario dentro del sistema Agosal.
			ret = 0;
			this->userDB = this->msgBlock["userDB"];
			push_Debug("Obtenemos la BD del usuario!: "+this->userDB);
		}
	}
	return ret;
}


void sgbd_conector::clearCredential(){
	this->username = "";
	this->pass = "";
	this->userDB = "";
}

/*
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
}*/
