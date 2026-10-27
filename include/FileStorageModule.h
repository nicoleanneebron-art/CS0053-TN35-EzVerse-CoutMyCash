#ifndef FILE_STORAGE_MODULE_H
#define FILE_STORAGE_MODULE_H

#include <vector>

#include "Expense.h"

bool initializeStorage();
bool loadExpenses(std::vector<Expense>& expenses);
bool saveExpenses(const std::vector<Expense>& expenses);

#endif
