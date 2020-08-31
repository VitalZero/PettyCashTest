#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <fstream>

class Department
{
public:
	Department(std::wstring fileName = L"departments.txt")
		: fileName(fileName)
	{}
	void Load();
	void Save();
	bool Add(int deptNumber, std::wstring & deptName);
	static BOOL CALLBACK StaticDepartmentDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	BOOL DepartmentDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	std::map<int, std::wstring> Get() const { return departments; }

private:
	std::wstring fileName;
	std::map<int, std::wstring> departments;
};
