#pragma once

#include "BaseWindow.h"
#include "Listbox.h"
#include "Editbox.h"
#include "Combobox.h"
#include "Checkbox.h"
#include "Button.h"
#include "Label.h"
#include <memory>
#include "MsgHandler.h"

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
	void Init() override;
	LRESULT OnCreate(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnDestroy(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnCtlColorStatic(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT DefaultProc(UINT msg, WPARAM wparam, LPARAM lparam);
	void SetGuiFont();

private:
	HFONT font = nullptr;
	// Data capture
	std::unique_ptr<Editbox> edDateStart;
	std::unique_ptr<Editbox> edDateEnd;
	std::unique_ptr<Editbox> edWeek;
	std::unique_ptr<Combobox> cbDept;
	std::unique_ptr<Editbox> edVendor;
	std::unique_ptr<Editbox> edRFC;
	std::unique_ptr<Editbox> edConcept;
	std::unique_ptr<Editbox> edInvoiceDate;
	std::unique_ptr<Editbox> edInvoiceNum;
	std::unique_ptr<Editbox> edAmount;
	std::unique_ptr<Combobox> cbDept;
	std::unique_ptr<Editbox> edTax;
	std::unique_ptr<Editbox> edRet;
	std::unique_ptr<Button> btAdd;
	// Totals
	std::unique_ptr<Editbox> edTotalReq;
	std::unique_ptr<Editbox> edPendRec;
	std::unique_ptr<Editbox> edCash;
	std::unique_ptr<Editbox> edPendInv;
	std::unique_ptr<Editbox> edTotalSum;
	std::unique_ptr<Editbox> edLoan;
	std::unique_ptr<Editbox> edTotalAssigned;
	std::unique_ptr<Editbox> edDifference;
	std::unique_ptr<Checkbox> checkIva;
	std::unique_ptr<Radiobutton> radioOk;
	std::unique_ptr<Label> labelHola;
	// Result

	std::unique_ptr<ListBox> list;
	MsgHandler msgHandler;
};