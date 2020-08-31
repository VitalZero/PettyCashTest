#include "Department.h"
#include <stdexcept>
#include <sstream>
#include "resource.h"

void Department::Load()
{
  std::wifstream is(fileName);
  if (is)
  {
    departments.clear();
    std::wstring tmp;

    while(std::getline(is, tmp) && is.good())
    {
      std::wstringstream ss(tmp);
      int deptTmp;
      ss >> deptTmp;
      ss.ignore();
      std::getline(ss, tmp);

      Add(deptTmp, tmp);
    }
  }
  else
  {
    std::wofstream os(fileName, std::ios_base::trunc);

    if (!os)
    {
      throw std::exception("Can't create departments file.");
    }
  }
}

void Department::Save()
{
  std::wofstream os(fileName, std::ios_base::trunc);
  if (os)
  {
    for (auto& d : departments)
    {
      os << d.first << L" " << d.second << L"\n";
    }
  }
  else
  {
    throw std::exception("Bad departments file.");
  }
}

bool Department::Add(int deptNumber, std::wstring& deptName)
{
  auto itr = departments.find(deptNumber);
  if (itr == departments.end())
  {
    departments.insert({ deptNumber, deptName });
    return true;
  }
  else
  {
    return false;
  }
}

BOOL Department::StaticDepartmentDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
  Department* pThis = nullptr;

  if (msg == WM_INITDIALOG)
  {
    pThis = (Department*)lparam;
    SetWindowLongPtr(wndDlg, DWLP_USER, (LONG_PTR)pThis);
  }
  else
  {
    pThis = (Department*)GetWindowLongPtr(wndDlg, DWLP_USER);
  }

  if (pThis)
  {
    return pThis->DepartmentDlgProcedure(wndDlg, msg, wparam, lparam);
  }


  return FALSE;
}

BOOL Department::DepartmentDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_INITDIALOG:
    SetFocus(GetDlgItem(wndDlg, IDC_DEPTNO));
    break;

  case WM_COMMAND:
    switch (LOWORD(wparam))
    {
    case IDOK:
    {
      wchar_t buffer[MAX_PATH] = { 0 };
      int len = GetWindowTextLength(GetDlgItem(wndDlg, IDC_DEPTNO));
      GetDlgItemText(wndDlg, IDC_DEPTNO, buffer, len + 1);
      int tmpDeptNo = std::stoi(buffer);

      len = GetWindowTextLength(GetDlgItem(wndDlg, IDC_DEPTDESC));
      GetDlgItemText(wndDlg, IDC_DEPTDESC, buffer, len + 1);
      std::wstring tmpDeptDesc = buffer;

      Load();
      Add(tmpDeptNo, tmpDeptDesc);
      Save();

      SetDlgItemText(wndDlg, IDC_DEPTNO, L"");
      SetDlgItemText(wndDlg, IDC_DEPTDESC, L"");
      SetFocus(GetDlgItem(wndDlg, IDC_DEPTNO));
    }
    case IDCANCEL:
      EndDialog(wndDlg, LOWORD(wparam));
      return TRUE;
    }
  }

  return FALSE;
}
