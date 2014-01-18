#include "MyFrame.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : frameContainer(title,pos,size)

{
    menuBar = new wxMenuBar;
	//SetMenuBar(menuBar);

  
	menuFile = new wxMenu;

    menuFile->Append( ID_About, _T("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _T("E&xit") );

    menuBar->Append(menuFile, _T("&File") );

    SetMenuBar(menuBar);


	this->app =  &wxGetApp();



	SetStatusText( _("Welcome to wxWidgets!") );
// 	MyPopup* pop = new MyPopup;
// 	pop->BuildPop(this);
}

void MyFrame::buildFrame(){


	wxGridBagSizer* gridBagSizer = new wxGridBagSizer();
	this->SetSizer(gridBagSizer);

	wxNotebook* N1 =  new wxNotebook(this, wxID_ANY, wxDefaultPosition,wxDefaultSize, 0, _T("ID_NOTEBOOK1"));

// 	wxPanel* Panel1 = new wxPanel(N1, wxID_ANY, wxDefaultPosition, wxDefaultSize);

// 	myPanel *Panel1 = new myPanel(N1);

	procedPanel *Panel1 = new procedPanel(N1);

	this->panelito = Panel1;




	N1->AddPage(Panel1, _("gridd"), true);

	pruebaPanel *PanelPrueba = new pruebaPanel(N1);


	PanelPrueba->setApp(this->app);
	N1->AddPage(PanelPrueba, _("prueba"), true);


	wxPanel* Panel2 = new wxPanel(N1, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	wxGridBagSizer* gridBagSizer2 = new wxGridBagSizer();
	Panel2->SetSizer(gridBagSizer2);



	gridBagSizer2->Add(100,30, wxGBPosition(0, 0),wxGBSpan(1, 1),	wxGROW);
	gridBagSizer2->Add(100,30, wxGBPosition(0, 2),wxGBSpan(1, 1),wxGROW);

	wxButton* b1 = new wxButton(Panel2, wxID_ANY, wxT("One (0,0)"));
	gridBagSizer2->Add(b1, wxGBPosition(0, 1),wxGBSpan(1, 1),	wxGROW);

	wxButton* b2 = new wxButton(Panel2, wxID_ANY, wxT("Two (2,2)"));	gridBagSizer2->Add(b2, wxGBPosition(1, 1), wxGBSpan(1, 1),	wxGROW);

	wxButton* b3 = new wxButton(Panel2, wxID_ANY, wxT("Three (3,2)"));gridBagSizer2->Add(b3, wxGBPosition(2, 1),wxGBSpan(1, 1),	wxGROW);

	wxButton* b4 = new wxButton(Panel2, wxID_ANY, wxT("Four (3,3)"));gridBagSizer2->Add(b4, wxGBPosition(3, 1),wxGBSpan(1, 1),	wxGROW);

 	gridBagSizer2->AddGrowableRow(0);
 	gridBagSizer2->AddGrowableCol(1);

	gridBagSizer2->Fit(Panel2);
	gridBagSizer2->SetSizeHints(Panel2);
	N1->AddPage(Panel2, _("segundo"), true);


	gridBagSizer->Add(N1, wxGBPosition(0, 1), wxGBSpan(3, 3),	wxGROW);

	gridBagSizer->AddGrowableRow(1);gridBagSizer->AddGrowableCol(1);

	gridBagSizer->Fit(this);
	gridBagSizer->SetSizeHints(this);


	SetStatusText( _("Bienvenido!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	
    Close(true);
}

void MyFrame::OnClick(wxCommandEvent& WXUNUSED(event))
{

}

// int translate_paint(list<field_type> registro){
// 	list<field_type>::iterator it_list;
// 	field_type row;
// 	field_type::iterator it_row;
// 	for ( it_list=registro.begin() ; it_list != registro.end(); it_list++ ){
// 			row = (*it_list);
// 			for ( it_row=row.begin() ; it_row != row.end(); it_row++ ){
// 					cout << (*it_row).first << " = " <<(*it_row).second << " || ";
// 			}
// 			cout << endl;
// 	}
// 	return 0;
// }




void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	cout << "El valor del select:" << endl;
// 	cout << this->ctr.select(this->panelito->qry) << endl;
wxGetApp().attr= "don jose";
// 	MyApp &app =  wxGetApp();
	cout << "Valor de la aplicacion "<< this->app->attr << endl;
// 	MYSQL *myData;
	list<string> order;
	list<field_type> record;
	order.push_front("telefono");
	order.push_front("N_Factura");
	

	sgbd_conector obj;// = new sgbd_conector();
	obj.query("test","select N_Factura,telefono  from prueba_record",order,record);
// 	translate_paint(record);
	
	this->panelito->grid->pushDataSet(record);
	cout << "!!!Fin de la aplicacion World!!!" << endl; // prints !!!Hello World!!!
// 	this->Disable();
}       
