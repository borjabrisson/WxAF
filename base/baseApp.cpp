#include "baseApp.h"

// baseApp::baseApp(): skeletonApp(){}

bool baseApp::OnInit() {

	createframeContainer();

	this->frame->Show(true);
	SetTopWindow(this->frame);

	this->conector = new sgbd_conector();

	loadControllers();

// 	this->frame->Disable();
#ifdef Enable_login
	this->time = new timer(this);
// 		time->Start(Enable_login,0);
	this->Login();
#endif

#ifdef Enable_autoRefresh
// 		this->autoRefresh = new timer(this);
// 		this->autoRefresh->Start(Enable_autoRefresh,1);
#endif
// 	time->Start(10000);

	return true;
}

void baseApp::wakeUp(int action) {
	switch (action) {
	case 0: // login
		wxMessageBox(_("Timer Test"));
		this->Login();
		this->time->Stop();
		break;
	case 1: // auto refresh
		wxMessageBox(_("Refresh Test"));
		this->frame->RefreshData();
		this->autoRefresh->Reset();
		break;
	}
}

void baseApp::Login() {
	this->frame->Disable();

	this->popLogin = new wxDialog(this->frame, wxID_ANY, _T("Login"),
			wxDefaultPosition, wxSize(300, 120), wxDEFAULT_DIALOG_STYLE);
	int inputSize = 100, heightRow = 30;
	int xBase = 50, yBase = 15;

	new wxStaticText(this->popLogin, wxNewId(), _("Usuario: "),
			wxPoint(xBase, yBase), wxSize(inputSize, heightRow));
	new wxStaticText(this->popLogin, wxNewId(), _("Contraseña: "),
			wxPoint(xBase, yBase + heightRow), wxSize(inputSize, heightRow));

	this->userInput = new wxTextCtrl(this->popLogin, wxNewId(), _T(""),
			wxPoint(xBase + inputSize, yBase), wxSize(inputSize, heightRow));
	this->passInput = new wxTextCtrl(this->popLogin, wxNewId(), _T(""),
			wxPoint(xBase + inputSize, yBase + heightRow),
			wxSize(inputSize, heightRow), wxTE_PASSWORD);

	wxButton *acept = new wxButton(this->popLogin, wxNewId(), _("Aceptar"),
			wxPoint(xBase, yBase + 2 * heightRow),
			wxSize(inputSize, heightRow));
	wxButton *cancel = new wxButton(this->popLogin, wxNewId(), _("Cancelar"),
			wxPoint(xBase + inputSize, yBase + 2 * heightRow),
			wxSize(inputSize, heightRow));

	this->Connect(acept->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(baseApp::AceptLogin));
	this->Connect(cancel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(baseApp::CancelLogin));

	this->popLogin->Show();
}

void baseApp::AceptLogin(wxCommandEvent& WXUNUSED(event)) {
	this->time->Stop();

	wxString value = this->userInput->GetValue();
	string user = (const char*) value.mb_str();

	value = this->passInput->GetValue();
	string pass = (const char*) value.mb_str();

	push_Debug("Usuario: " + user);
	push_Debug("Pass: " + pass);

	int out = this->conector->setCredentials(user, pass);
	if (out == 0) {
		this->frame->Enable();
		this->frame->RefreshData();
		this->popLogin->Close();
	}
}

void baseApp::CancelLogin(wxCommandEvent& WXUNUSED(event)) {
	this->frame->Disable();
}

bool baseApp::sendAction(string idFrame, int action, map<string, string> data,
		map<string, string> key) {

	cout << "ID: " << idFrame << endl;
	cout << "Action: " << action << endl;

	cout << "data" << data["factura"] << endl;
	cout << "key" << key["factura"] << endl;
	if (this->ctrVSpanel.count(idFrame) != 0) {
		string ctr = this->ctrVSpanel[idFrame];
		if (this->ctrContainer.count(ctr) != 0) {
			return this->ctrContainer[ctr]->sendAction(idFrame, action, data,
					key);
		} else {
			cout << "segundo caso " << endl;
			this->msgError = "El frame " + idFrame
					+ " no posee ningún controlador asignado";
			return false;
		}
	}

	cout << "ultimo caso " << endl;
	this->msgError = "No se tiene registrado al frame: " + idFrame;
	return false;
	return this->ctr->sendAction(idFrame, action, data, key);
}

string baseApp::getMsgError(string idFrame) {
	return this->ctr->getMsgError();
	string out;
	if (this->ctrVSpanel.count(idFrame) != 0) {
		string ctr = this->ctrVSpanel[idFrame];
		if (this->ctrContainer.count(ctr) != 0) {
			out = this->ctrContainer[ctr]->getMsgError();
		} else {
			this->msgError = "El frame " + idFrame
					+ " no posee ningún controlador asignado";
		}
	}
	return out;
}

list<field_type> baseApp::select(string idFrame, int type,
		map<string, string> filter) {
	list<field_type> data;
	if (this->ctrVSpanel.count(idFrame) != 0) {
		string ctr = this->ctrVSpanel[idFrame];
		if (this->ctrContainer.count(ctr) != 0) {
			return this->ctrContainer[ctr]->select(idFrame, type, filter);
		} else {
			cout << "segundo caso " << endl;
			this->msgError = "El frame " + idFrame
					+ " no posee ningún controlador asignado";
			return data;
		}
	}
	return data;

}

map<string, string> baseApp::filter(string idFrame, int type,map<string, string> &filter) {
	map<string, string> data;
	if (this->ctrVSpanel.count(idFrame) != 0) {
		string ctr = this->ctrVSpanel[idFrame];
		if (this->ctrContainer.count(ctr) != 0) {
			return this->ctrContainer[ctr]->filter(idFrame, type, filter);
		} else {
			cout << "segundo caso " << endl;
			this->msgError = "El frame " + idFrame
					+ " no posee ningún controlador asignado";
			return data;
		}
	}
	return data;
}


Customcomunicate baseApp::sendAction(Customcomunicate block) {
	Customcomunicate response;
	if (this->ctrVSpanel.count(block.panelID) != 0) {
		string ctr = this->ctrVSpanel[block.panelID];
		if (this->ctrContainer.count(ctr) != 0) {
			response = this->ctrContainer[ctr]->ActionRequest(block);
		} else {
			cout << "segundo caso " << endl;
			this->msgError = "El frame " + block.panelID
					+ " no posee ningún controlador asignado";
			response.type = -2;
		}
	}
	return response;
}

