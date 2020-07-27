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
  void CreateCommandLink(HWND parent,
    int id,
    const std::wstring& text,
    int x,
    int y,
    int width = 100,
    int height = 41,
    const std::wstring& note = L"",
    bool defPush = false);

private:
	HWND wnd;
	int width;
	int height;
};