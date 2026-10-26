#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

struct Expense
{
    int expenseId = 0;
    std::string description;
    int categoryId = 0;
    double amount = 0.0;
    std::string date;
};

#endif
