#include "ExpenseModificationModule.h"
#include "Expense.h"
#include "FileStorageModule.h"

#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <sstream>
#include <cctype>

using namespace std;

// Find the position of an expense using its ID
static int findExpenseById(const vector<Expense> &expenses, int expenseId)
{
    for (int i = 0; i < static_cast<int>(expenses.size()); i++)
    {
        if (expenses[i].expenseId == expenseId)
        {
            return i;
        }
    }

    return -1;
}

// Validate the date and check for leap years
static bool isValidExpenseDate(const string &date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i])))
        {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12)
    {
        return false;
    }

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};

    bool isLeapYear = (year % 400 == 0) ||
                      (year % 4 == 0 && year % 100 != 0);

    if (isLeapYear)
    {
        daysInMonth[1] = 29;
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

void updateExpense()
{
    vector<Expense> expenses;

    if (!initializeStorage() || !loadExpenses(expenses))
    {
        cout << "Error: Could not load expense records.\n";
        return;
    }

    if (expenses.empty())
    {
        cout << "No expense records available to update.\n";
        return;
    }

    int expenseId;
    string idInput;

    cout << "\n========== UPDATE EXPENSE ==========\n";
    cout << "Enter expense ID: ";
    getline(cin, idInput);

    istringstream idStream(idInput);
    char extra;

    if (!(idStream >> expenseId) || (idStream >> extra) || expenseId <= 0)
    {
        cout << "Invalid expense ID. Please enter a valid positive number.\n";
        return;
    }
    int expenseIndex = findExpenseById(expenses, expenseId);

    if (expenseIndex == -1)
    {
        cout << "Expense record not found.\n";
        return;
    }

    Expense updatedExpense = expenses[expenseIndex];

    cout << "\nSelected Expense:\n";
    cout << "Description : " << expenses[expenseIndex].description << endl;
    cout << "Category ID : " << expenses[expenseIndex].categoryId << endl;
    cout << "Amount      : " << expenses[expenseIndex].amount << endl;
    cout << "Date        : " << expenses[expenseIndex].date << endl;

    string newDescription;

    cout << "\nNew Description (Enter to keep current): ";
    getline(cin, newDescription);

    if (!newDescription.empty())
    {
        if (newDescription.find_first_not_of(" \t\r\n") == string::npos)
        {
            cout << "Description cannot be empty.\n";
            return;
        }

        updatedExpense.description = newDescription;
    }

    string newCategory;

    cout << "\nSelect New Category:\n";
    cout << "[1] Food\n";
    cout << "[2] Transportation\n";
    cout << "[3] Utilities\n";
    cout << "New Category (Enter to keep current): ";

    getline(cin, newCategory);

    if (!newCategory.empty())
    {
        if (newCategory == "1")
        {
            updatedExpense.categoryId = 1;
        }
        else if (newCategory == "2")
        {
            updatedExpense.categoryId = 2;
        }
        else if (newCategory == "3")
        {
            updatedExpense.categoryId = 3;
        }
        else
        {
            cout << "Invalid category. Choose 1, 2, or 3.\n";
            return;
        }
    }

    string newAmount;

    cout << "\nCurrent Amount: " << updatedExpense.amount << endl;
    cout << "New Amount (Enter to keep current): ";
    getline(cin, newAmount);

    if (!newAmount.empty())
    {
        double amount;
        char extra;
        istringstream amountInput(newAmount);

        if (!(amountInput >> amount) || (amountInput >> extra))
        {
            cout << "Amount must be numeric.\n";
            return;
        }

        if (!isfinite(amount) || amount <= 0 || amount > 1000000000.0)
        {
            cout << "Amount must be greater than 0 and at most 1,000,000,000.\n";
            return;
        }

        updatedExpense.amount = amount;
    }
    string newDate;

    cout << "\nCurrent Date: " << updatedExpense.date << endl;
    cout << "New Date (YYYY-MM-DD, Enter to keep current): ";
    getline(cin, newDate);

    if (!newDate.empty())
    {
        if (!isValidExpenseDate(newDate))
        {
            cout << "Invalid date. Use a real date in YYYY-MM-DD format.\n";
            return;
        }

        updatedExpense.date = newDate;
    }
    string confirmation;

    cout << "\n========== CONFIRM UPDATE ==========\n";
    cout << "Description : " << updatedExpense.description << endl;
    cout << "Category ID : " << updatedExpense.categoryId << endl;
    cout << "Amount      : " << updatedExpense.amount << endl;
    cout << "Date        : " << updatedExpense.date << endl;

    cout << "\n[1] Save Changes\n";
    cout << "[0] Cancel\n";
    cout << "Select an option: ";

    getline(cin, confirmation);

    if (confirmation == "0")
    {
        cout << "Update cancelled.\n";
        return;
    }

    if (confirmation != "1")
    {
        cout << "Invalid option. No changes were saved.\n";
        return;
    }

    // Save the updated expense record
    expenses[expenseIndex] = updatedExpense;

    if (!saveExpenses(expenses))
    {
        cout << "Error: Could not save the updated expense.\n";
        return;
    }

    cout << "\nExpense updated successfully!\n";
}


void deleteExpense()
{
    vector<Expense> expenses;

    if (!initializeStorage() || !loadExpenses(expenses))
    {
        cout << "Error: Could not load expense records.\n";
        return;
    }

    if (expenses.empty())
    {
        cout << "No expense records available to delete.\n";
        return;
    }

    string idInput;
    int expenseId;

    cout << "\n========== DELETE EXPENSE ==========\n";
    cout << "Enter expense ID: ";
    getline(cin, idInput);

    istringstream idStream(idInput);
    char extra;

    if (!(idStream >> expenseId) || (idStream >> extra) || expenseId <= 0)
    {
        cout << "Invalid expense ID. Please enter a valid positive number.\n";
        return;
    }

    int expenseIndex = findExpenseById(expenses, expenseId);

    if (expenseIndex == -1)
    {
        cout << "Expense record not found.\n";
        return;
    }

    cout << "\nSelected Expense:\n";
    cout << "Description : " << expenses[expenseIndex].description << endl;
    cout << "Category ID : " << expenses[expenseIndex].categoryId << endl;
    cout << "Amount      : " << expenses[expenseIndex].amount << endl;
    cout << "Date        : " << expenses[expenseIndex].date << endl;

    string confirmation;

    cout << "\n[1] Confirm Delete\n";
    cout << "[0] Cancel\n";
    cout << "Select an option: ";

    getline(cin, confirmation);

    if (confirmation == "0")
    {
        cout << "Deletion cancelled.\n";
        return;
    }

    if (confirmation != "1")
    {
        cout << "Invalid option. No expense was deleted.\n";
        return;
    }


    // Remove the selected expense
    expenses.erase(expenses.begin() + expenseIndex);

    if (!saveExpenses(expenses))
    {
        cout << "Error: Could not save the changes.\n";
        return;
    }

    cout << "\nExpense deleted successfully!\n";

}
