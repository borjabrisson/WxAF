
#include "pruebaPanel.h"


pruebaPanel::pruebaPanel(wxWindow *parent,string id) :panelGrid(parent,id){
	Init();

	this->qry.addField("facturas", "factura");
	this->qry.addField("facturas", "telefono");
	this->qry.addField("facturas", "linea");

// 	this->qry.addFilter("t1", "primero", "<=", "200");
// 	this->qry.addFilter("t4", "quinto", "<>", "200");

	this->qry.setOrder("facturas", "linea");
// 	this->qry.setOrder("t1", "pepe2", false);
// 	this->qry.setOrder("t1", "pepe3", true);

}


void pruebaPanel::OnLoad(){
	this->addAction(1, "Añadir Factura");
	this->addAction(2,"eliminar");
	this->addAction(3,"Editar Factura");

// 	this->addAction("añadir2", "Añadir Factura");
// 	this->addAction("borrar2","eliminar");
// 	this->addAction("editar2","Editar Factura");
}

void pruebaPanel::buildQuery(){
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

// void pruebaPanel::replayAction(string action,map<string,string>data){
// 	cout << "Action enviada desde popup: " << action << endl;
// }

void pruebaPanel::completeActionsHandler(map<string,string>data){

	bool exit = this->app->sendAction(this->id,1,data,this->curItem);
	string msg = this->getMsgError() + "-- Respiesta: ";
	if (exit == 1) msg += "Exito";
	else msg += "Fracaso";
	wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),   wxOK|wxICON_INFORMATION, this );
}

void pruebaPanel::actionsHandler(int action){
	cout << "Action enviada desde pruebaPanel: " << action << endl;

// 	wxGridCellAttr *attr = new wxGridCellAttr(this->grid->GetOrCreateCellAttr(1,1));
// 	attr->SetBackgroundColour(wxColour(135,206,235)); //sky blue
// 	this->grid->SetRowAttr(1,attr);

	this->grid->setColourRow(1,wxColour(135,206,235));
	this->grid->resetGrid();
	switch (action){
		case 1:{
			cout << "añadir" << endl;
			facturaPop* pop = new facturaPop;
			pop->BuildPop(this);
			break;}
		case 2:{
			cout << "eliminar" << endl;
			int numRow= this->grid->numRowSelected();
			if (numRow == 1){
				MyPopup* pop = new MyPopup;
				pop->BuildPop(this);
			}
			else{
				string msg;
				if (numRow == 0) msg = "Seleccione un elemento";
				else		   msg = "No puede seleccionar más de un elemento";
				wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),      wxOK|wxICON_INFORMATION, this );
			}
			break;}
		case 3:{
			cout << "editar" << endl;
			int numRow= this->grid->numRowSelected();
			if (numRow == 1){
				this->grid->resetGrid();

				this->curItem.insert(pair<string,string>("factura","5545"));
				MyPopup* pop = new MyPopup;
				pop->BuildPop(this);
			}
			else{
				string msg;
				if (numRow == 0) msg = "Seleccione un elemento";
				else		   msg = "No puede seleccionar más de un elemento";
				wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),      wxOK|wxICON_INFORMATION, this );
			}
			break;}
		case 4:
			cout << "jugar" << endl;
			break;
		default:
			cout << "default" << endl;
			break;
	}

}



list<itemHeaderColumn> pruebaPanel::headerGrid(){
	list<itemHeaderColumn> header;
	header.push_back(itemHeaderColumn("factura","Nº Factura"));
	header.push_back(itemHeaderColumn("telefono","telefono"));
	header.push_back(itemHeaderColumn("linea","Linea de Factura"));
	header.push_back(itemHeaderColumn("cliente","Cliente"));
	header.push_back(itemHeaderColumn("cantidad","Cantidad"));
	header.push_back(itemHeaderColumn("fecha","Fecha"));

	return header;
}