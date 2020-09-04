#pragma once
#include <sstream>
#include <string>
#include <iomanip>

namespace utilities {

	std::wstring format_decimal(double value, int decimalPlaces = 2)
	{
		std::wstringstream ss;
		ss << std::setprecision((std::streamsize)decimalPlaces) << std::fixed << value;

		return ss.str();
	}
	std::wstring format_decimal(float value, int decimalPlaces = 2)
	{
		std::wstringstream ss;
		ss << std::setprecision((std::streamsize)decimalPlaces) << std::fixed << value;

		return ss.str();
	}
}// end utilities