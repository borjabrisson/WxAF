
#include "panelCustomer.h"

panelCustomer::panelCustomer(wxWindow *parent, string id): myPanel(parent,id){
// 	this->Init();
}

void panelCustomer::BuildPage(){
	
	if (this->gridBagSizer == NULL){
		this->gridBagSizer = new wxGridBagSizer();
		this->SetSizer(this->gridBagSizer);
		
		this->customerBag = new wxGridBagSizer();
		this->actionBag = buildActionSizer(); // Podría utilizarse un sizerBox en lugar de un gridBag...

		this->gridBagSizer->Add(this->customerBag, wxGBPosition(0, 0), wxGBSpan(3, 2),wxGROW);
		this->gridBagSizer->Add(this->actionBag, wxGBPosition(0, 3));
	}
	this->gridBagSizer->Fit(this);
	this->gridBagSizer->SetSizeHints(this);

	this->gridBagSizer->AddGrowableRow(1);this->gridBagSizer->AddGrowableCol(1);
}


