
#include "mypanel.h"

myPanel::myPanel(wxWindow *parent,string id): basePanel(parent,id){
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

void myPanel::addAction(int id, wxControl* obj) {
	this->buttons.insert(pair<int,wxControl*>(id,obj));
	this->actions.insert(pair<int,int>(obj->GetId(),id));
};

void myPanel::BuildPage(){} // Realizará la construcción específica del panel utilizado.

void myPanel::Reload(){} // Recargará los datos obteneidos por la consulta construida en el objeto QUERY.


void myPanel::actionsHandler(int action){
	cout << "Action enviada: " << action << endl;
}

void myPanel::completeActionsHandler(map<string,string>data){
// 	cout << "myPanel::completeActionsHandler. Accion activa: " << this->curAction << endl;
	if(this->sendAction(this->curAction,data,data)) this->Reload();
	else{
		this->showMessage("Error",this->getMsgError());
	}
}

wxGridBagSizer* myPanel::buildActionSizer() {
	wxGridBagSizer *bag =new wxGridBagSizer();
	map<int, wxControl*>::iterator it;
	int ind = 1;
	for (it = this->buttons.begin(); it != this->buttons.end(); ind++, it++) {
		bag->Add((*it).second, wxGBPosition(ind, 0));
	}
	return bag;
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

map<string,string> myPanel::getFilter(){
	map<string,string> data;
	return this->app->filter(this->id,Agosal_Base_Action::ACT_getFilter,data);
}

void myPanel::setFilter(map<string,string> &data){
	this->app->filter(this->id,Agosal_Base_Action::ACT_setFilter,data);
}


void myPanel::replayAction(string action,map<string,string>data){
//	cout << "myPanel::replayAction. Accion activa: " << this->curAction << endl;
	if (this->curAction == Agosal_Base_Action::ACT_onFilter){
		this->setFilter(data);
		return;
	}
	if (this->curAction != -1){
		this->completeActionsHandler(data);
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
