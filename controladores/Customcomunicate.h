/*
 * Customcomunicate.h
 *
 *  Created on: 12/11/2013
 *      Author: borja
 */

#ifndef CUSTOMCOMUNICATE_H_
#define CUSTOMCOMUNICATE_H_

#include "../configuracion/configuracion.h"
#include "dataset.h"

class Customcomunicate {
public:
	enum typeAction{
		Action_type = 350,
		Query_type,
		Filter_type
	};

	string panelID;
	int type;
	int actionID; // Especifica tanto la acción como la consulta a utilizar.
	int specificAction; // Se utilizará como subcategoría en los casos donde una acción pueda tener alternativas.
	map<string,string> *data; // Contendrá los datos a utilizar en los casos de filtros, acciones, etc.
	list<field_type> *dataset; // Conjunto de datos provenientes de una consulta.

	Customcomunicate();
	~Customcomunicate();
};

#endif /* CUSTOMCOMUNICATE_H_ */
