
#include "Expense.h"
#include "FileStorageModule.h"
#include "ExpenseModificationModule.h"

#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

int main()
{
    if (filesystem::current_path().filename() != "CountMyCash-TestEnvironment")
    {
        cout << "Error: Run this test inside CountMyCash-TestEnvironment.\n";
        return 1;
    }

    vector<Expense> expenses;

    if (!initializeStorage() || !saveExpenses(expenses))
    {
        cout << "Error: Could not prepare empty test records.\n";
        return 1;
    }

    cout << "Empty test records prepared successfully.\n";
    cout << "\nStarting Empty Expense Test...\n";

    deleteExpense();

    return 0;
}
