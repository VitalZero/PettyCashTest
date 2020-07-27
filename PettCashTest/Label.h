#pragma once
#include "Includes.h"
#include <string>

class Label
{
public:
  void Create(
    HWND parent,
    int id,
    const std::wstring& text,
    int x,
    int y,
    int width,
    int height = 13);
  void SetText(const std::wstring& text);
  HWND Window() const { return wnd; }

private:
	HWND wnd;
	int width;
	int height;
};