#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "BaseWindow.h"
#include "Listbox.h"
#include "Editbox.h"
#include "Combobox.h"
#include "Checkbox.h"
#include "Button.h"
#include "Label.h"
#include <memory>

class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow();

public:
	LPCWSTR ClassName() const override { return L"PettyCash"; }
	LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override;
	static BOOL CALLBACK SetChildWndFontProc(HWND wndChild, LPARAM font);
	//BOOL InputDlgProc( HWND hWndDlg, UINT msg, WPARAM wparam, LPARAM lparam );
	//static BOOL CALLBACK StaticInputDlgProc( HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam );
	//static BOOL CALLBACK StaticAboutDlgProc( HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam );

private:
	void OnCreate(CREATESTRUCT* pcs);
	void SetGuiFont();

private:
	HFONT font = nullptr;
	std::unique_ptr<ListBox> list;
	std::unique_ptr<Editbox> editVendor;
	std::unique_ptr<Combobox> comboDept;
	std::unique_ptr<Checkbox> checkIva;
	std::unique_ptr<Button> buttonAgregar;
	std::unique_ptr<Radiobutton> radioOk;
	std::unique_ptr<Label> labelHola;
};