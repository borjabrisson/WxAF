
#ifndef PopUp_H_
#define PopUp_H_

#include <wx/wx.h>
#include <wx/panel.h>

#include <wx/button.h>
#include <wx/frame.h>

#include <wx/string.h>
#include <wx/object.h> 
#include <wx/textctrl.h>

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>

#include "lookupbox.h"
#include "DialogBase.h"
#include "mypanel.h"


#include <map>
#include <iostream>
#include <string>
#include <list>

using namespace std;



class MyPopup : public  DialogBase
{
	
public:
	MyLookUpBox *box;
	myPanel *parent;
public:
	MyPopup();
	~MyPopup();

	int SetGrid(map<string,string> components);
	
	int ShowGrid();
	
	int BuildPop(myPanel *parent);
	
	virtual int ChangeMode(bool lookup=false);
	void OnClick(wxCommandEvent& event);

	void HandleEvent(string action);
	
	virtual void createAction();

	void setValues(map<string,string> values);
};

#endif /* PopUp_H_ */