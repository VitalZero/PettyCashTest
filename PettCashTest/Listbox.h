#pragma once
#include "Includes.h"
#include <string>

class ListBox
{
public:
	int Count() const;
  void Create(
    HWND parent,
    int id,
    int x,
    int y,
    int width,
    int height,
    bool ownerDrawn = false);
  void AddItem(const std::wstring text);
  void SetItemData(int index, int level);
  void OnMeasureItem(MEASUREITEMSTRUCT* pmis);
  void OnDrawItem(DRAWITEMSTRUCT* pdis);
  std::wstring GetItem(int index);
  int GetItemLength(int index);
  int GetItemData(int index) const;
  HWND Window() const { return wnd; }

private:
	HWND wnd;
	int width;
	int height;
  int lastAdded;
};