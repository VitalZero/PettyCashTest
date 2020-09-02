#pragma once
#include <string>
#include <fstream>
#include <windows.h>

class Settings
{
public:
	Settings(std::wstring fileName = L"cfg.txt")
		: fileName(fileName), amount(0)
	{}
	void Load();
	void Save();
	double GetAmount() const { return amount; }
	std::wstring GetStringAmount();
	std::wstring GetOwner() const { return owner; }
	void SetAmount(double amount) { this->amount = amount; }
	void SetOwner(std::wstring& owner) { this->owner = owner; }
	static BOOL CALLBACK StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL ConfigDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	std::wstring owner;
	double amount;
	std::wstring fileName;
};