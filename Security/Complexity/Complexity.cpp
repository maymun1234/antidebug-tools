
#include "Complexity.h"
#include <stdio.h>
#include "../filehashcheck/filehashcheck.h"
#include "../../Common/helperFunctions.h"
#include <windows.h>
#include <iostream>
#include <ctime>

//değişkeni lisaans defterine
//buraaya bişi yapp
#define DURATION_COUNTER



bool CheckDurationBetweenMethods(){
    return true;
}


void CheckDuration(){
    std::time_t const result = std::time(nullptr);
  print_colored(true, "kirmizi konsol test");
  print_colored(true, std::asctime(std::localtime(& result)));
  //dnhf
}


void SaveDatatoRom(int val){
    val = int(DURATION_COUNTER); 
    return;
}