// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html

#ifndef MY_GRID_H_
#define MY_GRID_H_

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/string.h>
#include <wx/object.h>
#include <wx/string.h>
#include <wx/colour.h>


#include "../configuracion/configuracion.h"

// http://www.cplusplus.com/reference/stl/

/*
 void 	SetColLabelValue (int col, const wxString &value)
 	Set the value for the given column label. 
 	
void 	SetCellValue (const wxString &val, int row, int col)

### Miscellaneous Functions

### Sorting support.
 void 	SetSortingColumn (int col, bool ascending=true)
 
 wxGrid::GetSelectedRows
 */
/*
# Generar los label col y guardar las posiciones.
# Insertar una fila usando map string string
 */
typedef map<string,string> row_type;
typedef list<row_type> dataset;



class MyGrid : public wxGrid
{
	
protected:
	map<string,int> components; // Asocia el ID de cada columna con su posición dentro del grid
	dataset currentDataset; // Contiene el dataset utilizado actualmente.
public:
	MyGrid(wxWindow *parent, wxWindowID id, list<itemHeaderColumn> components,const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, 
			   long style=wxWANTS_CHARS, const wxString &name=wxGridNameStr);
	//GetNumberCols
	int MysetRow(unsigned int pos,map<string,string> row);
	int MyinsertRow(unsigned int pos, map<string,string> row);
	int MyappendRow(map<string,string> row);

	int pushDataSet(dataset data);
	void pushHeaders(list<itemHeaderColumn> headers);
	int numRowSelected();

	void resetGrid();
	void resetData();

	void setColourRow(unsigned int row,const wxColour &colour);
	void setColourRow(unsigned int row,unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha=wxALPHA_OPAQUE);
	
// Nos permiten acceder a la información de la fila pos. También nos permite seleccionar elementos específicos de esa fila.	
	map<string,string> MygetRow(unsigned int pos);
	map<string,string> MygetItemsRow(unsigned int pos,list<string> items);
};

#endif /* MY_GRID_H_ */
