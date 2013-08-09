#ifndef DATASET_H_
#define DATASET_H_

#include <map>
#include <iostream>
#include <string>
#include <list>
#include <set>

using namespace std;


typedef struct structField{
	string field; // nombre propio del campo en la BD.
	string caption;
	string type; // podría ser un enumerado. Text, date, date stamp, enum...
	string tnull; // pk, not null o null
	bool autoincrement; //
	// podría interesarme los FK ¿?
}field;

typedef map<string,field> field_asoc;

typedef struct structTable{
	string table;  // Nombre de la tabla en la BD.
	string caption;
	int permission;  // segun el valor nos permitirá realizar diversas acciones
	bool general; // Indica si se trata de una tabla general, visible por todos, o una propia.
	field_asoc fields;
}table;




typedef map<string,string> field_type;
typedef struct structWhere{
	string table;
	string field;
	string condition;
	string value;
}where_type;

typedef struct structOrder{
	string table;
	bool order; // True= ASC, false = Desc
}order_type;




#endif /* DATASET_H_ */