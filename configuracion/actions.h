#ifndef ACTION_APP_H_
#define ACTION_APP_H_

#include <map>
#include <iostream>
#include <string>
#include <list>

using namespace std;

 enum Agosal_Base_Action{
	 ACT_getFilter=1,
	 ACT_setFilter,
	 ACT_onFilter
 };
 enum Agosal_Type_BlockComunicate{
	 BKCM_Action=21,
	 BKCM_Query,
	 BKCM_Filter
 };

 enum Agosal_Acton_Ctr_TO_View{
	 C2V_showList=131,
	 C2V_showMsg,
	 C2V_actionOK,
	 C2V_actionDeny
 };

 enum Agosal_Acton_View_TO_Ctr{
	 V2C_setFilter = 241,
	 V2C_onFilter
 };


#endif /* ACTION_APP_H_ */
