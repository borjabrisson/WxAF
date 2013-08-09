
#include "panelCustomer.h"

panelCustomer::panelCustomer(wxWindow *parent, string id): myPanel(parent,id){
// 	this->Init();
}

void panelCustomer::BuildPage(){
	
	if (this->gridBagSizer == NULL){
		this->gridBagSizer = new wxGridBagSizer();
		this->actionBag = new wxGridBagSizer(); // Podría utilizarse un sizerBox en lugar de un gridBag...
		this->SetSizer(this->gridBagSizer);
		
		this->customerBag = new wxGridBagSizer();

		this->gridBagSizer->Add(this->customerBag, wxGBPosition(0, 0), wxGBSpan(3, 2),wxGROW);
		this->gridBagSizer->Add(this->actionBag, wxGBPosition(0, 3));
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


