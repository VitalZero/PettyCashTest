#pragma once
#include "MainWindow.h"
#include <commdlg.h>
#include <fstream>
#include "resource.h"
#include "Settings.h"
#include "Account.h"
#include "Department.h"
#include <sstream>
#include "Utilities.h"
#include <shellapi.h>

MainWindow::MainWindow()
	:
	fileName(L""), mainMenu(nullptr), font(nullptr)
{
	// msgs
	msgHandler.Register(WM_CREATE, &MainWindow::OnCreate, this);
	msgHandler.Register(WM_DESTROY, &MainWindow::OnDestroy, this);
	msgHandler.Register(WM_CTLCOLORSTATIC, &MainWindow::OnCtlColorStatic, this);
	msgHandler.Register(WM_PAINT, &MainWindow::OnPaint, this);
	msgHandler.Register(WM_COMMAND, &MainWindow::OnCommand, this);
	// commands
	msgHandler.Bind(EXITMENU, &MainWindow::OnExit, this);
	msgHandler.Bind(NEWMENU, &MainWindow::OnNew, this);
	msgHandler.Bind(OPENMENU, &MainWindow::OnOpen, this);
	msgHandler.Bind(SAVEMENU, &MainWindow::OnSave, this);
	msgHandler.Bind(SAVEASMENU, &MainWindow::OnSaveAs, this);
	msgHandler.Bind(CFGMENU, &MainWindow::OnConfig, this);
	msgHandler.Bind(BTADD, &MainWindow::OnBtnAdd, this);
	msgHandler.Bind(PRINTMENU, &MainWindow::OnPrint, this);
	msgHandler.Bind(ADDACTMENU, &MainWindow::OnAddAccount, this);
	msgHandler.Bind(ADDDEPTMENU, &MainWindow::OnAddDept, this);
	msgHandler.Bind(ABOUTMENU, &MainWindow::OnAbout, this);
}

void MainWindow::Init()
{
	CreateControls();
	CreateMainMenu();
	ResetInvoiceFields();
	Load();

	RECT rc = { 0 };
	GetWindowRect(wnd, &rc);
	int menuHeight = GetSystemMetrics(SM_CYMENU);
	x = rc.left;
	y = rc.top;
	width = rc.right - rc.left;
	height = rc.bottom - rc.top + menuHeight;
	MoveWindow(wnd, x, y, width, height, TRUE);
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return msgHandler.Dispatch(wnd, msg, wparam, lparam);
}

BOOL CALLBACK MainWindow::SetChildWndFontProc(HWND wndChild, LPARAM font)
{
	SendMessage(wndChild, WM_SETFONT, (WPARAM)font, TRUE);
	return TRUE;
}

void MainWindow::ResetInvoiceFields()
{
	edVendor->SetText(L"");
	edRFC->SetText(L"");
	edConcept->SetText(L"");
	edInvDate->SetText(L"");
	edInvNum->SetText(L"");
	cbAccount->SetText(L"");
	edAmount->SetText(L"");
	edTax->SetText(L"");
	edRet->SetText(L"");
}

void MainWindow::ResetHeaderFields()
{
	edStartDate->SetText(L"");
	edEndDate->SetText(L"");
	edWeek->SetText(L"");
	cbDept->SetText(L"");
}

void MainWindow::ResetTotalFields()
{
	edTotalReq->SetText(L"0");
	edPendInv->SetText(L"0");
	edCash->SetText(L"0");
	edPendInv->SetText(L"0");

	edTotalSum->SetText(L"0");

	edPendRecv->SetText(L"0");
	edLoan->SetText(L"0");

	edDiff->SetText(L"0");
}

LRESULT MainWindow::OnCreate(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return 1;
}

LRESULT MainWindow::OnDestroy(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	DeleteObject(font);
	PostQuitMessage(0);
	return 0;
}

LRESULT MainWindow::OnCtlColorStatic(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	SetBkMode((HDC)wparam, TRANSPARENT);
	return (LRESULT)(HBRUSH)GetStockObject(NULL_BRUSH);
}

