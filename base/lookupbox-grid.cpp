// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "lookupbox.h"
// #include "hello-wx2.cpp"

MyLookUpBox::MyLookUpBox(wxWindow *parent): wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize){
	this->labelSize = 100;
	this->InputSize= 100;
	this->heightRow= 30;
	
	this->mode = "card";
}

MyLookUpBox::~MyLookUpBox(){
	if (this->panel != NULL) delete this->panel;
}

int MyLookUpBox::AddComponent(string id,string label, bool lookup){
	this->labels.insert(pair<string,string>(id,label));

	itemCard item;
	item.input = NULL;//new wxTextCtrl(this,wxNewId(),_T(""),wxPoint(this->labelSize,this->heightRow), wxSize(this->InputSize,this->heightRow));
	item.btn = NULL;
	item.lookup = false;
	if(lookup){
		item.lookup = true;
// 		item.btn =  new wxButton(this, wxNewId(), _("#"), wxPoint(this->labelSize+this->InputSize,this->heightRow),  wxSize(this->heightRow,this->heightRow));
// 		this->lookup.insert(pair<int,string>(item.btn->GetId(),id));
	}
	this->inputs.insert(pair<string,itemCard>(id,item));
	
	return 0;
}

wxButton* MyLookUpBox::GetLookup(string id){
	if(this->inputs[id].btn != NULL){
		return this->inputs[id].btn;
	}
	return NULL;
}



void MyLookUpBox::GetSize(int &widthBox,int  &heightBox){
	
	if (this->lookup.size()!=0){
		widthBox = this->labelSize + this->InputSize + 35+ 50; 
	}
	else{
		widthBox = this->labelSize + this->InputSize + 50;		
	}
	heightBox = this->labels.size()*this->heightRow+100;
}

int MyLookUpBox::ChangeMode(){
	
	if(this->mode == "lookup"){
		this->mode = "card";
		
		this->SetSizer(this->BagCard,false);

		this->BagGrig->ShowItems(false);
		this->BagCard->ShowItems(true);
		
		this->BagCard->Fit(this);
		this->BagCard->SetSizeHints(this);
	
		
		return 1;
	}
	// Se encuentra en el modo card
	this->mode = "lookup";

	
	this->SetSizer(this->BagGrig,false);

	this->BagCard->ShowItems(false);
	this->BagGrig->ShowItems(true);
	
	this->BagGrig->Fit(this);
	this->BagGrig->SetSizeHints(this);
	
	
	
	return 2;
	
}

int MyLookUpBox::BuildBox(int widthBox , int heightBox){
	
// 	this->pop= new MyPopup(parent, wxID_ANY,_T("Emergenteee"),wxDefaultPosition,wxSize(widthBox,heightBox), wxDEFAULT_DIALOG_STYLE  |  wxRESIZE_BORDER);
	
	this->BuildCardBox();
 	this->BuildListBox(widthBox,heightBox);
	
	// asignamos el grid perteneciente al modo card y ocultamos los items del modo lista.

// 	this->SetSizer(this->BagCard);
// 	this->BagCard->Fit(this);
// 	this->BagCard->SetSizeHints(this);
	
	
//  	new wxButton(this->panel, wxNewId(), _("#"),  wxPoint(widthBox-(widthBox/2),heightBox-50),  wxSize(this->heightRow,this->heightRow));


	return 0;
}

