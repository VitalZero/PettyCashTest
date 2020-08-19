#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "MainWindow.h"

class App
{
public:
	App() = default;
	HRESULT Init();
	void Run();

private:
	MainWindow win;
};