LRESULT MainWindow::OnPaint(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(wnd, &ps);

	RECT rcEdge;
	rcEdge.left = 95;
	rcEdge.right = 712;
	rcEdge.top = 63;
	rcEdge.bottom = 64;

	DrawEdge(hdc, &rcEdge, BDR_SUNKENINNER, BF_TOP);

	rcEdge.top = 168;
	rcEdge.bottom = 169;
	rcEdge.left = 11;

	DrawEdge(hdc, &rcEdge, BDR_SUNKENINNER, BF_TOP);

	rcEdge.right = 712;
	rcEdge.left = 470;
	rcEdge.top = 310;
	rcEdge.bottom = 311;

	DrawEdge(hdc, &rcEdge, BDR_SUNKENINNER, BF_TOP);

	EndPaint(wnd, &ps);
	return 0;
}

LRESULT MainWindow::OnCommand(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (HIWORD(wparam) == EN_KILLFOCUS)
	{
		OnEnUpdate((UINT)LOWORD(wparam));
	}
	else
	{
		msgHandler.Dispatch(LOWORD(wparam));
	}
	return 0;
}

void MainWindow::OnExit()
{
	DestroyWindow(wnd);
}

void MainWindow::OnNew()
{
	ResetInvoiceFields();
	Load();
}

