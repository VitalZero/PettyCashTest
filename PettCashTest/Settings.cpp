#include "Settings.h"
#include <stdexcept>
#include <sstream>

void Settings::Load()
{
	std::wifstream is;
	is.open(fileName);
	
	if (is)
	{
		std::wstring tmp;
		while (std::getline(is >> std::ws, tmp) && is.good())
		{
			if (tmp == L"[owner]")
			{
				std::getline(is >> std::ws, owner);
			}
			else if (tmp == L"[amount]")
			{
				is >> amount;
			}
			else if (tmp.empty())
			{
			}
			else
			{
				throw std::runtime_error("Bad settings file");
			}
		}
		
	}
	else
	{
		Save();
	}
}

void Settings::Save()
{
	std::wofstream os;
	os.open(fileName, std::ios_base::trunc);

	if (os)
	{
		os << L"[owner]" << L"\n" << owner << L"\n";
		os << L"[amount]" << L"\n" << amount << L"\n";
	}
	else
	{
		throw std::runtime_error("Could not save settings file");
	}
}
