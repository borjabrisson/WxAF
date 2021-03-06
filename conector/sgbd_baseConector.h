/*
 * sgbd_baseConector.h
 *
 *  Created on: 27/12/2012
 *      Author: Borja
 */

#ifndef SGBD_BASECONECTOR_H_
#define SGBD_BASECONECTOR_H_

#include "../configuracion/configuracion.h"

#include <mysql.h>
#include <mysqld_error.h>
#include <map>
#include <iostream>
#include <string>
#include <list>
// #include "translateactionsql.h"
using namespace std;

// ### DATAS!!!

typedef map<string,string> field_type;
typedef struct mystruct{
	string value;
	string tipo;
	bool foreing; // Estas dos se pueden combinar
	string table;
}tep;


class sgbd_baseConector {
protected:
	MYSQL *myData;
	string username;
	string pass;
	string host;
	string generalDB;
	string userDB;
	map<string,string> msgBlock;


	string msgSP; // mesage Store Procedure.
	int port;
protected:
	field_type translade(list<string> order,MYSQL_ROW res);
	void setMessage(map<string,string> data);
	map<string,string> resultSP();
	
	bool commit();
	bool rollback();

	map<string,string> get_row(MYSQL_ROW &row,MYSQL_RES *res);

	
public:/*
	sgbd_baseConector();
	~sgbd_baseConector();*/
	
	sgbd_baseConector();
	int conect(string db = "");
	int desconect();

	int query(string db, string clause,list<field_type> &record);
	int procedure(string db, string clause);

	string msgLastProcedure();
	map<string,string> getmsgBlock();
	string getUserDB(){
		return userDB;
	}
	string getGeneralDB(){
		return generalDB;
	}
};
#endif /* SGBD_BASECONECTOR_H_ */
