
#include "procedPanel.h"


procedPanel::procedPanel(wxWindow *parent,string id): panelGrid(parent,id){
	Init();

	this->qry.addField("t1", "primero");
	this->qry.addField("t1", "segundo");
	this->qry.addField("t1", "tercero");

	this->qry.addFilter("t1", "primero", "<=", "200");
	this->qry.addFilter("t4", "quinto", "<>", "200");

	this->qry.setOrder("t1", "pepe");
	this->qry.setOrder("t1", "pepe2", false);
	this->qry.setOrder("t1", "pepe3", true);

	
}


void procedPanel::OnLoad(){
	this->addAction(1,"añadir");
	this->addAction(2,"eliminar");
	this->addAction(3,"don manuel");
}

void procedPanel::buildQuery(){
// 	this->qry addField(string table, string field);
}

// int translade(string str){
// 	int value = 0;
// 	int size = str.length();
// 	for(int i=0;i<size;i++){
// 		value += str[i];
// 	}
// 	return value;
// }

// void procedPanel::replayAction(string action,map<string,string>data){
// 	cout << "Action enviada desde popup: " << action << endl;
// }

void procedPanel::completeActionsHandler(map<string,string>data){

	bool exit = this->app->sendAction(this->id,1,data,this->curItem);
	string msg = this->getMsgError() + "-- Respiesta: ";
	if (exit == 1) msg += "Exito";
	else msg += "Fracaso";
	wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),   wxOK|wxICON_INFORMATION, this );
}

void procedPanel::actionsHandler(int action){
	cout << "Action enviada desde procedPanel: " << action << endl;
	this->grid->resetGrid();
	switch (action){
		case 1:{
			cout << "añadir" << endl;
			MyPopup* pop = new MyPopup;
			pop->BuildPop(this);
			break;
		}
		case 2:
			cout << "eliminar" << endl;
			break;
		case 3:
			cout << "borrar" << endl;
			break;
		case 4:
			cout << "jugar" << endl;
			break;
		default:
			cout << "default" << endl;
			break;
	}
	push_Debug("ProcedPanel accion:"+ action);
	
// 	if(action=="añadir"){
// 		
// 	}
// 	else if(action=="borrar"){
// 		
// 	}
// 	else if(action=="editar"){
// 		
// 	}else if(action=="jugar"){
// 
// 	}
// 	else{
// 		cout << "default" << endl;
// 	}
	
}



list<itemHeaderColumn> procedPanel::headerGrid(){
	list<itemHeaderColumn> header;
	header.push_back(itemHeaderColumn("N_Factura","primero"));
	header.push_back(itemHeaderColumn("telefono","segundo"));
	header.push_back(itemHeaderColumn("3","segundo"));
	header.push_back(itemHeaderColumn("4","segundo"));
	header.push_back(itemHeaderColumn("5","segundo"));
	return header;
}