#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <exception>

enum Controls
{
	StaticLbl = -1,
	ComboDept = 1000,
	ComboAcc = 1100,
	EditVendor = 1200,
	EditRFC = 1300,
	EditConcept = 1400,
	EditDate = 1500,
	EditInvoice = 1600,
	EditAmount = 1700,
	CheckTax = 1800,
	CheckRet = 1900,
	buttonAgregar = 2000,
	ListBoxId = 2100,
};