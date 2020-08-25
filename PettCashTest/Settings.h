#pragma once
#include <string>
#include <fstream>

class Settings
{
public:
	Settings(std::wstring fileName = L"cfg.txt")
		: fileName(fileName), amount(0)
	{}
	void Load();
	void Save();
	int GetAmount() const { return amount; }
	std::wstring GetOwner() const { return owner; }
	void SetAmount(int amount) { this->amount = amount; }
	void SetOwner(std::wstring& owner) { this->owner = owner; }
private:
	std::wstring owner;
	int amount;
	std::wstring fileName;
};