void MainWindow::OnOpen()
{
	wchar_t tmp[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = wnd;
	ofn.lpstrFilter = L"All files (*.*)\0*.*\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = tmp;
	ofn.Flags = OFN_EXPLORER;

	if (GetOpenFileName(&ofn))
	{
		ResetInvoiceFields();
		std::wifstream is;
		is.open(tmp);

		if (is)
		{
			std::wstring value;
			std::getline(is >> std::ws, value);
			MessageBox(wnd, value.data(), L"Archivo dice:", 0);
		}
		else
		{
			MessageBox(wnd, L"No se pudo crear el archivo", L"Error", 0);
		}
	}
}

void MainWindow::OnSave()
{
	pettyCash.FillHeader(
		edStartDate->GetText(),
		edEndDate->GetText(),
		std::stoi(edWeek->GetText()),
		std::stod(edPendRecv->GetText()),
		std::stod(edCash->GetText()),
		std::stod(edPendInv->GetText()),
		std::stod(edLoan->GetText()),
		std::stod(edTotalAssigned->GetText())
	);

	wchar_t tmp[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = wnd;
	ofn.lpstrFilter = L"All files (*.*)\0*.*\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = tmp;
	ofn.Flags = OFN_EXPLORER;
	ofn.lpstrDefExt = L"txt";

	if (GetSaveFileName(&ofn))
	{
		std::wofstream os;
		os.open(tmp, std::ios_base::trunc);

		if (os)
		{
			pettyCash.Save(os);
		}
		else
		{
			MessageBox(wnd, L"No se pudo crear el archivo", L"Error", 0);
		}
	}
}

void MainWindow::OnSaveAs()
{
	OnSave();
}

void MainWindow::OnConfig()
{
	std::unique_ptr<Settings> settings = std::make_unique<Settings>();
	if (DialogBoxParam(instance, MAKEINTRESOURCE(IDD_CONFIG), wnd, (DLGPROC)Settings::StaticConfigDlgProc, (LPARAM)settings.get()) == IDOK)
	{
		std::wstring tmpTitle;
		if (settings->GetOwner() != L"")
		{
			tmpTitle = L" - " + settings->GetOwner();
		}

		SetWindowText(wnd, (std::wstring(L"Petty Cash") + tmpTitle).c_str());
		edTotalAssigned->SetText(settings->GetStringAmount());
	}
}

LRESULT MainWindow::DefaultProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(wnd, msg, wparam, lparam);
}

void MainWindow::SetGuiFont()
{
	HDC hdc = GetDC(wnd);
	int fontSize = -MulDiv(9, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(wnd, hdc);

	font = CreateFont(
		fontSize,
		0,
		0,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		VARIABLE_PITCH,
		L"Segoe UI");

	EnumChildWindows(wnd, SetChildWndFontProc, (LPARAM)font);
}

void MainWindow::CreateControls()

{
	lbStartDate = std::make_unique<Label>();
	lbStartDate->Create(wnd, STATICLB, L"Fecha inicio", 11, 7, 80, 15);
	edStartDate = std::make_unique<Editbox>();
	edStartDate->Create(wnd, EDDATESTART, 11, 25, 80); 
	lbEndDate = std::make_unique<Label>();
	lbEndDate->Create(wnd, STATICLB, L"Fecha fin", 96, 7, 80, 15);
	edEndDate = std::make_unique<Editbox>();
	edEndDate->Create(wnd, EDDATEEND, 96, 25, 80);
	lbWeek = std::make_unique<Label>();
	lbWeek->Create(wnd, STATICLB, L"Semana num", 182, 7, 80, 15);
	edWeek = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edWeek->Create(wnd, EDWEEK, 182, 25, 80);

	lbDept = std::make_unique<Label>();
	lbDept->Create(wnd, STATICLB, L"Departamento", 412, 7, 80, 15);
	cbDept = std::make_unique<Combobox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | CBS_UPPERCASE);
	cbDept->Create(wnd, CBDEPT, 412, 25, 300);

	lbSectionInv = std::make_unique<Label>();
	lbSectionInv->Create(wnd, STATICLB, L"Comprobantes", 11, 54, 80, 15);

	lbVendor = std::make_unique<Label>();
	lbVendor->Create(wnd, STATICLB, L"Proveedor", 11, 74, 80, 15);
	edVendor = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_UPPERCASE);
	edVendor->Create(wnd, EDVENDOR, 11, 92, 252);
	children.push_back(edVendor->Window());
	lbRFC = std::make_unique<Label>();
	lbRFC->Create(wnd, STATICLB, L"RFC", 268, 74, 80, 15);
	edRFC = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_UPPERCASE);
	edRFC->Create(wnd, EDRFC, 268, 92, 102);
	children.push_back(edRFC->Window());
	lbConcept = std::make_unique<Label>();
	lbConcept->Create(wnd, STATICLB, L"Concepto", 375, 74, 80, 15);
	edConcept = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_UPPERCASE);
	edConcept->Create(wnd, EDCONCEPT, 375, 92, 168);
	children.push_back(edConcept->Window());
	lbInvDate = std::make_unique<Label>();
	lbInvDate->Create(wnd, STATICLB, L"Fecha factura", 548, 74, 80, 15);
	edInvDate = std::make_unique<Editbox>();
	edInvDate->Create(wnd, EDINVDATE, 548, 92, 80);
	children.push_back(edInvDate->Window());
	lbInvNum = std::make_unique<Label>();
	lbInvNum->Create(wnd, STATICLB, L"Num. factura", 633, 74, 80, 15);
	edInvNum = std::make_unique<Editbox>();
	edInvNum->Create(wnd, EDINVNUM, 633, 92, 80);
	children.push_back(edInvNum->Window());

	lbAccount = std::make_unique<Label>();
	lbAccount->Create(wnd, STATICLB, L"Cuenta", 11, 121, 80, 15);
	cbAccount = std::make_unique<Combobox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | CBS_UPPERCASE);
	cbAccount->Create(wnd, CBACCOUNT, 11, 139, 252);
	children.push_back(cbAccount->Window());
	lbAmount = std::make_unique<Label>();
	lbAmount->Create(wnd, STATICLB, L"Monto", 268, 121, 80, 15);
	edAmount = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edAmount->Create(wnd, EDAMOUNT, 268, 139, 80);
	children.push_back(edAmount->Window());
	lbTax = std::make_unique<Label>();
	lbTax->Create(wnd, STATICLB, L"I.V.A.", 353, 121, 80, 15);
	edTax = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTax->Create(wnd, EDTAX, 353, 139, 80);
	children.push_back(edTax->Window());
	lbRet = std::make_unique<Label>();
	lbRet->Create(wnd, STATICLB, L"Retención", 438, 121, 80, 15);
	edRet = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edRet->Create(wnd, EDRET, 438, 139, 80);
	children.push_back(edRet->Window());
	btAdd = std::make_unique<Button>();
	btAdd->Create(wnd, BTADD, L"Agregar", 638, 139);

	list = std::make_unique<ListBox>();
	list->Create(wnd, LSLIST, 11, 175, 450, 289);

	lbTotalReq = std::make_unique<Label>();
	lbTotalReq->Create(wnd, STATICLB, L"Total solicitado", 470, 180, 120, 15);
	edTotalReq = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTotalReq->Create(wnd, EDTOTALREQ, 619, 175, 92);
	lbPendRecv = std::make_unique<Label>();
	lbPendRecv->Create(wnd, STATICLB, L"Reembolso pendiente", 470, 206, 120, 15);
	edPendRecv = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edPendRecv->Create(wnd, EDPENDRECV, 619, 201, 92);
	lbCash = std::make_unique<Label>();
	lbCash->Create(wnd, STATICLB, L"Efectivo en caja", 470, 232, 120, 15);
	edCash = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edCash->Create(wnd, EDCASH, 619, 227, 92);
	lbPendInv = std::make_unique<Label>();
	lbPendInv->Create(wnd, STATICLB, L"Comprobantes pendientes", 470, 258, 120, 15);
	edPendInv = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edPendInv->Create(wnd, EDPENDINV, 619, 253, 92);
	lbTotalSum = std::make_unique<Label>();
	lbTotalSum->Create(wnd, STATICLB, L"Suma", 470, 284, 120, 15);
	edTotalSum = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTotalSum->Create(wnd, EDTOTALSUM, 619, 279, 92);

	lbLoan = std::make_unique<Label>();
	lbLoan->Create(wnd, STATICLB, L"Préstamos", 470, 324, 120, 15);
	edLoan = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edLoan->Create(wnd, EDLOAN, 619, 320, 92);
	lbTotalAssigned = std::make_unique<Label>();
	lbTotalAssigned->Create(wnd, STATICLB, L"Total fondo asignado", 470, 350, 120, 15);
	edTotalAssigned = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTotalAssigned->Create(wnd, EDTOTALASSIGNED, 619, 346, 92);
	lbDiff = std::make_unique<Label>();
	lbDiff->Create(wnd, STATICLB, L"Diferencia", 470, 376, 120, 15);
	edDiff = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edDiff->Create(wnd, EDDIFF, 619, 372, 92);
	
	ResetTotalFields();

	SetFocus(edStartDate->Window());

	SetGuiFont();
}

