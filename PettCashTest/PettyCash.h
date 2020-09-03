#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>

struct Invoice
{
	std::wstring vendor;
	std::wstring rfc;
	std::wstring concept;
	std::wstring date;
	std::wstring invoiceNo;
	std::wstring account;
	double amount;
	double retain;
	double tax;
};

class PettyCash
{
public:
	PettyCash();
public:
	void FillHeader(const std::wstring& startDate, const std::wstring& endDate, int week,
		double pending, double cash, double invoices, double loan, double assigned);
	void AddInvoice(const std::wstring& department, const Invoice& invoice);
	void Save(std::wostream& os);
	std::wstring GetLastItem() const { return lastItem; }
	double GetTotal() const { return total; }

private:
	void AddDepartment(const std::wstring& department);
	void SetLastItem(const std::wstring& dept, const Invoice& invoice);

private:
	std::wstring startDate;
	std::wstring endDate;
	int week;
	int records;
	double total;
	double pending;
	double cash;
	double invoices;
	double loan;
	double assigned;
	std::wstring lastItem;
	std::map<std::wstring, std::vector<Invoice>> data;
};