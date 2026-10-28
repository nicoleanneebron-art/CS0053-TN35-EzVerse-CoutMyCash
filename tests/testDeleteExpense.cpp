
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

    vector<Expense> expenses = {
        {1, "Lunch", 1, 120.00, "2026-10-20"},
        {2, "Bus Fare", 2, 50.00, "2026-10-21"},
        {3, "Electricity", 3, 850.00, "2026-10-22"}
    };

    if (!initializeStorage() || !saveExpenses(expenses))
    {
        cout << "Error: Could not prepare test records.\n";
        return 1;
    }

    cout << "Test records prepared successfully.\n";
    cout << "\nStarting Delete Expense Test...\n";

    deleteExpense();

    return 0;
}
