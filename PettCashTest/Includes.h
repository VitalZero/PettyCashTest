#pragma once
#define _WIN32_WINNT 0X0601
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <exception>

// Data capture
#define STATICLB -1
#define EDDATESTART 1000
#define EDDATEEND	1010
#define EDWEEK 1020
#define CBDEPT 1030
#define EDVENDOR 1040
#define EDRFC 1050
#define EDCONCEPT 1060
#define EDINVDATE 1070
#define EDINVNUM 1080
#define EDAMOUNT 1090
#define CBACCOUNT 1100
#define EDTAX 1110
#define EDRET 1120
#define BTADD 1130
// Totals
#define EDTOTALREQ 1140
#define EDPENDRECV 1150
#define EDCASH 1160
#define EDPENDINV 1170
#define EDTOTALSUM 1180
#define EDLOAN 1190
#define EDTOTALASSIGNED 1200
#define EDDIFF 1210
// List
#define LSLIST 1220
// Menu
#define NEWMENU 2000
#define OPENMENU 2010
#define SAVEMENU 2020
#define SAVEASMENU 2030
#define PRINTMENU 2040
#define ADDDEPTMENU 2050
#define ADDACTMENU 2060
#define CFGMENU 2070
#define EXITMENU 2200