#pragma once
#include <windows.h>
#include <string>
#include <fstream>
#include <map>

class Account
{
public:
	Account(std::wstring fileName = L"accounts.txt")
		: fileName(fileName)
	{}
	void Load();
	void Save();
	bool Add(int accountNumber, std::wstring& accountName);
	static BOOL CALLBACK StaticAccountDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL AccountDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	std::wstring fileName;
	std::map<int, std::wstring> accounts;
};