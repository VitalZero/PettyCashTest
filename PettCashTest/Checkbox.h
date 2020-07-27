#pragma once
#include "Includes.h"
#include <string>

class Checkbox
{
public:
  void Create(
    HWND parent,
    int id,
    const std::wstring& text,
    int x,
    int y,
    int width,
    int height = 17);
  HWND Window() const { return wnd; }
  bool IsChecked() const;
  void SetCheck(bool checked);

private:
	HWND wnd;
	int width;
	int height;
};

class Radiobutton
{
public:
  void Create(
    HWND parent,
    int id,
    const std::wstring& text,
    int x,
    int y,
    int width,
    int height = 17);
  HWND Window() const { return wnd; }
  bool IsChecked() const;
  void SetCheck(bool checked);

private:
  HWND wnd;
  int width;
  int height;
};