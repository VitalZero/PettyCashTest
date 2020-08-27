#include "Settings.h"
#include <stdexcept>
#include <sstream>
#include "resource.h"

void Settings::Load()
{
	std::wifstream is;
	is.open(fileName);
	
	if (is)
	{
		std::wstring tmp;
		while (std::getline(is, tmp) && is.good())
		{
			if (tmp == L"[owner]")
			{
				std::getline(is, owner);
			}
			else if (tmp == L"[amount]")
			{
				is >> amount;
			}
			else if (tmp.empty())
			{
			}
			else
			{
				throw std::exception("Bad settings file in open");
			}
		}
	}
	else
	{
		std::wofstream os(fileName, std::ios_base::trunc);

		if (!os)
		{
			throw std::exception("Can't create config file");
		}
	}
}

void Settings::Save()
{
	std::wofstream os;
	os.open(fileName, std::ios_base::trunc);

	if (os)
	{
		os << L"[owner]" << L"\n" << owner << L"\n";
		os << L"[amount]" << L"\n" << amount << L"\n";
	}
	else
	{
		throw std::exception("Bad settings file in save");
	}
}

BOOL CALLBACK Settings::StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	Settings* pThis = nullptr;

	if (msg == WM_INITDIALOG)
	{
		pThis = (Settings*)lparam;
		SetWindowLongPtr(wndDlg, DWLP_USER, (LONG_PTR)pThis);
	}
	else
	{
		pThis = (Settings*)GetWindowLongPtr(wndDlg, DWLP_USER);
	}

	if (pThis)
	{
		return pThis->ConfigDlgProcedure(wndDlg, msg, wparam, lparam);
	}

	return FALSE;
}

BOOL Settings::ConfigDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		Load();
		SetDlgItemInt(wndDlg, IDC_TOTAL, amount, FALSE);
		SetDlgItemText(wndDlg, IDC_CUSTODY, owner.c_str());
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case IDOK:
		{
			wchar_t buffer[MAX_PATH] = { 0 };
			GetDlgItemText(wndDlg, IDC_CUSTODY, buffer, MAX_PATH);
			owner = buffer;

			int len = GetWindowTextLength(GetDlgItem(wndDlg, IDC_TOTAL));
			GetDlgItemText(wndDlg, IDC_TOTAL, buffer, len + 1);
			amount = std::stoi(buffer);
			Save();
		}
		case IDCANCEL:
			EndDialog(wndDlg, LOWORD(wparam));
			return TRUE;
		}
		break;
	}

	return FALSE;
}