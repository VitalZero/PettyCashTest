#include "App.h"
#include <exception>

HRESULT App::Init()
{
	HRESULT hr = win.Create(
		L"Petty Cash", 
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX, 
		0,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		740, 
		500);

	if ( FAILED( hr ) )
	{
		throw std::exception("Main window could not be created.");
	}

	return hr;
}

void App::Run()
{
	MSG msg = {};
	BOOL retMsg;

	while ( (retMsg = GetMessage( &msg, 0, 0, 0 )) != 0 )
	{
		if ( retMsg == -1 )
		{
		}
		else
		{
			if ( !IsDialogMessage(win.Window(), &msg) )
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}