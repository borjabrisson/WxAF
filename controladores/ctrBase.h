/*
 * ctrBase.h
 *
 *  Created on: 20/02/2013
 *      Author: borja
 */

#ifndef CTRBASE_H_
#define CTRBASE_H_

#include "query.h"
#include "parser.h"
#include "../conector/sgbd_baseConector.h"
#include "../base/sysEvent.h"

#include "dataset.h"
#include "Customcomunicate.h"

class ctrBase {
protected:
	map<string,table> tables;
	sgbd_baseConector* conector;
	string error_type; // Indicara la procedencia(tipo) del último error producido.
	parser filterParser;
	map<string,string> filterObj;
	string filterString;
public:
	ctrBase();
	~ctrBase();


	virtual list<field_type> select(string idFrame,int type,map<string,string> filter){list<field_type> temp; return temp;}
	
	int executeProcedure();
//	map<string,string> select(query clause);

	Customcomunicate ActionRequest(Customcomunicate block);

	string messageProcedure();

	bool procedure(string bd,string procedure,list<string> values);


	virtual bool sendAction(string idFrame,int action, map<string,string> data, map<string,string> key);//{return false;}
	virtual field_type filter(string idFrame,int type,map<string,string> &filter);
	string getMsgError();
	
// 	int setCredentials(string user,string pass);
	void setConector(sgbd_baseConector *conector);

protected:

	Customcomunicate createMsgblock(int action);
	Customcomunicate createMsgblock(int action, map<string, string> data);
	Customcomunicate createMsgblock(int action, list<field_type> dataset);
	Customcomunicate createMsgblock(int action,int subType,map<string,string> data);
	Customcomunicate createMsgblock(int action,int subType,list<field_type> dataset);
	Customcomunicate createMsgblock(int action,int subType,map<string,string> data,list<field_type> dataset);
	
	virtual Customcomunicate HandleActions(Customcomunicate block);
	virtual Customcomunicate HandleQuery(Customcomunicate block);
	virtual Customcomunicate HandleFilter(Customcomunicate block);

	int checkFormat(string type, string value);
	int checkPK(string table,map<string,string> values);
	int checkNotNull(string table,map<string,string> values, bool insert=true);

	string clauseSelect(map<string,string> select);
	string clauseFrom(set<string> tables);
	string clauseWhere(list<where_type> where);
	string clauseOrder(map<string,order_type> order);
	string getClauseWhere(map<string,string> &filter);

	string buildArgsString(string args[],int size,map<string, string> &data);

	void buildFilterString();
};

#endif /* CTRBASE_H_ */
