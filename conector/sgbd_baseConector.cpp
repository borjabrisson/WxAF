/*
 * sgbd_baseConector.cpp
 *
 *  Created on: 27/12/2012
 *      Author: Borja
 */

#include "sgbd_baseConector.h"
/*
sgbd_baseConector::sgbd_baseConector() {}

sgbd_baseConector::~sgbd_baseConector() {}
*/

sgbd_baseConector::sgbd_baseConector() {
	this->username = SGBD_USER_DEFAULT;
	this->pass = SGBD_PASS_DEFAULT;
	this->host = SGBD_HOST_DEFAULT;
	this->generalDB = SGBD_DB_DEFAULT;
	this->port = MYSQL_PORT;
	this->userDB = "";
}
/*
int sgbd_baseConector::conect(string db){
	if(!(this->myData = mysql_init(0))){
	   // Imposible crear el objeto myData
	   push_Error("\nsgbd_baseConector::Conect.\n Imposible crear el objeto myData:: " + (string)mysql_error(this->myData) );
	   this->msgSP = mysql_error(this->myData);
	   return 1;
	}
	if (db == "") db = this->generalDB;
	mysql_ssl_set(this->myData, NULL, NULL, "/etc/mysql/cert/ca-cert.pem", NULL, NULL);
	if(!mysql_real_connect(this->myData, this->host.c_str(), this->username.c_str(),this->pass.c_str(),db.c_str(),this->port, NULL, 0)){		  
		// No se puede estabñecer la conexión con el servidor.
		push_Error("\nsgbd_baseConector::Conect.\n No se ha podido crear la conexion:\n Error:"+(string)mysql_error(this->myData) );
		this->msgSP = mysql_error(this->myData);
		this->desconect();
		return 1;
	}
	push_Debug("Conexion correcta!!!");
	return 0;
}
*/
int sgbd_baseConector::conect(string db){
	if(!(this->myData = mysql_init(0))){
	   // Imposible crear el objeto myData
	   push_Error("\nsgbd_baseConector::Conect.\n Imposible crear el objeto myData:: " + (string)mysql_error(this->myData) );
	   this->msgSP = mysql_error(this->myData);
	   return 1;
	}
	if (db == "") db = this->generalDB;
	mysql_ssl_set(this->myData, NULL, NULL, DIR_CERT, NULL, NULL);
	if(!mysql_real_connect(this->myData, this->host.c_str(), this->username.c_str(),this->pass.c_str(),db.c_str(),this->port, NULL, 0)){
		// No se puede estabñecer la conexión con el servidor.
		push_Error("\nsgbd_baseConector::Conect.\n No se ha podido crear la conexion:\n Error:"+(string)mysql_error(this->myData) );
		this->msgSP = mysql_error(this->myData);
		this->desconect();
		return 1;
	}
	return 0;
}


int sgbd_baseConector::desconect(){
	if(this->myData != NULL ){
		mysql_close(this->myData);
		this->myData = NULL;
		return 0;
	}
	push_Error("\nsgbd_baseConector::desconect.Se está intentando cerrar una conexión no establecida." );
	return 2;
}

int sgbd_baseConector::query(string db, string clause,list<field_type> &record){
	this->conect(db);
	if(mysql_query(this->myData, clause.c_str())) {
		// Error al realizar la consulta:
		push_Error("sgbd_baseConector::query. Error en la consulta. Error:"+(string)mysql_error(this->myData) );
		push_Error("sgbd_baseConector::query. Error en la consulta. consulta:"+clause);
		this->msgSP = mysql_error(this->myData);
// 		cout << "ERROR: " << mysql_error(this->myData) << endl;
		this->desconect();
		return 2;
	}
	MYSQL_RES       *res;
	if((res =  mysql_use_result(this->myData))) {
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(res)))
		{
			record.push_back(this->get_row(row,res));
		}
		mysql_free_result(res);
	}
	this->desconect();
	return record.size();
}

string sgbd_baseConector::msgLastProcedure(){
	return this->msgSP;
}

int sgbd_baseConector::procedure(string db, string clause){
	this->conect(db);
	mysql_autocommit(this->myData,0);

	clause = "call "+clause;
	if(mysql_query(this->myData, clause.c_str())) {
		// Error al realizar la consulta:
		push_Error("SGBD:Procedure. ERROR: "+(string)mysql_error(this->myData));
		push_Error("SGBD:Sentencia: "+ clause);
		this->msgSP = mysql_error(this->myData);
// 		this->rollback();
		this->desconect();
		return 0;//2
	}
	this->msgBlock = this->resultSP();
	int ret = 1;
	if (this->msgBlock.count("error") != 0){
		if (this->msgBlock["error"] == "0")
			this->commit();
		else{
			this->rollback();
			ret = 0;
		}
	}
	else{
		push_Error("SGBD:Procedure.No se encuentra el campo error en la respuesta del procedimiento.");
		this->rollback();
		ret = 0;
	}

	this->setMessage(this->msgBlock);

	this->desconect();
	return ret;
}

void sgbd_baseConector::setMessage(map<string,string> data){
	if (  (data.count("msg") != 0) || (data.count("message") != 0)  ){
		if (data.count("msg") != 0) 	this->msgSP = data["msg"];
		if (data.count("message") != 0) this->msgSP = data["message"];
	}
	else
		this->msgSP = "";
}

map<string,string> sgbd_baseConector::resultSP(){
	MYSQL_RES	*res;
	map<string,string> data;
	MYSQL_ROW row;

	while(mysql_next_result(this->myData)){ // La librería nos obliga a realizar un while para poder liberar los recursos y cerrar la conexión. ###
		res =  mysql_store_result(this->myData);
		while ((row = mysql_fetch_row(res)))
		{
			data = this->get_row(row,res);
		}
		 mysql_free_result(res);
	}
	return data;
}

map<string,string> sgbd_baseConector::get_row(MYSQL_ROW &row,MYSQL_RES *res){
	map<string,string> data;
	MYSQL_FIELD* fields;
	int nFields;

	fields = mysql_fetch_fields(res);
	nFields = mysql_num_fields(res);
	
	for (int ind_field = 0; ind_field < nFields; ind_field++) {
		if (NULL != row[ind_field]) {
			push_Debug("SGB:resultSP: Campo: " + (string) fields[ind_field].name+ " Valor: " + (string) row[ind_field]);
			data.insert(pair<string, string>(fields[ind_field].name,row[ind_field]));

		} else {
			push_Debug("SGB:resultSP: Campo: " + (string) fields[ind_field].name+ " Valor: 'Nulo'");
			data.insert(pair<string, string>(fields[ind_field].name, ""));
		}
	}

	return data;
}


bool sgbd_baseConector::commit(){
	if(!mysql_commit(this->myData))	return true;
	push_Error("SGBD:Commit. Error"+(string)mysql_error(this->myData) );
	this->msgSP = mysql_error(this->myData);
	return false;
}

bool sgbd_baseConector::rollback(){
	if (!mysql_rollback(this->myData))return true;
	push_Error("SGBD:RollBack. Error"+(string)mysql_error(this->myData) );
	this->msgSP = mysql_error(this->myData);
	return false;
}

map<string,string> sgbd_baseConector::getmsgBlock(){
	return msgBlock;
}

