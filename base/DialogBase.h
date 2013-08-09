
#ifndef DialogBase_H_
#define DialogBase_H_

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

#include "../configuracion/configuracion.h"


class DialogBase : public  wxDialog
{
protected:
	typedef map<string,string> row_type;
typedef list<row_type> dataset;
	string lookup;
	
public:
	DialogBase();
	~DialogBase();

	virtual int ChangeMode(bool lookup=false){return 0;}
	virtual void OnClick(wxCommandEvent& event){}
	virtual void HandleEvent(string action){}
	virtual list<row_type> getLookupQuery(string action,list<itemHeaderColumn> &header){ list<row_type> aux; return aux;}
	virtual void setValues(map<string,string> values){}
};

#endif /* DialogBase_H_ */