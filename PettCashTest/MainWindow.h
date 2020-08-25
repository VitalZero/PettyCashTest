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
#include <vector>

class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow();

public:
	LPCWSTR ClassName() const override { return L"PettyCash"; }
	LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) override;
	void AppendControl() {}
	//BOOL InputDlgProc( HWND hWndDlg, UINT msg, WPARAM wparam, LPARAM lparam );
	//static BOOL CALLBACK StaticAboutDlgProc( HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam );

private:
	static BOOL CALLBACK SetChildWndFontProc(HWND wndChild, LPARAM font);
	static BOOL CALLBACK StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL ConfigDlgProc(HWND hWndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnCreate(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnDestroy(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnCtlColorStatic(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnPaint(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT OnCommand(UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT DefaultProc(UINT msg, WPARAM wparam, LPARAM lparam);
	void ResetFields();
	void Init() override;
	void OnExit();
	void OnNew();
	void OnOpen();
	void OnSave();
	void OnSaveAs();
	void OnConfig();
	void SetGuiFont();
	void CreateControls();
	void CreateMainMenu();

private:
	std::vector<HWND> children;

private:
	HFONT font = nullptr;
	HMENU mainMenu = nullptr;
	// Data capture
	std::unique_ptr<Editbox> edDateStart;
	std::unique_ptr<Editbox> edDateEnd;
	std::unique_ptr<Editbox> edWeek;
	std::unique_ptr<Combobox> cbDept;
	std::unique_ptr<Editbox> edVendor;
	std::unique_ptr<Editbox> edRFC;
	std::unique_ptr<Editbox> edConcept;
	std::unique_ptr<Editbox> edInvDate;
	std::unique_ptr<Editbox> edInvNum;
	std::unique_ptr<Editbox> edAmount;
	std::unique_ptr<Combobox> cbAccount;
	std::unique_ptr<Editbox> edTax;
	std::unique_ptr<Editbox> edRet;
	std::unique_ptr<Button> btAdd;
	// Totals
	std::unique_ptr<Editbox> edTotalReq;
	std::unique_ptr<Editbox> edPendRecv;
	std::unique_ptr<Editbox> edCash;
	std::unique_ptr<Editbox> edPendInv;
	std::unique_ptr<Editbox> edTotalSum;
	std::unique_ptr<Editbox> edLoan;
	std::unique_ptr<Editbox> edTotalAssigned;
	std::unique_ptr<Editbox> edDiff;
	// Result
	std::unique_ptr<ListBox> list;
	// Labels for controls
	std::unique_ptr<Label> lbDateStart;
	std::unique_ptr<Label> lbDateEnd;
	std::unique_ptr<Label> lbWeek;
	std::unique_ptr<Label> lbDept;
	std::unique_ptr<Label> lbVendor;
	std::unique_ptr<Label> lbRFC;
	std::unique_ptr<Label> lbConcept;
	std::unique_ptr<Label> lbInvDate;
	std::unique_ptr<Label> lbInvNum;
	std::unique_ptr<Label> lbAccount;
	std::unique_ptr<Label> lbAmount;
	std::unique_ptr<Label> lbTax;
	std::unique_ptr<Label> lbRet;
	std::unique_ptr<Label> lbTotalReq;
	std::unique_ptr<Label> lbPendRecv;
	std::unique_ptr<Label> lbCash;
	std::unique_ptr<Label> lbPendInv;
	std::unique_ptr<Label> lbTotalSum;
	std::unique_ptr<Label> lbLoan;
	std::unique_ptr<Label> lbTotalAssigned;
	std::unique_ptr<Label> lbDiff;
	// Labels for sections
	std::unique_ptr<Label> lbSectionInv;
	MsgHandler msgHandler;
};