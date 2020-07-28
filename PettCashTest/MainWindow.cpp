#pragma once
#include "MainWindow.h"

MainWindow::MainWindow()
{
}

LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;
	bool wasHandled = false;

	switch ( msg )
	{
		case WM_CREATE:
			OnCreate((CREATESTRUCT*)lparam);
			result = 1;
		break;

		case WM_CTLCOLORSTATIC:
			SetBkMode((HDC)wparam, TRANSPARENT);
			result = (LRESULT)(HBRUSH)GetStockObject(NULL_BRUSH); // COLOR_WINDOW + 1;
			wasHandled = true;
		break;
	
		case WM_DESTROY:
			DeleteObject(font);
			PostQuitMessage(0);
			result = 0;
			wasHandled = true;
		break;
	}

	if ( !wasHandled )
	{
		result = DefWindowProc(wnd, msg, wparam, lparam);
	}

	return result;
}

BOOL CALLBACK MainWindow::SetChildWndFontProc(HWND wndChild, LPARAM font)
{
	SendMessage(wndChild, WM_SETFONT, (WPARAM)font, TRUE);
	return TRUE;
}

void MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	list = std::make_unique<ListBox>();
	list->Create(wnd, Controls::ListBoxId, 10, 40, 200, 300, false);
	list->AddItem(L"Uno");
	list->AddItem(L"Dos");
	list->AddItem(L"Tres");

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
	buttonAgregar->Create(wnd, Controls::buttonAgregar, L"Agregar", 274, 40, 120, 58);

	radioOk = std::make_unique<Radiobutton>();
	radioOk->Create(wnd, Controls::CheckRet, L"Retencion", 274, 150, 80);

	labelHola = std::make_unique<Label>();
	labelHola->Create(wnd, Controls::StaticLbl, L"Hola!", 274, 184, 50);

	SetGuiFont();
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