/*
 * ctrBase.cpp
 *
 *  Created on: 20/02/2013
 *      Author: borja
 */

#include "ctrBase.h"
ctrBase::ctrBase() {
	// TODO Auto-generated constructor stub
	field campo;
	table tabla;
	tabla.general=true;		tabla.permission=1;
	tabla.table="facturas";		tabla.caption= "prueba_record";

	campo.autoincrement=true;	campo.caption= "N_Factura";	campo.field= "C1";
	campo.tnull="pk";			campo.type="text";

	tabla.fields.insert(pair<string,field>("factura",campo));


	campo.autoincrement=true;	campo.caption= "telefono";	campo.field= "C2";
	campo.tnull="null";			campo.type="text";

	tabla.fields.insert(pair<string,field>("telefono",campo));


	campo.autoincrement=false;	campo.caption= "N_Linea";	campo.field= "C3";
	campo.tnull="not";			campo.type="text";

	tabla.fields.insert(pair<string,field>("linea",campo));

	this->tables.insert(pair<string,table>("facturas",tabla));

}

ctrBase::~ctrBase() {
	// TODO Auto-generated destructor stub
	this->tables.clear();
}

int ctrBase::checkFormat(string type, string value){
	return 0;
}

int ctrBase::checkPK(string table,map<string,string> values){
	field_asoc fields = this->tables[table].fields;
	field_asoc::iterator it;

	for (it = fields.begin(); (*it).second.tnull != "null"; it++){
		if (values.count((*it).first) == 0) return 1;
	}
	return 0;
}

int ctrBase::checkNotNull(string table,map<string,string> values, bool insert){
	field_asoc fields = this->tables[table].fields;
	field_asoc::iterator it;
	int code;
	for (it = fields.begin(); it != fields.end(); it++){
		if (values.count((*it).first) != 0){
			if (((*it).second.tnull != "null")&&(values[(*it).first]=="") && (!((*it).second.autoincrement && insert))) return 4;
			code = this->checkFormat((*it).second.type,values[(*it).first]);
			if (code != 0) return code;
		}
		else{
			if (((*it).second.tnull != "null") && (!((*it).second.autoincrement && insert))) return 3;
		}
	}
	return 0;
}

int translate_paint(list<field_type> registro){
	list<field_type>::iterator it_list;
	field_type row;
	field_type::iterator it_row;
	for ( it_list=registro.begin() ; it_list != registro.end(); it_list++ ){
			row = (*it_list);
			for ( it_row=row.begin() ; it_row != row.end(); it_row++ ){
					cout << (*it_row).first << " = " <<(*it_row).second << " || ";
			}
			cout << endl;
	}
	return 0;
}

void ctrBase::setConector(sgbd_baseConector *conector){
	this->conector = conector;
}


list<field_type>  ctrBase::select(query clause){
	string select, from, where, order, out;
	
	select = "Select "+ this->clauseSelect(clause.getFields()) + "\n";
	from = "From "+ this->clauseFrom(clause.getTables()) + "\n";
	out = this->clauseWhere(clause.getFilters());
	
	if (out != "")	where = "Where "+ out  + "\n";
// 	else where
	out = this->clauseOrder(clause.getOrder());
	if(out != "")	order = "Order by " +  out + "\n";

	list<field_type> record;
	this->conector->query("test",select + from + where + order,record);

	#ifdef DEBUG_OUT
		translate_paint(record);
	#endif
		
	push_Debug(select + from + where + order);
	return record;	
}


string ctrBase::messageProcedure(){
	return this->conector->msgLastProcedure();
}


string ctrBase::clauseSelect(map<string,string> select){
	map<string,string>::iterator it;
	table tabla;
	string out="",sep="";
	for (it = select.begin();it != select.end(); it++){
		tabla = this->tables[(*it).second];
		out += sep+tabla.caption + "." + tabla.fields[(*it).first].caption;
		sep = ", ";
	}
	return out;
}

string ctrBase::clauseFrom(set<string> tables){
	set<string>::iterator it;
	string out="",sep="";
	for (it = tables.begin();it != tables.end(); it++){
		out += sep+this->tables[(*it)].caption;
		sep = ", ";
	}
	return out;
}

string ctrBase::clauseWhere(list<where_type> where){
	list<where_type>::iterator it;
	string out="",sep="";
	table tabla;
	for (it = where.begin();it != where.end(); it++){
		tabla = this->tables[(*it).table];
		out += sep+tabla.caption + "." + tabla.fields[(*it).field].caption + " " + (*it).condition+" "+(*it).value;
		sep = " AND ";
	}
	return out;
}

string ctrBase::clauseOrder(map<string,order_type> order){
	map<string,order_type> ::iterator it;
	string out="",sep="";
	table tabla;
	for (it = order.begin();it != order.end(); it++){
		tabla = this->tables[(*it).second.table];
		out += sep+tabla.caption + "." + tabla.fields[(*it).first].caption;
		if ((*it).second.order) out += " ASC";
		else out += " DESC";
		sep = ", ";
	}
	return out;
}

// int ctrBase::setCredentials(string user,string pass){
// 	return this->conector->setCredentials(user,pass);
// }


bool ctrBase::procedure(string bd,string procedure,list<string> values){
// 	if (this->conector->procedure(bd,)){
// 		return true;
// 	}
// 	this->error_type
return true;
}

string ctrBase::getMsgError(){
	return this->conector->msgLastProcedure();
}

bool ctrBase::sendAction(string idFrame,int action, map<string,string> data, map<string,string> key){
	push_Debug("ctrBase::sendAction.# idFrame: "+idFrame+". Action: ");
	return this->conector->procedure("test","call prueba(\"121\",\"554\",\"0\");");
}

