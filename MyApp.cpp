#include "MyApp.h"

void MyApp::createframeContainer(){
	 this->frame = new MyFrame( _("AGOSAL"), wxPoint(50, 50),wxSize(100, 900));

    this->frame->Connect( ID_Quit, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnQuit );
    this->frame->Connect( ID_About, wxEVT_COMMAND_MENU_SELECTED,
                    (wxObjectEventFunction) &MyFrame::OnAbout );



// 	this->frame = frame;
}


void MyApp::loadControllers(){
	this->ctr = new myCtr();
	this->ctr->setConector(this->conector);

	setController(calendarioCtr,"CalendarioCtr");
	setControllerPage("CalendarioCtr","calendar");

	setController(MensajeriaCtr,"MensajeriaCtr");
	setControllerPage("MensajeriaCtr","mensajes");

	this->ctrContainer["CalendarioCtr"]->setConector(this->conector);
	this->ctrContainer["MensajeriaCtr"]->setConector(this->conector);
}


// void MyApp::Login(){}


// void MyApp::AceptLogin(wxCommandEvent& WXUNUSED(event)){}

// void MyApp::CancelLogin(wxCommandEvent& WXUNUSED(event)){}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : frameContainer(title,pos,size)

{
	this->Init();
}

void MyFrame::Init()
{
	this->app =  &wxGetApp();
	frameContainer::Init();
}

void MyFrame::buildFrame(){

	wxMenu* menuFile = new wxMenu;

    menuFile->Append( ID_About, _T("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _T("E&xit") );

    this->menuBar->Append(menuFile, _T("&File") );


	setPage(procedPanel,"primero","caption");
	setPage(pruebaPanel,"segundo","Prueba");

	
	setPage(CalendarioPage,"calendar","Calendario");

	setPage(MensajeriaPage,"mensajes","Mensajes");


// 	setPage(panelCalendar,"calendar2","Calendario 2");

	
// 	pruebaPanel *PanelPrueba = new pruebaPanel(this->note);
// 	this->addPage("segundo","Prueba",PanelPrueba);

// 	myPanel *Panel1 = new procedPanel(this->note);
// 	this->addPage("primero","Primero",Panel1);

// 	panelCustomer *customer = new panelCustomer(this->note);
// 	this->addPage("customer","Customer",customer);

	SetStatusText( _("Bienvenido!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}



void MyFrame::OnClick(wxCommandEvent& WXUNUSED(event)){}


void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxFrame *framisito = new wxFrame(this,wxNewId(),_T("PEPe"));
	wxCalendarCtrl* aux= new wxCalendarCtrl (framisito, wxNewId());

	wxGridBagSizer* gridBagSizer = new wxGridBagSizer();

	gridBagSizer->Add(aux, wxGBPosition(0, 0), wxGBSpan(10, 2),wxGROW);
	gridBagSizer->Fit(framisito);
	gridBagSizer->SetSizeHints(framisito);

	gridBagSizer->AddGrowableRow(1);gridBagSizer->AddGrowableCol(1);

	framisito->Show(true);

	
// 	cout << "El valor del select:" << endl;
// // 	cout << this->ctr->select(this->panelito->qry) << endl;
// wxGetApp().attr= "don jose";
// // 	MyApp &app =  wxGetApp();
// 	cout << "Valor de la aplicacion "<< this->app->attr << endl;
// // 	MYSQL *myData;
// 	list<string> order;
// 	list<field_type> record;
// 	order.push_front("telefono");
// 	order.push_front("N_Factura");
// 	
// 
// 	sgbd_conector obj;// = new sgbd_conector();
// 	obj.query("test","select N_Factura,telefono  from prueba_record",order,record);
// // 	translate_paint(record);
// 	
// 	this->panelito->grid->pushDataSet(record);
// 	cout << "!!!Fin de la aplicacion World!!!" << endl; // prints !!!Hello World!!!
// // 	this->Disable();
}       
