#include "Account.h"
#include <stdexcept>

void Account::Load()
{
}

void Account::Save()
{
  std::wofstream os(fileName, std::ios_base::trunc);
  if (os)
  {
    for (auto& a : accounts)
    {
      os << a.first << L":" << a.second << L"\n";
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
    accounts[accountNumber] = accountName;
    return true;
  }
  else
  {
    return false;
  }
}

BOOL Account::StaticAccountDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return 0;
}

BOOL Account::AccountDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return 0;
}
