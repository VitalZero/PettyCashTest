#pragma once

#include "Includes.h"
#include <string>

class Button
{
public:
  void Create(
    HWND parent,
    int id,
    const std::wstring& text,
    int x,
    int y,
    int width = 75,
    int height = 23,
    bool defPush = false);
  void Enable(bool status) const;
  bool IsEnabled() const;
  void SetText(const std::wstring& text) const;

private:
	HWND wnd;
	int width;
	int height;
};