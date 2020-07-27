#include "Combobox.h"

int Combobox::Count() const
{
  return (int)SendMessage(wnd, CB_GETCOUNT, 0, 0);
}

void Combobox::Create(HWND parent, int id, int x, int y, int width, int height)
{
  if ( wnd )
  {
    throw std::exception("ListBox already created.");
  }

  DWORD styles = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS;

  wnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    L"COMBOBOX",
    L"",
    styles,
    x,
    y,
    width,
    height,
    parent,
    (HMENU)id,
    GetModuleHandle(nullptr),
    nullptr);

  if ( !wnd )
  {
    throw std::exception("Listbox could not be created");
  }
}

void Combobox::AddItem(const std::wstring text)
{
  lastAdded = (int)SendMessage(wnd, CB_ADDSTRING, 0, (LPARAM)text.c_str());
}

std::wstring Combobox::GetItem(int index)
{
  std::wstring tmp;
  tmp.reserve(GetItemLength(index) + 1);

  if ( SendMessage(wnd, CB_GETLBTEXT, (WPARAM)index, (LPARAM)&tmp[0]) > 0 )
  {
    return tmp;
  }

  return std::wstring();
}

size_t Combobox::GetItemLength(int index) const
{
  return SendMessage(wnd, CB_GETLBTEXTLEN, (WPARAM)index, 0);
}