void MainWindow::CreateMainMenu()
{
	mainMenu = CreateMenu();
	HMENU fileMenu = CreatePopupMenu();
	AppendMenu(fileMenu, MF_STRING, NEWMENU, L"Nuevo");
	AppendMenu(fileMenu, MF_STRING, OPENMENU, L"Abrir");
	AppendMenu(fileMenu, MF_STRING, SAVEMENU, L"Guardar");
	AppendMenu(fileMenu, MF_STRING, SAVEASMENU, L"Guardar como");
	AppendMenu(fileMenu, MF_SEPARATOR, -1, L"-");
	AppendMenu(fileMenu, MF_STRING, PRINTMENU, L"Imprimir");
	AppendMenu(fileMenu, MF_SEPARATOR, -1, L"-");
	AppendMenu(fileMenu, MF_STRING, EXITMENU, L"Salir");
	AppendMenu(mainMenu, MF_POPUP | MF_STRING, (UINT_PTR)fileMenu, L"Archivo");

	HMENU editMenu = CreatePopupMenu();
	AppendMenu(editMenu, MF_STRING, ADDDEPTMENU, L"Agregar departamento");
	AppendMenu(editMenu, MF_STRING, ADDACTMENU, L"Agregar cuenta");
	AppendMenu(editMenu, MF_SEPARATOR, -1, L"-");
	AppendMenu(editMenu, MF_STRING, CFGMENU, L"Configuración");
	AppendMenu(mainMenu, MF_POPUP | MF_STRING, (UINT_PTR)editMenu, L"Editar");

	HMENU helpMenu = CreatePopupMenu();
	AppendMenu(helpMenu, MF_STRING, ABOUTMENU, L"Acerca de...");
	AppendMenu(mainMenu, MF_POPUP | MF_STRING, (UINT_PTR)helpMenu, L"Ayuda");

	SetMenu(wnd, mainMenu);
}