int MyLookUpBox::BuildCardBox(){
	
	this->BagCard = new wxGridBagSizer();

	this->SetSizer(this->BagCard);
	this->BagCard->Fit(this);
	this->BagCard->SetSizeHints(this);
	
	
// 	this->gridBagSizer2->Add(this->grid2, wxGBPosition(0, 0), wxGBSpan(3, 2),	wxGROW);
// 	this->gridBagSizer2->Add(this->b2, wxGBPosition(0, 3), wxGBSpan(1, 2),	wxGROW);
	
	this->BagCard->Add(100,30, wxGBPosition(0, 0),wxGBSpan(1, 1),	wxGROW);

	this->BagCard ->Add(100,30, wxGBPosition(0, 2),wxGBSpan(1, 1),wxGROW);
	
// 	this->BagCard->AddGrowableRow(1);this->BagCard->AddGrowableCol(1);	

// 	wxStaticBoxSizer *box = new wxStaticBoxSizer(wxVERTICAL,this,_T("Don jose"));
	wxBoxSizer *box = new wxBoxSizer(wxVERTICAL);
	wxGridBagSizer *boxH;// = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *tag;
	map<string,string>::iterator it;
	int ind=1;

	for ( it=this->labels.begin() ; it != this->labels.end(); ind++,it++ ){
		boxH = new wxGridBagSizer();
		boxH->Fit(this);
		boxH->SetSizeHints(this);
		boxH->AddGrowableRow(0);			boxH->AddGrowableCol(0);
		
		tag = new  wxStaticText (this, wxID_ANY, wxString( (*it).second.c_str(), wxConvUTF8), wxDefaultPosition, wxSize(this->labelSize,this->heightRow));

// 		tag = new  wxStaticText (this, wxID_ANY, wxString( (*it).second.c_str(), wxConvUTF8), wxPoint(0,(this->heightRow)*ind), wxSize(this->labelSize,this->heightRow));
		
		
// 		this->inputs[(*it).first] = new wxTextCtrl(this->panel,wxNewId(),_T(""), wxPoint(this->labelSize,ind*this->heightRow), wxSize(this->InputSize,this->heightRow));
		
		boxH->Add(tag,wxGBPosition(0, 0), wxGBSpan(1, 1),	wxGROW);
		
		this->inputs[(*it).first].input = new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(this->InputSize,this->heightRow));

// 		this->inputs[(*it).first].input = new wxTextCtrl(this,wxNewId(),_T(""),wxPoint(this->labelSize,(this->heightRow)*ind), wxSize(this->InputSize,this->heightRow));
		
		boxH->Add(this->inputs[(*it).first].input,wxGBPosition(0, 1), wxGBSpan(1, 1),	wxGROW);
		
		if(this->inputs[(*it).first].lookup){
			this->inputs[(*it).first].btn =  new wxButton(this, wxNewId(), _("#"), wxDefaultPosition,  wxSize(this->heightRow,this->heightRow));

// 			this->inputs[(*it).first].btn =  new wxButton(this, wxNewId(), _("#"), wxPoint(this->labelSize+this->InputSize,(this->heightRow)*ind),  wxSize(this->heightRow,this->heightRow));
			
			this->lookup.insert(pair<int,string>(this->inputs[(*it).first].btn->GetId(),(*it).first));

			boxH->Add(this->inputs[(*it).first].btn,wxGBPosition(0, 2), wxGBSpan(1, 1),	wxGROW);

			this->Connect(this->inputs[(*it).first].btn->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyLookUpBox::OnClick) );
		}
		else{
			boxH->Add(new  wxStaticText (this, wxID_ANY,  _(" "), wxDefaultPosition,  wxSize(this->heightRow,this->heightRow)),wxGBPosition(0,2), wxGBSpan(1, 1),	wxGROW);
// 			boxH->AddSpacer(10);
		}

// 		box->Add(boxH,wxSHAPED|wxEXPAND);
		this->BagCard->Add(boxH, wxGBPosition(ind, 1), wxGBSpan(1, 1),	wxGROW);

		
// 		this->BagCard->Add(boxH, wxGBPosition(ind, 1), wxGBSpan(1, 1),	wxGROW);
	}
	this->BagCard->Add(100,30, wxGBPosition(ind, 1),wxGBSpan(1, 1),	wxGROW);
	this->BagCard->AddGrowableRow(0);this->BagCard->AddGrowableCol(0);
// 	this->BagCard->Add(box, wxGBPosition(0, 0), wxGBSpan(1, 1),	wxGROW);
	return 0;
}

int MyLookUpBox::BuildListBox(int widthBox, int heightBox){

// 	wxStaticBoxSizer *boxgrid = new wxStaticBoxSizer(wxVERTICAL,this->panel,_T("PEPE"));
	
	map<string,string> cols;
	cols.insert(pair<string,string>("first","Primeró"));
	cols.insert(pair<string,string>("second","segundño"));
	cols.insert(pair<string,string>("third","segundo"));
	
// 	this->grid = new MyGrid(this->panel, wxID_ANY, cols,wxPoint(0,0), wxSize(widthBox-100,heightBox-100)); 	this->grid->Show();
	
	this->BagGrig = new wxGridBagSizer();
// 	this->SetSizer(this->BagGrig,false);

	this->grid = new wxGrid(this, wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	
	this->BagGrig->Add(this->grid, wxGBPosition(0, 0), wxGBSpan(3, 2),wxGROW);
	this->BagGrig->AddGrowableRow(0);	this->BagGrig->AddGrowableCol(0);

	this->BagGrig->Fit(this);
	this->BagGrig->SetSizeHints(this);

	this->BagGrig->ShowItems(false);

	return 0;
}

void MyLookUpBox::OnClick(wxCommandEvent& event){
	cout << this->lookup[event.GetId()] << endl;
	cout << "On clik!!" << endl;
	this->ChangeMode();
}

int MyLookUpBox::SetWidth(string type, int width){
	return 0;
	
}