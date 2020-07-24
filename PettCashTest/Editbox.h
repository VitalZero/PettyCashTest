#pragma once
#include "Includes.h"
#include <string>

class Editbox
{
public:
	int GetLength() const;
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

private:
	HWND wnd;
	int width;
	int height;
};