void MainWindow::OnBtnAdd()
{
	Invoice invoice;
	invoice.vendor = edVendor->GetText();
	invoice.rfc = edRFC->GetText();
	invoice.concept = edConcept->GetText();
	invoice.date = edInvDate->GetText();
	invoice.invoiceNo = edInvNum->GetText();
	invoice.account = cbAccount->GetText();
	invoice.amount = std::stod(edAmount->GetText());
	invoice.tax = std::stod(edTax->GetText());
	invoice.retain = std::stod(edRet->GetText());

	pettyCash.AddInvoice(cbDept->GetText(), invoice);
	list->AddItem(pettyCash.GetLastItem());
	edTotalReq->SetText(utilities::format_decimal(pettyCash.GetTotal()));

	ResetInvoiceFields();
	UpdateSum();
	UpdateDiff();
}

void MainWindow::OnPrint()
{
	MessageBox(wnd, L"Próximamente", L"Info", MB_ICONINFORMATION);
}

void MainWindow::OnAddDept()
{
	std::unique_ptr<Department> departments = std::make_unique<Department>();
	DialogBoxParam(instance, MAKEINTRESOURCE(IDD_ADDDEPT), wnd, (DLGPROC)Department::StaticDepartmentDlgProc, (LPARAM)departments.get());
}

void MainWindow::OnAddAccount()
{
	std::unique_ptr<Account> accounts = std::make_unique<Account>();
	DialogBoxParam(instance, MAKEINTRESOURCE(IDD_ADDACCOUNT), wnd, (DLGPROC)Account::StaticAccountDlgProc, (LPARAM)accounts.get());
}

void MainWindow::OnAbout()
{
	ShellAbout(wnd, L"Petty cash#Jonathan Michel. All Rights reserved.", L"This software is distributed as is, without any warranties",
		LoadIcon(instance, MAKEINTRESOURCE(IDI_MAIN)));
}

void MainWindow::OnEnUpdate(UINT idCtrl)
{
	if (idCtrl == EDTOTALREQ ||
		idCtrl == EDPENDINV ||
		idCtrl == EDPENDRECV ||
		idCtrl == EDCASH)
	{
		UpdateSum();
		UpdateDiff();
	}
	else if (idCtrl == EDLOAN ||
		idCtrl == EDTOTALASSIGNED)
	{
		UpdateDiff();
	}
}

void MainWindow::Load()
{
	Settings settings;
	settings.Load();
	std::wstring tmpTitle;
	if (settings.GetOwner() != L"")
	{
		tmpTitle = L" - " + settings.GetOwner();
	}

	SetWindowText(wnd, (std::wstring(L"Petty Cash") + tmpTitle).c_str());
	edTotalAssigned->SetText(settings.GetStringAmount());

	Department departments;
	departments.Load();
	auto tmpDeptMap = std::move(departments.Get());
	for (auto& d : tmpDeptMap)
	{
		int index = cbDept->AddItem(d.second);
		cbDept->SetItemData(index, d.first);
	}

	Account accounts;
	accounts.Load();
	auto tmpActMap = std::move(accounts.Get());
	for (auto& a : tmpActMap)
	{
		int index = cbAccount->AddItem(std::to_wstring(a.first) + L"-" + a.second);
		cbAccount->SetItemData(index, a.first);
	}
}

void MainWindow::UpdateSum()
{
	// Sum 
	double totalReq = pettyCash.GetTotal();
	double pendRecv = std::stod(edPendRecv->GetText());
	double cash = std::stod(edCash->GetText());
	double pendInv = std::stod(edPendInv->GetText());
	double sum = totalReq + pendRecv + cash + pendInv;
	edTotalSum->SetText(utilities::format_decimal(sum));
}

void MainWindow::UpdateDiff()
{
	// Difference
	double sum = std::stod(edTotalSum->GetText());
	double loan = std::stod(edLoan->GetText());
	double totalAssigned = std::stod(edTotalAssigned->GetText());
	double difference = (sum + loan) - totalAssigned;
	edDiff->SetText(utilities::format_decimal(difference));
}
