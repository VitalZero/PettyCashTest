#pragma once
#include <cassert>
#include "Includes.h"

template <class DERIVED_T>
class BaseWindow
{
public:
	BaseWindow()
		:
		wnd(nullptr), instance(GetModuleHandle(nullptr)),	width(200), height(200)
	{}

public:
	void Show(int show) { ShowWindow(wnd, show); }
	HWND Window() const { return wnd; }
	HRESULT Create(
		LPCWSTR wndName, 
		DWORD style, 
		DWORD exStyle = 0,
		int x = CW_USEDEFAULT, 
		int y = CW_USEDEFAULT, 
		int width = CW_USEDEFAULT, 
		int height = CW_USEDEFAULT,
		HWND wndParent = 0, 
		HMENU menu = 0)
	{
		HRESULT hr;

		RECT rc = {};
		rc.left = x;
		rc.right = width + x;
		rc.top = y;
		rc.bottom = height + y;
		AdjustWindowRect(&rc, style, TRUE);

		this->width = rc.right - rc.left;
		this->height = rc.bottom - rc.top;

		ATOM result = Register();
		assert(result != 0);

		wnd = CreateWindowEx(
			exStyle, 
			ClassName(), 
			wndName, 
			style,
			x, 
			y, 
			width, 
			height,
			wndParent, 
			menu, 
			instance, 
			this);

		hr = wnd ? S_OK : E_FAIL;
		if ( SUCCEEDED( hr ) )
		{
			ShowWindow(wnd, SW_SHOW);
			UpdateWindow(wnd);
		}

		return hr;
	}

	ATOM Register()
	{
		WNDCLASSEX wcx = {};

		wcx.cbSize = sizeof(WNDCLASSEX);
		wcx.hInstance = instance;
		wcx.lpszClassName = ClassName();
		wcx.lpfnWndProc = DERIVED_T::WndProc;
		wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcx.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

		return RegisterClassEx(&wcx);
	}

protected:
	virtual LPCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT msg, WPARAM wparam, LPARAM lparam) = 0;

public:
	static LRESULT CALLBACK WndProc(HWND procWnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		DERIVED_T* thisWnd = nullptr;

		if ( msg == WM_NCCREATE )
		{
			LPCREATESTRUCT pCreate = (LPCREATESTRUCT)lparam;
			thisWnd = (DERIVED_T*)pCreate->lpCreateParams;
			thisWnd->wnd = procWnd;

			assert(thisWnd != nullptr);

			SetWindowLongPtr(procWnd, GWLP_USERDATA, (LONG_PTR)thisWnd);
		}
		else
		{
			thisWnd = (DERIVED_T*)GetWindowLongPtr(procWnd, GWLP_USERDATA);
		}
		if (thisWnd)
		{
			return thisWnd->HandleMessage(msg, wparam, lparam);
		}
		else
		{
			return DefWindowProc(procWnd, msg, wparam, lparam);
		}
	}

protected:
	HWND wnd;
	HINSTANCE instance;
	int width;
	int height;
};