/*
 * query.cpp
 *
 *  Created on: 20/02/2013
 *      Author: borja
 */

#include "query.h"

query::query() {
	// TODO Auto-generated constructor stub

}

query::~query() {
	// TODO Auto-generated destructor stub
}


int query::addField(string table, string field){
	this->select.insert(pair<string,string>(field,table));
	this->tables.insert(table);
	return 0;
}

int query::addFilter(string table, string field, string cond, string value){
	where_type filter;
	filter.table= table; 	filter.field= field;
	filter.condition=cond;	filter.value=value;
	this->where.push_back(filter);
	this->tables.insert(table);
	return 0;
}

int query::setOrder(string table, string field, bool order){
	order_type aux;
	aux.order = order;
	aux.table = table;
	this->order.insert(pair<string,order_type>(field,aux));

	return 0;
}


map<string,string> query::getFields(){
	return this->select;
}

list<where_type> query::getFilters(){
	return this->where;
}

set<string> query::getTables(){
	return this->tables;
}


map<string,order_type> query::getOrder(){
	return this->order;
}
