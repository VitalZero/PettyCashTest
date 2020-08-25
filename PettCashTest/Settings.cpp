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
		while (std::getline(is, tmp) && is.good())
		{
			if (tmp == L"[owner]")
			{
				std::getline(is, owner);
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
				throw std::exception("Bad settings file in open");
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
		throw std::exception("Bad settings file in save");
	}
}
