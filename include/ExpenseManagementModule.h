#ifndef EXPENSE_MANAGEMENT_MODULE_H
#define EXPENSE_MANAGEMENT_MODULE_H

#include <vector>

#include "Expense.h"

void viewExpenses(const std::vector<Expense> &expenses);
void searchExpenses(const std::vector<Expense> &expenses);

#endif