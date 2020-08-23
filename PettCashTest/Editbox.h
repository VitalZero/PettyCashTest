#pragma once
#include "Includes.h"
#include <string>

class Editbox
{
public:
  Editbox()
    : style(WS_TABSTOP | WS_CHILD | WS_VISIBLE | ES_LEFT)
  {}
  Editbox(DWORD style)
    : style(style)
  {}
	size_t GetLength() const;
  std::wstring GetText();
  void SetText(const std::wstring& text);
  void Create(
    HWND parent,
    int id,
    int x,
    int y,
    int width,
    int height = 23);
  HWND Window() const { return wnd; }
  void Disable() const;
  void Enable() const;

private:
	HWND wnd;
	int width;
	int height;
  DWORD style;
};