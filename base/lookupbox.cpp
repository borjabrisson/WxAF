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

	this->acept = new wxButton(this, wxNewId(), _("Aceptar"), wxDefaultPosition,  wxSize(this->InputSize,this->heightRow));
	this->cancel = new wxButton(this, wxNewId(), _("Cancelar"), wxDefaultPosition,  wxSize(this->InputSize,this->heightRow));


	this->Connect(this->acept->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyLookUpBox::OnAcept) );
	this->Connect(this->cancel->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyLookUpBox::OnCancel) );
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
	if (this->mode != "lookup"){
		widthBox = this->labelSize + 2*this->InputSize;
		if (this->lookup.size()!=0){
			widthBox += this->heightRow;
		}
		heightBox = (this->labels.size()+4)*this->heightRow;
	}
	else{
		widthBox = 600;
		heightBox = 400;
	}
}

int MyLookUpBox::ChangeMode(){
	
	if(this->mode == "lookup"){
		this->mode = "card";

		this->parent->ChangeMode(false);

		this->SetSizer(this->BagCard,false);

		
		this->BagGrig->ShowItems(false);
		this->BagCard->ShowItems(true);
		
		this->BagCard->Fit(this);
		this->BagCard->SetSizeHints(this);
	
		return 1;
	}
	// Se encuentra en el modo card
	this->mode = "lookup";

	this->parent->ChangeMode(true);

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

	this->BagCard->ShowItems(true);
	
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
	
	this->BagCard->Add(this->InputSize/2,30, wxGBPosition(0, 0),wxGBSpan(1, 1));		this->BagCard->Add(this->InputSize/2,30, wxGBPosition(0, 2),wxGBSpan(1, 1));
	
	wxBoxSizer *boxH;// = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *tag;
	map<string,string>::iterator it;
	int ind=1;

	for ( it=this->labels.begin() ; it != this->labels.end(); ind++,it++ ){
		boxH = new wxBoxSizer(wxHORIZONTAL);
		tag = new  wxStaticText (this, wxID_ANY, wxString( (*it).second.c_str(), wxConvUTF8), wxDefaultPosition, wxSize(this->labelSize,this->heightRow));
		boxH->Add(tag);
		
		this->inputs[(*it).first].input = new wxTextCtrl(this,wxNewId(),_T(""),wxDefaultPosition, wxSize(this->InputSize,this->heightRow));//,wxTE_PASSWORD);
		boxH->Add(this->inputs[(*it).first].input);
		
		if(this->inputs[(*it).first].lookup){
			this->inputs[(*it).first].btn =  new wxButton(this, wxNewId(), _("#"), wxDefaultPosition,  wxSize(this->heightRow,this->heightRow));

			this->lookup.insert(pair<int,string>(this->inputs[(*it).first].btn->GetId(),(*it).first));

			boxH->Add(this->inputs[(*it).first].btn);
			this->Connect(this->inputs[(*it).first].btn->GetId(),wxEVT_COMMAND_BUTTON_CLICKED,  wxCommandEventHandler(MyLookUpBox::OnClick) );
		}
		else{
			boxH->Add(new  wxStaticText (this, wxID_ANY,  _(" "), wxDefaultPosition, wxSize(this->heightRow,this->heightRow)));
// 			boxH->AddSpacer(10);
		}

		this->BagCard->Add(boxH, wxGBPosition(ind, 1), wxGBSpan(1, 1),	wxGROW);
	}
	this->BagCard->Add(100,30, wxGBPosition(ind, 1),wxGBSpan(1, 1),	wxGROW);
	boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(this->acept);					boxH->Add(new  wxStaticText (this, wxID_ANY,  _(" "), wxDefaultPosition, wxSize(this->heightRow,this->heightRow)));
	boxH->Add(this->cancel);

	this->BagCard->Add(boxH, wxGBPosition(ind+1, 1),wxGBSpan(1, 1),	wxGROW);
	this->BagCard->Add(100,30, wxGBPosition(ind+2, 1),wxGBSpan(1, 1),	wxGROW);
	
	this->BagCard->AddGrowableRow(0);this->BagCard->AddGrowableCol(1);
// 	this->BagCard->Add(box, wxGBPosition(0, 0), wxGBSpan(1, 1),	wxGROW);
	return 0;
}

