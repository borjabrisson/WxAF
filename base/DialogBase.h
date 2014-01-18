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

typedef struct itemCard_struct {
	wxControl* input;
	wxButton* btn;
	string label;
	bool lookup;
	int minSize;
	int maxSize;
	int type;
	itemCard_struct() {
		minSize = 0;
		maxSize = -1;
		lookup = false;
	}
	;
} itemCard;

enum typeInputs {
	textInput = 0x0A,
	textAreaInput,
	dateInput,
	timeInput,
	booleanInput,
	optionInput
};
class DialogBase: public wxDialog {
protected:
	typedef map<string, string> row_type;
	typedef list<row_type> dataset;

	map<string, itemCard> inputs;
	map<int, string> lookupBtn;
	list<string> orderItem;
	list<string> actions;

	string lookup;
	map<string, string> curRecord;
public:
	DialogBase();
	~DialogBase();

	int AddComponent(string id,string label,int type=textInput, int maxSize=-1,int minSize=0, bool lookup=false);
	virtual int ChangeMode(bool lookup = false) {
		return 0;
	}

	virtual list<row_type> getLookupQuery(string action,
			list<itemHeaderColumn> &header) {
		list<row_type> aux;
		return aux;
	}
	virtual void setValues(map<string, string> values) {}
	map<string, string> getCurRecord() {
			return this->curRecord;
		}
	virtual void HandleEvent(string action) {}

	void OnLookUpBtn(wxCommandEvent& event);
	virtual void OnEventClick(wxCommandEvent& event) {}
protected:
	void showMessage(string msg,string header="Atención");
	void addAction(string action);
	virtual void OnAcept(wxCommandEvent& event) {}
	virtual void OnCancel(wxCommandEvent& event) {}


	void ClearAll();
	virtual void HandleLookupEvnt(string lookup){}
};

#endif /* DialogBase_H_ */
