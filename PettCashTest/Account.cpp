#include "Account.h"
#include <stdexcept>
#include <sstream>
#include "resource.h"

void Account::Load()
{
  std::wifstream is(fileName);

  if (is)
  {
    accounts.clear();

    std::wstring tmp;
    while (std::getline(is, tmp) && is.good())
    {
      std::wstringstream ss(tmp);
      int tmpAct;
      ss >> tmpAct >> tmp;

      Add(tmpAct, tmp);
    }
  }
  else
  {
    std::wofstream os(fileName, std::ios_base::trunc);

    if (!os)
    {
      throw std::exception("Can't create accounts file");
    }
  }

}

void Account::Save()
{
  std::wofstream os(fileName, std::ios_base::trunc);
  if (os)
  {
    for (auto& a : accounts)
    {
      os << a.first << L" " << a.second << L"\n";
    }
  }
  else
  {
    throw std::exception("Bad accounts file");
  }
}

bool Account::Add(int accountNumber, std::wstring& accountName)
{
  auto itr = accounts.find(accountNumber);
  if (itr == accounts.end())
  {
    accounts.insert({ accountNumber, accountName });
    return true;
  }
  else
  {
    return false;
  }
}

BOOL Account::StaticAccountDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
  Account* pThis = nullptr;

  if (msg == WM_INITDIALOG)
  {
    pThis = (Account*)lparam;
    SetWindowLongPtr(wndDlg, DWLP_USER, (LONG_PTR)pThis);
  }
  else
  {
    pThis = (Account*)GetWindowLongPtr(wndDlg, DWLP_USER);
  }

  if (pThis)
  {
    return pThis->AccountDlgProcedure(wndDlg, msg, wparam, lparam);
  }
  
  return FALSE;
}

BOOL Account::AccountDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_COMMAND:
    switch (LOWORD(wparam))
    {
    case IDOK:
    {
      int i = 0;
    }
    case IDCANCEL:
      EndDialog(wndDlg, LOWORD(wparam));
      return TRUE;
    }
    break;
  }
  return FALSE;
}
