#ifndef MyLookUpBox_H_
#define MyLookUpBox_H_
#include <wx/wx.h>

#include <wx/button.h>

#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/datectrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/radiobox.h>

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

#include <wx/listctrl.h>

#include "DialogBase.h"

#ifdef wxVersion2_9
	#include <wx/timectrl.h>
#endif

using namespace std;

class MyLookUpBox : public wxPanel
{
protected:
	map<int,wxDateTime::Month> mounthCode;
	map<int,string> actionsEnable;
	MyGrid *grid;
	
	int labelSize, InputSize, heightRow, btnActionSize;
	wxGridBagSizer *BagGrid, *BagCard;

	string mode;
	DialogBase *parent;
public:
	MyLookUpBox(wxWindow *parent);
	~MyLookUpBox();
	
	int BuildBox(map<string, itemCard> &inputs,map<int, string> &lookupBtn,list<string> &orderItem,list<string> &actions,int widthBox=300 , int heightBox=300);
	int SetWidth(string type="label", int width=50);

	int ChangeMode();

	void setValue(int type,wxControl *obj, string value);
	string getValue(int type,wxControl *obj);

	void SetModeList();
	void SetModeCard();
	string getActionsID(int btnID);

protected:
	int BuildListBox(int widthBox, int heightBox);
	int BuildCardBox(map<string, itemCard> &inputs,map<int, string> &lookupBtn,list<string> &orderItem,list<string> &actions);

	wxGridBagSizer* CreateCardRow(wxStaticText* label,wxControl* input,wxButton* lookup);
	wxGridBagSizer* createSizerActions(list<string> &actions);

	wxControl* createInputCard(int type,int maxSize);
	wxStaticText* createLabelInput(string label);
};

#endif /* MyLookUpBox_H_ */
