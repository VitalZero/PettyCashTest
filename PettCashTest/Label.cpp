#include "Label.h"

void Label::Create(HWND parent, int id, const std::wstring& text, int x, int y, int width, int height)
{
  if (wnd)
  {
    throw std::exception("Label already created.");
  }

  wnd = CreateWindowEx(
    0,
    L"STATIC",
    text.c_str(),
    WS_CHILD | WS_VISIBLE | SS_LEFT,
    x,
    y,
    width,
    height,
    parent,
    (HMENU)id,
    GetModuleHandle(nullptr),
    nullptr);

  if (!wnd)
  {
    throw std::exception("Label could not be created.");
  }
}

void Label::SetText(const std::wstring& text)
{
  SetWindowText(wnd, text.c_str());
}
