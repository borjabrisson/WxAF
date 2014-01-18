// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "PeopleContactCard.h"

PeopleContactCard::PeopleContactCard():MyPopup(){
	this->type = 0;
}

PeopleContactCard::PeopleContactCard(int type):MyPopup(){
	this->type = type;
}


void PeopleContactCard::createAction(){
	switch(type){
	case type_Empresas:
		this->AddComponent("ID","ID",textInput,20);
		this->AddComponent("CIF","CIF",textInput,150);
		this->AddComponent("name","Nombre",textInput,600);
		this->AddComponent("web","Web",textInput,60);
		this->AddComponent("address","Dirección",textInput,150);
		this->AddComponent("email","Email",textInput,600);

		break;
	case type_Abogados:
		this->AddComponent("ID","ID",textInput,20);
				this->AddComponent("lawyerNumber","Nº Abogado",textInput,150);
				this->AddComponent("name","Nombre",textInput,600);
				this->AddComponent("surnames","Apellidos",textInput,60);
				this->AddComponent("address","Dirección",textInput,150);
				this->AddComponent("email","Email",textInput,600);

		break;
	case type_Procuradores:
		this->AddComponent("ID","ID",textInput,20);
					this->AddComponent("attorneyNumber","Nº Procurador",textInput,150);
					this->AddComponent("name","Nombre",textInput,600);
					this->AddComponent("surnames","Apellidos",textInput,60);
					this->AddComponent("address","Dirección",textInput,150);
					this->AddComponent("email","Email",textInput,600);

		break;
	case type_Clientes:
		this->AddComponent("ID","ID",textInput,20);
					this->AddComponent("DNI","DNI",textInput,150);
					this->AddComponent("name","Nombre",textInput,600);
					this->AddComponent("surnames","Apellidos",textInput,60);
					this->AddComponent("address","Dirección",textInput,150);
					this->AddComponent("email","Email",textInput,600);

		break;
	}

	sendMode();
}



//void PeopleContactCard::HandleEvent(string action){
//	map<string,string> out = this->getInputsValue();
//	this->parent->replayAction(action,out);
//	this->Close(true);
//// 	this->Destroy();
//}

void PeopleContactCard::HandleEvent(string action){
	if ((action == "Salir")||(action == "Descartar")){
		this->Close(true);
		return;
	}
	else{
		if (checkInputsValue()){
				cout << "Dentro del IF HandleEvent!!!"<< endl;
				map<string,string> out = this->getInputsValue();
				this->parent->replayAction(action,out);
				this->Close(true);
			}
	}
}


void PeopleContactCard::readMode(){
	this->addAction("Responder");		this->addAction("Reenviar");		this->addAction("Salir");
}
void PeopleContactCard::sendMode(){
	this->addAction("Enviar");		this->addAction("Descartar");
}

// int PeopleContactCard::ChangeMode(bool lookup){
// 	map<string,string> out;
// 	out.insert(pair<string,string>("factura","1234"));
// 	out.insert(pair<string,string>("cliente","pepe"));
// 	this->setValues(out);
// 
// 	return 2;
// }

// list<row_type> PeopleContactCard::getLookupQuery(string action,map<string,string> &header){}

// void PeopleContactCard::setValues(map<string,string> values){
// 	if (this->lookup == "factura"){
// 		this->box->setValue("factura",values["factura"]);
// 	}
// }

