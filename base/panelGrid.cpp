
#include "panelGrid.h"

panelGrid::panelGrid(wxWindow *parent, string id): panelBaseGrid(parent,id){
	//
}

void panelGrid::BuildPage(){
	
	if (this->gridBagSizer == NULL){
		this->gridBagSizer = new wxGridBagSizer();
		this->actionBag = new wxGridBagSizer(); // Podría utilizarse un sizerBox en lugar de un gridBag...
		this->SetSizer(this->gridBagSizer);
		list<itemHeaderColumn> aux = this->headerGrid();
		this->grid = new MyGrid(this, wxID_ANY,aux,wxDefaultPosition,wxDefaultSize);
		
		this->gridBagSizer->Add(this->grid, wxGBPosition(0, 0), wxGBSpan(10, 2),wxGROW);
		this->gridBagSizer->Add(this->actionBag, wxGBPosition(0, 3), wxGBSpan(1, 1),wxGROW);

		this->setGridEvent(this->grid);
	}

	
	this->gridBagSizer->Fit(this);
	this->gridBagSizer->SetSizeHints(this);

	map<int,wxButton*>::iterator it;
	int ind =1;
	for ( it=this->buttons.begin() ; it != this->buttons.end();ind++, it++ ){
		this->actionBag->Add((*it).second, wxGBPosition(ind, 0));
	}



	this->gridBagSizer->AddGrowableRow(1);this->gridBagSizer->AddGrowableCol(1);
}


void panelGrid::Reload(){
	cout << "Reload:: PANEL"<< endl;
	list<field_type> dataset;
	dataset = this->app->select(this->qry);
	this->grid->pushDataSet(dataset);
}
