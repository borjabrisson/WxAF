
#include "panelGrid.h"

panelGrid::panelGrid(wxWindow *parent, string id): panelBaseGrid(parent,id){
	//
}

void panelGrid::BuildPage(){
	
	if (this->gridBagSizer == NULL){
		this->gridBagSizer = new wxGridBagSizer();
		this->SetSizer(this->gridBagSizer);
		list<itemHeaderColumn> aux = this->headerGrid();
		this->grid = new MyGrid(this, wxID_ANY,aux,wxDefaultPosition,wxDefaultSize);
		
		this->actionBag = buildActionSizer(); // Podría utilizarse un sizerBox en lugar de un gridBag...

		this->gridBagSizer->Add(this->grid, wxGBPosition(0, 0), wxGBSpan(10, 2),wxGROW);
		this->gridBagSizer->Add(this->actionBag, wxGBPosition(0, 3), wxGBSpan(1, 1),wxGROW);
		this->setGridEvent(this->grid);
	}

	
	this->gridBagSizer->Fit(this);
	this->gridBagSizer->SetSizeHints(this);

	this->gridBagSizer->AddGrowableRow(1);this->gridBagSizer->AddGrowableCol(1);
}


void panelGrid::Reload(){
	cout << "Reload:: panelGrid"<< endl;
}
