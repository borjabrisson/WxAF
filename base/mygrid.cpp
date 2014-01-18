#include "mygrid.h"

MyGrid::MyGrid(wxWindow *parent, wxWindowID id, list<itemHeaderColumn> components, const wxPoint &pos, const wxSize &size, 
			   long style, const wxString &name)
	: wxGrid(parent,id, pos, wxSize(200,200), style,name){
// 		components representa los campos de la tabla a mostrar. Su id (first) será el id del campo y el otro valor
// 		el caption, o texto representativo.

	this->CreateGrid(0,components.size());// wxGridSelectRowsOrColumns

	this->EnableDragColMove();
    this->EnableEditing(false);
    this->EnableGridLines(true);
    this->SetDefaultCellFont( this->GetFont() );
    this->SetDefaultCellTextColour( this->GetForegroundColour() );   

	this->pushHeaders(components);
}

int MyGrid::numRowSelected(){
	return this->GetSelectedRows().GetCount();
}


void MyGrid::pushHeaders(list<itemHeaderColumn> headers){

	if (this->components.size() != 0){
		this->components.clear();
		this->resetGrid();
		this->AppendCols(headers.size());
	}
	list<itemHeaderColumn>::iterator it;
	int ind=0;
	for ( it=headers.begin() ; it != headers.end(); ind++,it++ ){
		this->components.insert(pair<string,int>((*it).fieldID,ind));
		this->SetColLabelValue(ind, wxString((*it).description.c_str(), wxConvUTF8) ) ;
	}
}

void MyGrid::resetGrid(){
	this->resetData();
	this->DeleteCols(0,this->GetNumberCols());
}

void MyGrid::resetData(){

	this->ClearGrid(); // limpia los datos almacenados en cada fila
	this->DeleteRows(0,this->GetNumberRows()); // elimina el identificador y registro de las filas existentes.
}


int MyGrid::MysetRow(unsigned int pos,map<string,string> row){
	map<string,string>::iterator it;
	int ind=0;
	for ( it=row.begin() ; it != row.end(); ind++,it++ ){
// 		SetCellValue (const wxString &val, int row, int col)
		this->SetCellValue(wxString( (*it).second.c_str(), wxConvUTF8), pos, this->components[(*it).first]);
	}
	return 0;
}

int MyGrid::MyinsertRow(unsigned int pos, map<string,string> row){
// 	bool 	InsertRows (int pos=0, int numRows=1, bool updateLabels=true)
	this->InsertRows(pos);
	this->MysetRow(pos,row);
	return 0;
}

int MyGrid::MyappendRow(map<string,string> row){
	int pos = this->GetNumberRows();
// 	AppendRows (int numRows=1, bool updateLabels=true)
	this->AppendRows();
	this->MysetRow(pos,row);
	return 0;
}


int MyGrid::pushDataSet(dataset data){
	int pos = 0;
	dataset::iterator it;
	for ( it=data.begin() ; it != data.end(); pos++,it++ ){
		this->MyappendRow((*it));
	}
	this->currentDataset = data;
	return pos;
}


map<string,string> MyGrid::MygetRow(unsigned int pos){
	dataset::iterator it;
	map<string,string> out ;
	if (pos < this->currentDataset.size()){
		unsigned int ind=0;
		for (it = this->currentDataset.begin(); ind < pos; ind++,it++);
		out = (*it);
	}
	return out;
}

map<string,string> MyGrid::MygetItemsRow(unsigned int pos,list<string> items){
	list<string>::iterator it;
	map<string,string> out, row;
	row = MygetRow(pos);
	for ( it=items.begin() ; it != items.end(); it++ ){
		out.insert(pair<string,string>( *it , row[(*it)]));
	}
	return out;	
}

void MyGrid::setColourRow(unsigned int row,const wxColour &colour){
	if (row >= 0){
		wxGridCellAttr *attr = new wxGridCellAttr(this->GetOrCreateCellAttr(row,1));
	// 	attr->SetBackgroundColour(wxColour(135,206,235)); //sky blue
		attr->SetBackgroundColour(colour);
		this->SetRowAttr(row,attr);
	}
}

void MyGrid::setColourRow(unsigned int row,unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
	this->setColourRow(row,wxColour(red,green,blue,alpha));
}



	
