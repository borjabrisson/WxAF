#ifndef MyLookUpBox_H_
#define MyLookUpBox_H_
#include <wx/wx.h>

#include <wx/button.h>
// #include <wx/frame.h>

#include <wx/string.h>
// #include <wx/object.h> 
#include <wx/textctrl.h>

// #include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>

#include "mygrid.h"



#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/string.h>

#include <map>
#include <iostream>
#include <string>
#include <list>

#include "DialogBase.h"

using namespace std;

class MyLookUpBox : public wxPanel
{
protected:
	typedef struct itemCard_struct{
		wxTextCtrl*		input;
		wxButton*	btn;
		bool lookup;
	}itemCard;
	
	map<string,itemCard> inputs;
	map<int,string> lookup;
	map<string,string> labels;
	
	wxPanel *panel;

	MyGrid *grid;
	
	int labelSize;
	int InputSize;
	int heightRow;

	wxButton* acept;
	wxButton* cancel;
	
	wxGridBagSizer* BagGrig;
	wxGridBagSizer* BagCard;

	string mode;
	DialogBase *parent;
public:
	MyLookUpBox(wxWindow *parent);
	
	~MyLookUpBox();
	
	int AddComponent(string id,string label, bool lookup=false);
	wxButton* GetLookup(string id);
	
	void OnClick(wxCommandEvent& event);
	
	int BuildBox(int widthBox=300 , int heightBox=300);
	
	int SetWidth(string type="label", int width=50);
	
	void GetSize(int &widthBox,int  &heightBox);
	int ChangeMode();

	void SetParentEvent(DialogBase *parent);

	map<string,string> getInputsValue();

	void setValue(string id, string value);
// 	int Hide();
// 	int Show();
// 	virtual void OnLoad();
protected:
	typedef map<string,string> row_type;
	typedef list<row_type> dataset;

	void OnAcept(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);

	int BuildCardBox();
	
	int BuildListBox(int widthBox, int heightBox);
};

#endif /* MyLookUpBox_H_ */