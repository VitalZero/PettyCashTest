#include "Listbox.h"

int ListBox::Count() const
{
  return (int)SendMessage(wnd, LB_GETCOUNT, 0, 0);
}

void ListBox::Create(HWND parent, int id, int x, int y, int width, int height, bool ownerDrawn)
{
  if ( wnd )
  {
    throw std::exception("ListBox already created.");
  }

  DWORD styles = WS_TABSTOP | WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | WS_HSCROLL | WS_VSCROLL;

  if ( ownerDrawn )
    styles |= LBS_OWNERDRAWFIXED;

  wnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    L"LISTBOX",
    L"",
    styles,
    x,
    y,
    width,
    height,
    parent,
    (HMENU)id,
    GetModuleHandle(nullptr),
    nullptr);

  if ( !wnd )
  {
    throw std::exception("Listbox could not be created");
  }
}

void ListBox::AddItem(const std::wstring text)
{
  lastAdded = (int)SendMessage(wnd, LB_ADDSTRING, 0, (LPARAM)text.c_str());
}

void ListBox::SetItemData(int index, int level)
{
  SendMessage(wnd, LB_SETITEMDATA, (WPARAM)index, (LPARAM)level);
}

void ListBox::OnMeasureItem(MEASUREITEMSTRUCT* pmis)
{
  pmis->itemHeight = 20;
}

void ListBox::OnDrawItem(DRAWITEMSTRUCT* pdis)
{
  unsigned int cch;
  wchar_t buffer[MAX_PATH] = { 0 };
  TEXTMETRIC tm;

  if ( pdis->itemID != -1 )
  {
    switch ( pdis->itemAction )
    {
    case ODA_FOCUS:
      if ( pdis->itemState & ODS_SELECTED )
      {
        DrawFocusRect(pdis->hDC, &pdis->rcItem);
      }
      break;
    case ODA_SELECT:
    case ODA_DRAWENTIRE:
    {
      SendMessage(pdis->hwndItem, LB_GETTEXT, pdis->itemID, (LPARAM)buffer);

      GetTextMetrics(pdis->hDC, &tm);
      int yPos = (pdis->rcItem.bottom + pdis->rcItem.top - tm.tmHeight) / 2;

      cch = (unsigned int)wcslen(buffer);
      COLORREF colorPen = RGB(100, 100, 100);

      if ( pdis->itemState & ODS_SELECTED )
      {
        colorPen = RGB(255, 255, 255);
        SetTextColor(pdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
        SetBkColor(pdis->hDC, GetSysColor(COLOR_HIGHLIGHT));
      }
      else
      {
        SetTextColor(pdis->hDC, GetSysColor(COLOR_WINDOWTEXT));
        SetBkColor(pdis->hDC, GetSysColor(COLOR_WINDOW));

      }
      WORD data = (WORD)SendMessage(pdis->hwndItem, LB_GETITEMDATA, pdis->itemID, 0);
      unsigned char level = (unsigned char)LOWORD(data);
      unsigned char state = (unsigned char)HIWORD(data);
      const int xBitMap = 0;// 24;
      const int yBitMap = GetSystemMetrics(SM_CYSMICON);
      const int yBitPos = (pdis->rcItem.bottom + pdis->rcItem.top - yBitMap) / 2;
      int xOffset = 10 * level;

      ExtTextOut(pdis->hDC, pdis->rcItem.left + xOffset + xBitMap, yPos,
        ETO_OPAQUE, &pdis->rcItem, buffer, cch, 0);

      if (level > 0)
      {
        LOGBRUSH lbrush = { 0 };
        lbrush.lbColor = colorPen;
        lbrush.lbStyle = BS_SOLID;
        HPEN dotPen = ExtCreatePen(PS_COSMETIC | PS_ALTERNATE, 1, &lbrush, 0, nullptr);
        MoveToEx(pdis->hDC, 2, yPos + tm.tmHeight / 2, nullptr);
        HPEN oldPen = (HPEN)SelectObject(pdis->hDC, dotPen);
        LineTo(pdis->hDC, pdis->rcItem.left + xOffset + xBitMap - 2, yPos + tm.tmHeight / 2);
        SelectObject(pdis->hDC, oldPen);
        DeleteObject(oldPen);
      }

      //ImageList_Draw(sysImgListSM, 3/*level*/, pdis->hDC, pdis->rcItem.left + xOffset + 4, yBitPos, ILD_TRANSPARENT);
    }
    break;
    }
  }
}

std::wstring ListBox::GetItem(int index)
{
  std::wstring tmp;
  tmp.reserve(GetItemLength(index) + 1);

  if ( SendMessage(wnd, LB_GETTEXT, (WPARAM)index, (LPARAM)&tmp[0]) > 0 )
  {
    return tmp;
  }

  return std::wstring();
}

size_t ListBox::GetItemLength(int index)
{
  return SendMessage(wnd, CB_GETLBTEXTLEN, (WPARAM)index, 0);
}

int ListBox::GetItemData(int index) const
{
  return (int)SendMessage(wnd, LB_GETITEMDATA, (WPARAM)index, 0);
}
