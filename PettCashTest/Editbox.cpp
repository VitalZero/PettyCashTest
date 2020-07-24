#include "EditBox.h"

int Editbox::GetLength() const
{
  return SendMessage(wnd, WM_GETTEXTLENGTH, 0, 0);
}

std::wstring Editbox::GetText()
{
  std::wstring tmp;
  tmp.reserve(GetLength() + 1);

  if ( GetWindowText(wnd, &tmp[0], GetLength() + 1) > 0 )
  {
    return tmp;
  }

  return std::wstring();
}

void Editbox::SetText(const std::wstring& text)
{
  SetWindowText(wnd, text.c_str());
}

void Editbox::Create(HWND parent, int id, int x, int y, int width, int height)
{
  if ( wnd )
  {
    throw std::exception("Editbox already created.");
  }

  wnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    L"EDIT",
    L"",
    WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT,
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
    throw std::exception("Editbox could not be created.");
  }
}
