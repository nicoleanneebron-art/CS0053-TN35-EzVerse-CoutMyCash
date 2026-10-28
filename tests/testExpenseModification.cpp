#include <iostream>
#include <vector>
#include "../src/ExpenseModificationModule.cpp"

using namespace std;

int main()
{
    vector<Expense> expenses = {
        {1, "Lunch", 1, 120.00, "2026-10-20"},
        {2, "Bus Fare", 2, 50.00, "2026-10-21"},
        {3, "Electricity", 3, 850.00, "2026-10-22"}
    };

    cout << "TEST 1: Existing Expense ID" << endl;
    cout << "Expected: 1" << endl;
    cout << "Actual: " << findExpenseById(expenses, 2) << endl;

    cout << "\nTEST 2: Nonexistent Expense ID" << endl;
    cout << "Expected: -1" << endl;
    cout << "Actual: " << findExpenseById(expenses, 99) << endl;

    vector<Expense> emptyExpenses;

    cout << "\nTEST 3: Empty Expense Records" << endl;
    cout << "Expected: -1" << endl;
    cout << "Actual: " << findExpenseById(emptyExpenses, 1) << endl;

    return 0;
}