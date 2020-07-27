// Win32OOP.cpp : Define el punto de entrada de la aplicación.
//
#include "App.h"
#include <cstring>
#include <array>

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
		std::array<wchar_t, MAX_PATH> errorMsg;

		const char* msg = e.what();

		for ( int i = 0; msg[i] != '\0'; ++i )
		{
			errorMsg[i] = msg[i];
		}

		MessageBox(nullptr, errorMsg.data(), L"Error!", MB_ICONERROR);
	}

	return 0;
}