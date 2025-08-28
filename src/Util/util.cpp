#include "Common/settings.h"
#include "Common/globals.h"
#include "Common/literal.h"
#include "Security/AntiDebug/antidebug.h"
#include "Util/util.h"

int GetLicenseCondition(void){
    return licensCondition;
}

void SetLicenseCondition(int val){
    licensCondition = val;
}

void AntiDebugControl(){
    bool status;
    status = CheckProcessesNames();
    if(status)
        SetLicenseCondition(0);
    else
        SetLicenseCondition(1);

}

