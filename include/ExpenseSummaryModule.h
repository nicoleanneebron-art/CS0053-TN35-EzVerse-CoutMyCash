#ifndef EXPENSE_SUMMARY_MODULE_H
#define EXPENSE_SUMMARY_MODULE_H

#include <vector>

#include "Expense.h"
#include "ExpenseSummary.h"

ExpenseSummary generateSummary(const std::vector<Expense>& expenses);
void displaySummary(const ExpenseSummary& summary);

#endif
