// Win32OOP.cpp : Define el punto de entrada de la aplicación.
//
#include "App.h"
#include <cstring>

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	try
	{
		App app;
		if ( SUCCEEDED( app.Init() ) )
		{
			app.Run();
		}
	}
	catch (std::exception& e)
	{
		const char* ble = e.what();
		wchar_t msg[MAX_PATH] = {};

		for ( int i = 0; ble[i] != '\0'; ++i )
		{
			msg[i] = ble[i];
		}

		MessageBox(nullptr, msg, L"Error!", MB_ICONERROR);
	}

	return 0;
}