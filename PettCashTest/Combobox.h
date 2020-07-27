#pragma once
#include "Includes.h"
#include <string>

class Combobox
{
public:
  int Count() const;
  void Create(
    HWND parent,
    int id,
    int x,
    int y,
    int width,
    int height = 23);
  void AddItem(const std::wstring text);
  std::wstring GetItem(int index);
  size_t GetItemLength(int index) const;
  HWND Window() const { return wnd; }

private:
	HWND wnd;
	int width;
	int height;
	int lastAdded;
};