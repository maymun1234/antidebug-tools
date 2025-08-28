



#include <iostream>
#include "settings.h"
#include "literal.h"
#include "globals.h"

using namespace std;

int licensCondition;

void Initvariables(void){
    licensCondition = 0;
}

void DefaultVariables(void){
    licensCondition = 10;
    cout << licensCondition << "\n";
}


//tüm global değişkenler ramde duracak.