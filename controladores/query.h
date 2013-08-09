/*
 * query.h
 *
 *  Created on: 20/02/2013
 *      Author: borja
 */

#ifndef QUERY_H_
#define QUERY_H_

#include "dataset.h"

class query {
protected:
	map<string,string> select;
	list<where_type> where;
	map<string,order_type> order;
	set<string> tables;
public:
	query();
	virtual ~query();

	int addField(string table, string field);
	int addFilter(string table, string field, string cond, string value);
	int setOrder(string table, string field, bool order=true);

	map<string,string> getFields();
	list<where_type> getFilters();
	set<string> getTables();
	map<string,order_type> getOrder();

	void impresion();
};

#endif /* QUERY_H_ */
