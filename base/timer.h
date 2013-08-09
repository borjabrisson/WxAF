
#ifndef TIMER_H_
#define TIMER_H_

#include "skeletonApp.h"
#include <wx/timer.h>



#include <map>
#include <iostream>
#include <string>
#include <list>

using namespace std;

class timer : public  wxTimer
{
	
private:
	skeletonApp *app;
	int period;
	int action;
public:
	timer(skeletonApp *app);
	~timer();

	void Notify();

	bool Start(int milliseconds=-1,int action=0);

	bool Reset();
	
};

#endif /* TIMER_H_ */