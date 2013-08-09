
#include "mypanel.h"

myPanel::myPanel(wxWindow *parent,string id): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize){

	this->id = id;

// 	&this->app =  wxGetApp();
}

void myPanel::Init(){
	this->OnLoad();
	this->BuildPage();
// 	this->app = &wxGetApp();
}


void myPanel::OnLoad(){
// 	this->addAction("insertar");
// 	this->addAction("borrar","eliminar");
// 	this->addAction("borrar2","eliminar");
// 	this->addAction("borrar3","eliminar");
// 	this->addAction("borrar4","eliminar");
// 	this->addAction("pepe","don jose");

}  // Cargará las acciones de las que dispondrá el panel.

void myPanel::buildQuery(){} // Se utiliza para construir el objeto query específico.


void myPanel::addAction(int id, string caption){
	wxButton* btn;
	if (caption == "") caption = id;

	btn = new wxButton(this, wxNewId(), wxString(caption.c_str(), wxConvUTF8),wxDefaultPosition, wxSize(190, 30));

	this->buttons.insert(pair<int,wxButton*>(id,btn));
	this->actions.insert(pair<int,int>(btn->GetId(),id));
	this->Connect(btn->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(myPanel::OnClickActionButton) );
}

void myPanel::BuildPage(){} // Realizará la construcción específica del panel utilizado.

void  myPanel::setApp(skeletonApp *app){
	this->app = app;
}


void myPanel::Reload(){} // Recargará los datos obteneidos por la consulta construida en el objeto QUERY.


void myPanel::actionsHandler(int action){
	cout << "Action enviada: " << action << endl;
}

void myPanel::completeActionsHandler(map<string,string>data){
// 	cout << "completeActionsHandler. Accion activa: " << this->curAction << endl;
	if(this->sendAction(this->curAction,data,data)) this->Reload();
	else{
		this->showMessage("Error",this->getMsgError());
	}
}

void myPanel::OnClickActionButton(wxCommandEvent& event){
	this->curAction = this->actions[event.GetId()];
	this->actionsHandler(this->curAction);
}

void  myPanel::showMessage(string msg,string header){
	wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),wxString( header.c_str(), wxConvUTF8),   wxOK|wxICON_INFORMATION, this );
}

bool myPanel::sendAction(int action, map<string,string> data,map<string,string> key){
	return this->app->sendAction(this->id,action,data,key);
}


void myPanel::replayAction(string action,map<string,string>data){
	if ((action== "acept") && (this->curAction != -1) )
	{
		this->completeActionsHandler(data);
// 		this->showMessage("Entramos bien!!","Alertilla!!!!");
		
		/*bool exit = this->app->sendAction(this->id,this->curAction,data,this->curItem);
		string msg = this->app->getMsgError() + "-- Respiesta: ";
		if (exit == 1) msg += "Exito";
		else msg += "Fracaso";
		wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),   wxOK|wxICON_INFORMATION, this );*/
	}
	this->curAction = -1;
	this->curItem.clear();	

	
} // Captará la respuesta del objeto popup lanzado.


list<temp> myPanel::select(int type,map<string,string> filter){
	return this->app->select(this->id,type,filter);
}

string myPanel::getMsgError(){
	return this->app->getMsgError(this->id);
}
