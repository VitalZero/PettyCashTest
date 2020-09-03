#include "PettyCash.h"
#include <sstream>
#include <iomanip>

PettyCash::PettyCash()
	:
	startDate(L""), endDate(L""), week(-1), total(0), records(0), pending(0),
	cash(0), invoices(0), loan(0), assigned(0)
{
}

void PettyCash::FillHeader(const std::wstring& startDate, const std::wstring& endDate, int week,
	double pending, double cash, double invoices, double loan, double assigned)
{
	this->startDate = startDate;
	this->endDate = endDate;
	this->week = week;
	this->pending = pending;
	this->cash = cash;
	this->invoices = invoices;
	this->loan = loan;
	this->assigned = assigned;
}

void PettyCash::AddDepartment(const std::wstring& department)
{
	auto itr = data.find(department);
	if (itr == data.end())
	{
		data[department];
	}
}

void PettyCash::AddInvoice(const std::wstring& department, const Invoice& invoice)
{
	AddDepartment(department);
	data[department].emplace_back(invoice);
	total += invoice.amount + invoice.tax - invoice.retain;
	records++;
	SetLastItem(department, invoice);

	//auto itr = data.find(department);
	//if (itr != data.end())
	//{
	//	data[department].emplace_back(invoice);
	//	total += invoice.amount + invoice.tax - invoice.retain;
	//	records++;
	//	SetLastItem(department, invoice);
	//}
}

void PettyCash::Save(std::wostream& os)
{
	// header
	os << L"1.1 " << records << "\n";
	os << L"[fechas]\n";
	os << startDate << L" " << endDate << week << L"\n";
	os << L"[montos]\n";
	os << total << L" " << pending << L" " << cash << L" " 
		<< invoices << L" "	<< loan << L" " << assigned << "\n";
	
	//department data
	for (auto& d : data)
	{
		os << "[departamento]\n";
		os << d.first << "\n";
		os << d.second.size() << "\n";
		os << "[facturas]\n";

		//invoice data
		for (auto& i : d.second)
		{
			os << i.vendor << L"|" << i.rfc << L"|" << i.concept << L"|"
				<< i.date << L"|" << i.invoiceNo << L"|" << i.account << L"|"
				<< i.amount << L"|" << i.tax << L"|" << i.retain << "\n";
		}
	}
}

void PettyCash::SetLastItem(const std::wstring& dept, const Invoice& invoice)
{
	std::wstringstream ss;
	ss << invoice.vendor << L":" << invoice.rfc << L" " << invoice.date << L":" << invoice.invoiceNo
		<< L" " << invoice.account << L":> $ " << std::setprecision(4) << invoice.amount
		<< L" I.V.A.:> $ " << std::setprecision(4) << invoice.tax << L" -$ " << std::setprecision(4) << invoice.retain
		<< L"  TOTAL:> $ " << std::setprecision(4) << (invoice.amount + invoice.tax - invoice.retain);

	lastItem = ss.str();
}
