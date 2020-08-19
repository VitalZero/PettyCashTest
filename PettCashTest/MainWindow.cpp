#pragma once
#include "MainWindow.h"

MainWindow::MainWindow()
{
	msgHandler.Register(WM_CREATE, &MainWindow::OnCreate, this);
	msgHandler.Register(WM_DESTROY, &MainWindow::OnDestroy, this);
	msgHandler.Register(WM_CTLCOLORSTATIC, &MainWindow::OnCtlColorStatic, this);
	msgHandler.Register(0, &MainWindow::DefaultProc, this);
	msgHandler.Register(WM_MEASUREITEM, &MainWindow::OnMeasureItem, this);
	msgHandler.Register(WM_DRAWITEM, &MainWindow::OnDrawItem, this);
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return msgHandler.Handle(msg, wparam, lparam);
}

BOOL CALLBACK MainWindow::SetChildWndFontProc(HWND wndChild, LPARAM font)
{
	SendMessage(wndChild, WM_SETFONT, (WPARAM)font, TRUE);
	return TRUE;
}

void MainWindow::Init()
{
	list = std::make_unique<ListBox>();
	list->Create(wnd, Controls::ListBoxId, 10, 40, 200, 300, true);
	list->AddItem(L"Dirección mantenimiento campo");
	list->SetItemData(0, 0);
	list->AddItem(L"Operación mantenimiento campo");
	list->SetItemData(1, 0);
	list->AddItem(L"Refacciones");
	list->SetItemData(2, 1);

	editVendor = std::make_unique<Editbox>();
	editVendor->Create(wnd, Controls::EditVendor, 10, 10, 100);

	comboDept = std::make_unique<Combobox>();
	comboDept->Create(wnd, Controls::ComboDept, 117, 10, 150);
	comboDept->AddItem(L"Diez");
	comboDept->AddItem(L"Veinte");
	comboDept->AddItem(L"Treinta");

	checkIva = std::make_unique<Checkbox>();
	checkIva->Create(wnd, Controls::CheckTax, L"IVA", 274, 10, 50);

	buttonAgregar = std::make_unique<Button>();
	buttonAgregar->CreateCommandLink(wnd, Controls::buttonAgregar, L"Agregar", 274, 40, 120, 58, L"Esto es una nota");

	radioOk = std::make_unique<Radiobutton>();
	radioOk->Create(wnd, Controls::CheckRet, L"Retencion", 274, 150, 80);

	labelHola = std::make_unique<Label>();
	labelHola->Create(wnd, Controls::StaticLbl, L"Hola!", 274, 184, 50);

	SetGuiFont();
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

LRESULT MainWindow::DefaultProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(wnd, msg, wparam, lparam);
}

LRESULT MainWindow::OnMeasureItem(UINT msg, WPARAM wparam, LPARAM lparam)
{
	list->OnMeasureItem((MEASUREITEMSTRUCT*)lparam);
	return 0;
}

LRESULT MainWindow::OnDrawItem(UINT msg, WPARAM wparam, LPARAM lparam)
{
	list->OnDrawItem((DRAWITEMSTRUCT*)lparam);
	return TRUE;
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