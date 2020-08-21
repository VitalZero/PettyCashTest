#pragma once
#include "MainWindow.h"

MainWindow::MainWindow()
{
	msgHandler.Register(WM_CREATE, &MainWindow::OnCreate, this);
	msgHandler.Register(WM_DESTROY, &MainWindow::OnDestroy, this);
	msgHandler.Register(WM_CTLCOLORSTATIC, &MainWindow::OnCtlColorStatic, this);
	msgHandler.Register(WM_PAINT, &MainWindow::OnPaint, this);
	msgHandler.Register(0, &MainWindow::DefaultProc, this);
}

void MainWindow::Init()
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
	edWeek = std::make_unique<Editbox>();
	edWeek->Create(wnd, EDWEEK, 182, 25, 80);

	lbDept = std::make_unique<Label>();
	lbDept->Create(wnd, STATICLB, L"Departamento", 412, 7, 80, 15);
	cbDept = std::make_unique<Combobox>();
	cbDept->Create(wnd, CBDEPT, 412, 25, 300);

	lbSectionInv = std::make_unique<Label>();
	lbSectionInv->Create(wnd, STATICLB, L"Comprobantes", 11, 54, 80, 15);


	SetGuiFont();
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

	DrawEdge(hdc, &rcEdge, BDR_SUNKENINNER, BF_BOTTOM);

	EndPaint(wnd, &ps);
	return 0;
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