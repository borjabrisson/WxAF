// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "facturaPop.h"



void facturaPop::createAction(){

	this->AddComponent("factura","Nº Factura",true);
	this->AddComponent("linea","Nº de Línea");
	this->AddComponent("telefono","Teléfono");
	this->AddComponent("cliente","Id. Cliente",true);
}



void facturaPop::HandleEvent(string action){
//	map<string,string> out = this->box->getInputsValue();
//	cout << "valor de los elementos "<< out["1"] << endl;
//	this->parent->replayAction(action,out);
	this->Close(true);
// 	this->Destroy();
}

// int facturaPop::ChangeMode(bool lookup){
// 	map<string,string> out;
// 	out.insert(pair<string,string>("factura","1234"));
// 	out.insert(pair<string,string>("cliente","pepe"));
// 	this->setValues(out);
// 
// 	return 2;
// }

list<row_type> facturaPop::getLookupQuery(string action,map<string,string> &header){
	this->lookup= action;
	if(action == "factura"){
cout << "facturaPop::getLookupQuery action ="<< action << endl;

		header.insert(pair<string,string>("factura","Nº Factura"));
		header.insert(pair<string,string>("telefono","telefono"));
		header.insert(pair<string,string>("linea","Linea de Factura"));
		header.insert(pair<string,string>("cliente","Cliente"));
		header.insert(pair<string,string>("cantidad","Cantidad"));
		header.insert(pair<string,string>("fecha","Fecha"));

		list<row_type> out;
		query qry;
		qry.addField("facturas", "factura");
		qry.addField("facturas", "telefono");
		qry.addField("facturas", "linea");

// 		qry.addFilter("facturas", "factura", "<=", "200");
// 		qry.addFilter("t4", "quinto", "<>", "200");

		qry.setOrder("facturas", "linea");
		//out = this->parent->app->select(qry);
		return out;
	}
	else{
		list<row_type> out;
		return out;
	}
	
}

void facturaPop::setValues(map<string,string> values){
//	if (this->lookup == "factura"){
//		this->box->setValue("factura",values["factura"]);
//	}
}

