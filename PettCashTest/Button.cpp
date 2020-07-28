#include "Button.h"
#include <CommCtrl.h>

void Button::Create(HWND parent, int id, const std::wstring& text, int x, int y, int width, int height, bool defPush)
{
  if (wnd)
  {
    throw std::exception("Button already created.");
  }

  int style = WS_TABSTOP | WS_CHILD | WS_VISIBLE;

  if (defPush)
  {
    style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;
  }

  wnd = CreateWindow(
    L"BUTTON",
    text.c_str(),
    style,
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
    throw std::exception("Button could not be created.");
  }
}

void Button::Enable(bool status) const
{
  EnableWindow(wnd, status);
}

bool Button::IsEnabled() const
{
  return IsWindowEnabled(wnd);
}

void Button::SetText(const std::wstring& text) const
{
  SetWindowText(wnd, text.c_str());
}

void Button::CreateCommandLink(HWND parent, int id, const std::wstring& text, int x, int y, int width, int height, const std::wstring& note, bool defPush)
{
  if (wnd)
  {
    throw std::exception("Button already created.");
  }
  
  int style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_COMMANDLINK;
  
  if (defPush)
  {
    style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFCOMMANDLINK;
  }

  wnd = CreateWindow(
    L"BUTTON",
    text.c_str(),
    style,
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
    throw std::exception("Button could not be created.");
  }

  if (!note.empty())
  {
    SendMessage(wnd, BCM_SETNOTE, 0, (LPARAM)note.c_str());
  }
}
