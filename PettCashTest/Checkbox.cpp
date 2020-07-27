#include "Checkbox.h"

void Checkbox::Create(HWND parent, int id, const std::wstring& text, int x, int y, int width, int height)
{
  if (wnd)
  {
    throw std::exception("Checkbox already created.");
  }

  wnd = CreateWindow(
    L"BUTTON",
    text.c_str(),
    WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
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
    throw std::exception("Checkbox could not be created.");
  }
}

bool Checkbox::IsChecked() const
{
  return SendMessage(wnd, BM_GETCHECK, 0, 0);
}

void Checkbox::SetCheck(bool checked)
{
  int checkState;

  if (checked)
  {
    checkState = BST_CHECKED;
  }
  else
  {
    checkState = BST_UNCHECKED;
  }

  SendMessage(wnd, BM_SETCHECK, (WPARAM)checkState, 0);
}

void Radiobutton::Create(HWND parent, int id, const std::wstring& text, int x, int y, int width, int height)
{
  if (wnd)
  {
    throw std::exception("Checkbox already created.");
  }

  wnd = CreateWindow(
    L"BUTTON",
    text.c_str(),
    WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
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
    throw std::exception("Checkbox could not be created.");
  }
}

bool Radiobutton::IsChecked() const
{
  return SendMessage(wnd, BM_GETCHECK, 0, 0);
}

void Radiobutton::SetCheck(bool checked)
{
  int checkState;

  if (checked)
  {
    checkState = BST_CHECKED;
  }
  else
  {
    checkState = BST_UNCHECKED;
  }

  SendMessage(wnd, BM_SETCHECK, (WPARAM)checkState, 0);
}
