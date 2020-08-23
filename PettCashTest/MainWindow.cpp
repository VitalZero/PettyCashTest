#pragma once
#include "MainWindow.h"

MainWindow::MainWindow()
{
	msgHandler.Register(WM_CREATE, &MainWindow::OnCreate, this);
	msgHandler.Register(WM_DESTROY, &MainWindow::OnDestroy, this);
	msgHandler.Register(WM_CTLCOLORSTATIC, &MainWindow::OnCtlColorStatic, this);
	msgHandler.Register(WM_PAINT, &MainWindow::OnPaint, this);
	msgHandler.Register(0, &MainWindow::DefaultProc, this);
	msgHandler.Register(WM_COMMAND, &MainWindow::OnCommand, this);
	msgHandler.Bind(EXITMENU, &MainWindow::OnExit, this);
}

void MainWindow::Init()
{
	CreateControls();
	CreateMainMenu();

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
	return msgHandler.Dispatch(msg, wparam, lparam);
}

BOOL CALLBACK MainWindow::SetChildWndFontProc(HWND wndChild, LPARAM font)
{
	SendMessage(wndChild, WM_SETFONT, (WPARAM)font, TRUE);
	return TRUE;
}

LRESULT MainWindow::OnCreate(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return 1;
}

LRESULT MainWindow::OnDestroy(UINT msg, WPARAM wparam, LPARAM lparam)
{
	DeleteObject(font);
	PostQuitMessage(0);
	return 0;
}

LRESULT MainWindow::OnCtlColorStatic(UINT msg, WPARAM wparam, LPARAM lparam)
{
	SetBkMode((HDC)wparam, TRANSPARENT);
	return (LRESULT)(HBRUSH)GetStockObject(NULL_BRUSH);
}

LRESULT MainWindow::OnPaint(UINT msg, WPARAM wparam, LPARAM lparam)
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
	rcEdge.top = 309;
	rcEdge.bottom = 310;

	DrawEdge(hdc, &rcEdge, BDR_SUNKENINNER, BF_TOP);

	EndPaint(wnd, &ps);
	return 0;
}

LRESULT MainWindow::OnCommand(UINT msg, WPARAM wparam, LPARAM lparam)
{
	msgHandler.Dispatch(LOWORD(wparam));
	return 0;
}

void MainWindow::OnExit()
{
	DestroyWindow(wnd);
}

