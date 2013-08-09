
#include "panelCalendar.h"

panelCalendar::panelCalendar(wxWindow *parent, string id): panelBaseGrid(parent,id){
// 	this->Init();
}

panelCalendar::~panelCalendar() {
	// TODO Auto-generated destructor stub

}


void panelCalendar::Init(){
	panelBaseGrid::Init();
	this->curDate.SetToCurrent();
}

void panelCalendar::handleCalendarEvent(wxCalendarEvent& event){
	wxDateTime date = event.GetDate();
	cout << "Entrooo: " << event.GetEventType() << " ::: "<< endl;
	switch (event.GetEventType()){
		case EVT_SEL_CHANGED:
				cout << "SEL_CHANGED:: " <<date.GetDay()<< endl;
				this->clearNotes();
				this->OnSel_Changed(date);
			break;
		case EVT_WEEKDAY_CLICKED:
				this->OnWeekday_Clicked(date);
				cout << "wxEVT_CALENDAR_WEEKDAY_CLICKED" << endl;
			break;
		case EVT_DOUBLECLICKED:
			cout << "wxEVT_CALENDAR_DOUBLECLICKED" << endl;
			this->OnDoubleClicked(date);
			break;
		case EVT_YEAR_CHANGED:
			cout << "wxEVT_CALENDAR_YEAR_CHANGED" << endl;
			this->clearNotes();
			this->OnYear_Changed(date);
			break;
		case EVT_MONTH_CHANGED:
			cout << "wxEVT_CALENDAR_MONTH_CHANGED" << endl;
			this->clearNotes();
			this->OnMonth_Changed(date);
			break;
		case EVT_DAY_CHANGED:
			cout << "wxEVT_CALENDAR_DAY_CHANGED" << endl;
			this->OnDay_Changed(date);
			break;
		
	}
	this->curDate = date;
}

// void panelCalendar::handleGridEvent(wxGridEvent& event){
// 	cout << "pepe"<< endl;
// 	cout << "Entrooo: " << event.GetEventType() << " ::: "<< endl;
// 
// }

void panelCalendar::clearNotes() {
	wxDateTime date = this->calendar->GetDate();//(1,wxDateTime::Feb,2004);
	
	for(int day=1; day <=31; day++){
		date.SetDay(day);
		this->calendar->SetAttr(day,STYLE_CLEAR_NOTE);
		if (!date.IsWorkDay()){
			cout << "Dia festivo:: " << day << endl;
			this->calendar->SetAttr(day,STYLE_HOLIDAYS);
		}
	}
}


void panelCalendar::addNotes(int day){
	this->calendar->SetAttr(day,STYLE_ADD_NOTE);
}

void panelCalendar::loadCalendarConfig(){

	wxDateTime datetime = wxDateTime::Today();
	this->calendar->SetDate(datetime);
	this->calendar->SetHolidayColours(wxColour(_T("red")), wxColour(_T("white")));


// 	string aux="21";
// 	this->addNotes(strToint(aux));
}

void panelCalendar::setCalendarEvent(wxCalendarCtrl *calendar){
	this->Connect(calendar->GetId(),wxEVT_CALENDAR_WEEKDAY_CLICKED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));
// 		this->Connect(calendar->GetId(),wxEVT_CALENDAR_SEL_CHANGED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));

	this->Connect(calendar->GetId(),wxEVT_CALENDAR_DOUBLECLICKED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));
	this->Connect(calendar->GetId(),wxEVT_CALENDAR_YEAR_CHANGED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));
	this->Connect(calendar->GetId(),wxEVT_CALENDAR_MONTH_CHANGED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));
	this->Connect(calendar->GetId(),wxEVT_CALENDAR_DAY_CHANGED,wxCalendarEventHandler(panelCalendar::handleCalendarEvent));
	
}

void panelCalendar::BuildPage(){
	
	if (this->gridBagSizer == NULL){
		this->gridBagSizer = new wxGridBagSizer();
		this->actionBag = new wxGridBagSizer(); // Podría utilizarse un sizerBox en lugar de un gridBag...
		this->SetSizer(this->gridBagSizer);
		this->calendar = new wxCalendarCtrl (this, wxNewId(),wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxCAL_SHOW_HOLIDAYS | wxCAL_MONDAY_FIRST,wxCalendarNameStr);

// 		this->picker = new wxDatePickerCtrl  (this, wxNewId(),wxDefaultDateTime,wxDefaultPosition,wxDefaultSize,wxDP_DEFAULT|wxDP_SHOWCENTURY);

// 		this->noteList = new MyGrid(this, wxNewId(),wxDefaultPosition,wxDefaultSize);//,wxLC_LIST | wxLC_SORT_ASCENDING | wxLC_HRULES | wxLC_VRULES);

		list<itemHeaderColumn> temp = headerGrid();//= this->headerGrid();
		this->noteList = new MyGrid(this, wxNewId(),temp,wxDefaultPosition,wxDefaultSize,wxDOUBLE_BORDER|wxWANTS_CHARS);
		this->grid= this->noteList;
		this->setCalendarEvent(this->calendar);
		this->setGridEvent(this->noteList);
		
// 		this->gridBagSizer->Add(this->picker, wxGBPosition(0, 0), wxGBSpan(1, 2),wxGROW);

		this->loadCalendarConfig();
		
		this->gridBagSizer->Add(this->calendar, wxGBPosition(0, 0), wxGBSpan(1, 2),wxGROW);
		
		this->gridBagSizer->Add(this->noteList, wxGBPosition(1, 0), wxGBSpan(10, 2),wxGROW);
		this->gridBagSizer->Add(this->actionBag, wxGBPosition(0, 3), wxGBSpan(2, 1),wxGROW);
	}
	
	this->gridBagSizer->Fit(this);
	this->gridBagSizer->SetSizeHints(this);

	map<int,wxButton*>::iterator it;
	int ind =1;
	for ( it=this->buttons.begin() ; it != this->buttons.end();ind++, it++ ){
		this->actionBag->Add((*it).second, wxGBPosition(ind, 0));
	}


	this->gridBagSizer->AddGrowableRow(1);this->gridBagSizer->AddGrowableCol(1);
}

