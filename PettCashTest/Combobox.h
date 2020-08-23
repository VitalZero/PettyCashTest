#pragma once
#include "Includes.h"
#include <string>

class Combobox
{
public:
  Combobox()
    : style(WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | CBS_DROPDOWN | CBS_HASSTRINGS)
  {}
  Combobox(DWORD style)
    : style(style)
  {}
  int Count() const;
  void Create(
    HWND parent,
    int id,
    int x,
    int y,
    int width,
    int height = apparentMinHeight);
  void AddItem(const std::wstring text);
  std::wstring GetItem(int index);
  size_t GetItemLength(int index) const;
  HWND Window() const { return wnd; }

private:
	HWND wnd;
	int width;
	int height;
	int lastAdded;
  DWORD style;
  static constexpr int apparentMinHeight = 100;
};