LRESULT MainWindow::DefaultProc(UINT msg, WPARAM wparam, LPARAM lparam)
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
	lbDateStart = std::make_unique<Label>();
	lbDateStart->Create(wnd, STATICLB, L"Fecha inicio", 11, 7, 80, 15);
	edDateStart = std::make_unique<Editbox>();
	edDateStart->Create(wnd, EDDATESTART, 11, 25, 80);
	lbDateEnd = std::make_unique<Label>();
	lbDateEnd->Create(wnd, STATICLB, L"Fecha fin", 96, 7, 80, 15);
	edDateEnd = std::make_unique<Editbox>();
	edDateEnd->Create(wnd, EDDATEEND, 96, 25, 80);
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
	lbRFC = std::make_unique<Label>();
	lbRFC->Create(wnd, STATICLB, L"RFC", 268, 74, 80, 15);
	edRFC = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_UPPERCASE);
	edRFC->Create(wnd, EDRFC, 268, 92, 102);
	lbConcept = std::make_unique<Label>();
	lbConcept->Create(wnd, STATICLB, L"Concepto", 375, 74, 80, 15);
	edConcept = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_UPPERCASE);
	edConcept->Create(wnd, EDCONCEPT, 375, 92, 168);
	lbInvDate = std::make_unique<Label>();
	lbInvDate->Create(wnd, STATICLB, L"Fecha factura", 548, 74, 80, 15);
	edInvDate = std::make_unique<Editbox>();
	edInvDate->Create(wnd, EDINVDATE, 548, 92, 80);
	lbInvNum = std::make_unique<Label>();
	lbInvNum->Create(wnd, STATICLB, L"Num. factura", 633, 74, 80, 15);
	edInvDate = std::make_unique<Editbox>();
	edInvDate->Create(wnd, EDINVNUM, 633, 92, 80);

	lbAccount = std::make_unique<Label>();
	lbAccount->Create(wnd, STATICLB, L"Cuenta", 11, 121, 80, 15);
	cbAccount = std::make_unique<Combobox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS | CBS_UPPERCASE);
	cbAccount->Create(wnd, CBACCOUNT, 11, 139, 252);
	lbAmount = std::make_unique<Label>();
	lbAmount->Create(wnd, STATICLB, L"Monto", 268, 121, 80, 15);
	edAmount = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edAmount->Create(wnd, EDAMOUNT, 268, 139, 80);
	lbTax = std::make_unique<Label>();
	lbTax->Create(wnd, STATICLB, L"I.V.A.", 353, 121, 80, 15);
	edTax = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTax->Create(wnd, EDTAX, 353, 139, 80);
	lbRet = std::make_unique<Label>();
	lbRet->Create(wnd, STATICLB, L"Retención", 438, 121, 80, 15);
	edRet = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edRet->Create(wnd, EDRET, 438, 139, 80);
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
	edTotalSum->Disable();
	edTotalSum->SetText(L"Disabled!");

	lbLoan = std::make_unique<Label>();
	lbLoan->Create(wnd, STATICLB, L"Préstamos", 470, 324, 120, 15);
	edLoan = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edLoan->Create(wnd, EDLOAN, 619, 320, 92);
	lbTotalAssigned = std::make_unique<Label>();
	lbTotalAssigned->Create(wnd, STATICLB, L"Total fondo asignado", 470, 350, 120, 15);
	edTotalAssigned = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edTotalAssigned->Create(wnd, EDTOTALASSIGNED, 619, 346, 92);
	edTotalAssigned->Disable();
	edTotalAssigned->SetText(L"Disabled!");
	lbDiff = std::make_unique<Label>();
	lbDiff->Create(wnd, STATICLB, L"Diferencia", 470, 376, 120, 15);
	edDiff = std::make_unique<Editbox>(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_RIGHT);
	edDiff->Create(wnd, EDDIFF, 619, 372, 92);
	edDiff->Disable();
	edDiff->SetText(L"Disabled!");

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

	SetMenu(wnd, mainMenu);
}

//BOOL CALLBACK MainWindow::StaticInputDlgProc( HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam )
//{
//	//MainWindow* pThis = nullptr; 
//
//	//if (msg == WM_INITDIALOG)
//	//{
//	//	pThis = (MainWindow*)lparam;
//	//	SetWindowLongPtr(wndDlg, DWLP_USER, (LONG_PTR)pThis);
//	//}
//	//else
//	//	pThis = (MainWindow*)GetWindowLongPtr(wndDlg, DWLP_USER);
//
//	//if (pThis)
//	//	return pThis->InputDlgProc(wndDlg, msg, wparam, lparam);
//
//	//return FALSE;
//}
//
//BOOL CALLBACK MainWindow::StaticAboutDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	//switch (msg)
//	//{
//	//case WM_COMMAND:
//	//	if (LOWORD(wparam) == IDCANCEL)
//	//	{
//	//		EndDialog(wndDlg, LOWORD(wparam));
//	//		return TRUE;
//	//	}
//	//}
//	//
//	//return FALSE;
//}
//
//BOOL MainWindow::InputDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	//switch (msg)
//	//{
//	//case WM_INITDIALOG:
//	//	if( btnAsignar.WasPressed() )
//	//	{
//	//		SetDlgItemText(wndDlg, IDD_STATIC, "Asignar a:");
//	//	}
//	//	else if (btnBuscar.WasPressed())
//	//	{
//	//		SetDlgItemText(wndDlg, IDD_STATIC, "Buscar a:");
//	//	}
//	//break;
//
//	//case WM_COMMAND:
//	//	switch (LOWORD(wparam))
//	//	{
//	//	case IDD_OK:
//	//	{
//	//		std::fill(szDialogInput, szDialogInput + sizeof(szDialogInput), 0);
//
//	//		unsigned int rtrn = GetDlgItemText(wndDlg, IDD_TEXTBOX, szDialogInput, MAX_PATH);
//	//		
//	//	}
//	//	case IDD_CANCEL:
//	//		EndDialog(wndDlg, LOWORD(wparam));
//	//		return TRUE;
//	//	}
//	//	break;
//	//}
//
//	//return FALSE;
//}