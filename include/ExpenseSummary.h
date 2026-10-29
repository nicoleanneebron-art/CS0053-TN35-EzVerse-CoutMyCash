#ifndef EXPENSE_SUMMARY_H
#define EXPENSE_SUMMARY_H

#include <cstddef>
#include <map>
#include <string>

struct ExpenseSummary
{
    double totalAmount = 0.0;
    std::size_t expenseCount = 0;
    std::map<std::string, double> categoryTotals;
};

#endif