int MyLookUpBox::BuildListBox(int widthBox, int heightBox){

// 	wxStaticBoxSizer *boxgrid = new wxStaticBoxSizer(wxVERTICAL,this->panel,_T("PEPE"));
	
	list<itemHeaderColumn> cols;
// 	cols.insert(pair<string,string>("first","Primeró"));
// 	cols.insert(pair<string,string>("second","segundño"));
// 	cols.insert(pair<string,string>("third","segundo"));
// 
// 	map<string,string> row;
// 	row.insert(pair<string,string>("first","Valor"));
// 	row.insert(pair<string,string>("third","Valor 3"));
	
	this->BagGrig = new wxGridBagSizer();
	this->BagGrig->Fit(this);
	this->BagGrig->SetSizeHints(this);
// 	this->SetSizer(this->BagGrig,false);
	

	this->grid = new MyGrid(this, wxID_ANY, cols); /*	this->grid->Show();*/

// 	this->grid->MyappendRow(row);
// 	row["first"] = "2";
// 	this->grid->MyappendRow(row);
// 	row["first"] = "3";
// 	this->grid->MyappendRow(row);
	
// 	this->grid = new wxGrid(this, wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	this->BagGrig->Add(this->grid, wxGBPosition(0, 0), wxGBSpan(3, 3),wxGROW);


	wxBoxSizer* boxH = new wxBoxSizer(wxHORIZONTAL);
	boxH->Add(new  wxStaticText (this, wxID_ANY,  _(" "), wxDefaultPosition, wxSize(200,this->heightRow)));
	boxH->Add(this->acept);
	boxH->Add(new  wxStaticText (this, wxID_ANY,  _(" "), wxDefaultPosition, wxSize(this->heightRow,this->heightRow)));
	boxH->Add(this->cancel);

	this->BagGrig->Add(boxH, wxGBPosition(3, 1));
	this->BagGrig->AddGrowableRow(0);	this->BagGrig->AddGrowableCol(2);

	this->BagGrig->ShowItems(false);

	return 0;
}

void MyLookUpBox::OnClick(wxCommandEvent& event){
	cout << this->lookup[event.GetId()] << endl;
	cout << "On clik!!" << endl;
	list<itemHeaderColumn> headers;
	list<row_type> dataset;
	dataset = this->parent->getLookupQuery(this->lookup[event.GetId()],headers);
	
	this->grid->pushHeaders(headers);
	this->grid->pushDataSet(dataset);
	this->ChangeMode();
}

void MyLookUpBox::OnCancel(wxCommandEvent& event){
	cout << "Cancelt!!" << endl;

	if (this->mode == "lookup") 	this->ChangeMode();
	else this->parent->HandleEvent("cancel");
}

void MyLookUpBox::OnAcept(wxCommandEvent& event){
	cout << "Acept!!" << endl;
	if (this->mode == "lookup"){
		
		cout << this->grid->GetSelectedRows().GetCount() << endl;
		wxArrayInt array;
		array = this->grid->GetSelectedRows();
		int size = array.GetCount();
		if ((size>0)  && (size<2)){
			cout << "Fila seleccionada: " << array[0] << endl;
			map<string,string> temp;
			temp = this->grid->MygetRow(array[0]);
			cout << "Valor del primero en ese caso: " << temp["first"] << endl;
			this->parent->setValues(temp);
			this->ChangeMode();
		}
		else{
			string msg;
			if (size == 0) msg = "Seleccione un elemento";
			else		   msg = "No puede seleccionar más de un elemento";
			wxMessageBox(  wxString( msg.c_str(), wxConvUTF8),_("Atención"),      wxOK|wxICON_INFORMATION, this );
		}
	}
	else this->parent->HandleEvent("acept");
}

map<string,string> MyLookUpBox::getInputsValue(){
	map<string,string> out;
	map<string,itemCard>::iterator it;
	wxString value;
	string str;
	for(it=this->inputs.begin(); it != this->inputs.end(); it++){
		value = (*it).second.input->GetValue();
		str = (const char*)value.mb_str();
		out.insert(pair<string,string>((*it).first, str));
	}
	return out;	
}

void MyLookUpBox::setValue(string id, string value){
	if(this->inputs.count(id) > 0){
		this->inputs[id].input->SetValue( wxString( value.c_str(), wxConvUTF8));
	}
}


int MyLookUpBox::SetWidth(string type, int width){
	return 0;
}


void MyLookUpBox::SetParentEvent(DialogBase *parent){
	this->parent = parent;
}