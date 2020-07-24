#pragma once
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