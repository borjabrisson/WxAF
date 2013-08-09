/*
 * ctrBase.h
 *
 *  Created on: 20/02/2013
 *      Author: borja
 */

#ifndef CTRBASE_H_
#define CTRBASE_H_

#include "query.h"
#include "../conector/sgbd_baseConector.h"

#include "dataset.h"

class ctrBase {
protected:
	map<string,table> tables;
	sgbd_baseConector* conector;
	string error_type; // Indicara la procedencia(tipo) del último error producido.
public:
	ctrBase();
	~ctrBase();

	list<field_type> select(query clause);

	virtual list<field_type> select(string idFrame,int type,map<string,string> filter){list<field_type> temp; return temp;}
	
	int executeProcedure();
//	map<string,string> select(query clause);

	// ### A Borrar estas 3.
	int insert(string table, map<string,string> values);
	int eraser(string table, map<string,string> id);
	int modify(string table, map<string,string> values, map<string,string> id);

	string messageProcedure();

	bool procedure(string bd,string procedure,list<string> values);


	virtual bool sendAction(string idFrame,int action, map<string,string> data, map<string,string> key);//{return false;}
	string getMsgError();
	
// 	int setCredentials(string user,string pass);
	void setConector(sgbd_baseConector *conector);

protected:

	
	int checkFormat(string type, string value);
	int checkPK(string table,map<string,string> values);
	int checkNotNull(string table,map<string,string> values, bool insert=true);

	string clauseSelect(map<string,string> select);
	string clauseFrom(set<string> tables);
	string clauseWhere(list<where_type> where);
	string clauseOrder(map<string,order_type> order);
};

#endif /* CTRBASE_H_ */
