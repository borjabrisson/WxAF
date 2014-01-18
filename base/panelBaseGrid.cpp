
#include "panelBaseGrid.h"

panelBaseGrid::panelBaseGrid(wxWindow *parent, string id): myPanel(parent,id){
// 	this->Init();
}


void panelBaseGrid::handleGridEvent(wxGridEvent& event){
// 	cout << "panelBaseGrid: " << event.GetEventType() << " ::: "<< endl;
	stringstream stream;
	stream << event.GetEventType();
	push_Debug("panelBaseGrid::handleGridEvent. "+ stream.str() );
	switch (event.GetEventType()){
		case EVT_GRID_CELL_LEFT_CLICK:
				this->OnLeftClick(event);
			break;
		case EVT_GRID_CELL_LEFT_DCLICK:
				this->OnLeftDbClick(event);
			break;
		case EVT_GRID_CELL_RIGHT_CLICK:
				this->OnRightClick(event);
			break;
		case EVT_GRID_CELL_RIGHT_DCLICK:
				this->OnRightDbClick(event);
			break;
		case EVT_GRID_COL_MOVE:	{
// 			int columnaID = event.GetCol();
// 			int newPos = this->grid->GetColPos(columnaID);
// 			push_Debug("handleGridEvent.columna utilizada "+ (string)columnaID );
// 			push_Debug("handleGridEvent.Posición actual "+ (string)newPos );
// 			if (newPos != -1)	this->grid->SetColPos(columnaID,newPos);
		}
			break;
		default:
			push_Error("panelBaseGrid::handleGridEvent. Evento no controlado");
		break;
	}
}

list<itemHeaderColumn> panelBaseGrid::headerGrid(){
	list<itemHeaderColumn> header;
	return header;
}

void panelBaseGrid::setGridEvent(MyGrid *grid){

	this->Connect(grid->GetId(),wxEVT_GRID_CELL_LEFT_DCLICK,wxGridEventHandler(panelBaseGrid::handleGridEvent));
	this->Connect(grid->GetId(),wxEVT_GRID_CELL_LEFT_CLICK,wxGridEventHandler(panelBaseGrid::handleGridEvent));

	this->Connect(grid->GetId(),wxEVT_GRID_CELL_RIGHT_DCLICK,wxGridEventHandler(panelBaseGrid::handleGridEvent));
	this->Connect(grid->GetId(),wxEVT_GRID_CELL_RIGHT_CLICK,wxGridEventHandler(panelBaseGrid::handleGridEvent));
	
	this->Connect(grid->GetId(),wxEVT_GRID_COL_MOVE,wxGridEventHandler(panelBaseGrid::handleGridEvent));

}

void panelBaseGrid::OnLeftClick(wxGridEvent& event){
	this->grid->SelectRow(event.GetRow());
}

bool panelBaseGrid::checkSelectedRowsNumber(){
	int numRow= this->grid->numRowSelected();
	if (numRow == 1){
			return true;
	}
	else{
		string msg;
		if (numRow == 0) msg = "Seleccione un elemento";
		else		   msg = "No puede seleccionar más de un elemento";
		this->showMessage("Atención",msg);
	}
	return false;
}


