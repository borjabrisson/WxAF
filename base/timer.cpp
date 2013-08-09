// hworld.cpp
// Version using dynamic event routing
// http://docs.wxwidgets.org/trunk/group__group__funcmacro__events.html
#include "timer.h"


timer::timer(skeletonApp *app){
	this->app = app;
}

timer::~timer(){}

void timer::Notify(){
	this->app->wakeUp(this->action);
}


bool timer::Start(int milliseconds,int action){
	this->period = milliseconds;
	this->action = action;
	return wxTimer::Start(milliseconds, false);
}

bool timer::Reset(){
	this->Stop();
	return this->Start();
}