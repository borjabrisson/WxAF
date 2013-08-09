
#include "frameContainer.h"


frameContainer::frameContainer(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame( NULL, -1, title, wxDefaultPosition, wxDefaultSize,wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{}

void frameContainer::Init(){
	this->menuBar = new wxMenuBar;
    SetMenuBar(this->menuBar);

	wxGridBagSizer* gridBagSizer = new wxGridBagSizer();
	this->SetSizer(gridBagSizer);
	this->note =  new wxNotebook(this, wxID_ANY, wxDefaultPosition,wxDefaultSize, 0, _T("ID_NOTEBOOK1"));

	this->buildFrame();

	gridBagSizer->Add(this->note, wxGBPosition(0, 1), wxGBSpan(3, 3),	wxGROW);
	gridBagSizer->AddGrowableRow(1);gridBagSizer->AddGrowableCol(1);

	gridBagSizer->Fit(this);
	gridBagSizer->SetSizeHints(this);
	
}

void frameContainer::addPage(string id,string tab, myPanel* page){
	this->contenedor.insert(pair<string,myPanel*>(id,page));

	page->setApp(this->app);
	this->note->AddPage(page, wxString( tab.c_str(), wxConvUTF8), true);
}

void frameContainer::RefreshData(){
	push_Debug("Entramos ne le RefreshData");

	map<string,myPanel*>::iterator it;

	for(it=this->contenedor.begin(); it!=this->contenedor.end();it++){
		push_Debug("Reload de: " + (*it).first);
		(*it).second->Reload();
	}
}