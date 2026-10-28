#include "ExpenseManagementModule.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace
{
    const int FOOD_CATEGORY_ID = 1;
    const int TRANSPORTATION_CATEGORY_ID = 2;
    const int UTILITIES_CATEGORY_ID = 3;

    std::string getCategoryName(int categoryId)
    {
        switch (categoryId)
        {
        case FOOD_CATEGORY_ID:
            return "Food";

        case TRANSPORTATION_CATEGORY_ID:
            return "Transportation";

        case UTILITIES_CATEGORY_ID:
            return "Utilities";

        default:
            return "Unknown";
        }
    }

    void displayTableHeader()
    {
        std::cout << std::left
                  << std::setw(6) << "ID"
                  << std::setw(25) << "Description"
                  << std::setw(20) << "Category"
                  << std::setw(12) << "Amount"
                  << std::setw(15) << "Date"
                  << std::endl;

        std::cout << std::string(78, '-') << std::endl;
    }

    void displayExpense(const Expense &expense)
    {
        std::cout << std::left
                  << std::setw(6) << expense.expenseId
                  << std::setw(25) << expense.description
                  << std::setw(20) << getCategoryName(expense.categoryId)
                  << std::fixed << std::setprecision(2)
                  << std::setw(12) << expense.amount
                  << std::setw(15) << expense.date
                  << std::endl;
    }

    bool readInteger(int &value)
    {
        if (std::cin >> value)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            return true;
        }

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        return false;
    }

    void displayMatchingExpenses(
        const std::vector<Expense> &expenses,
        int searchType,
        const std::string &searchText,
        int searchValue)
    {
        bool foundExpense = false;

        for (const Expense &expense : expenses)
        {
            bool isMatch = false;

            if (searchType == FOOD_CATEGORY_ID)
            {
                isMatch = expense.categoryId == searchValue;
            }
            else if (searchType == TRANSPORTATION_CATEGORY_ID)
            {
                isMatch = expense.date == searchText;
            }
            else if (searchType == UTILITIES_CATEGORY_ID)
            {
                isMatch = expense.expenseId == searchValue;
            }

            if (isMatch)
            {
                if (!foundExpense)
                {
                    displayTableHeader();
                }

                displayExpense(expense);
                foundExpense = true;
            }
        }

        if (!foundExpense)
        {
            std::cout << "No matching expenses were found." << std::endl;
        }
    }

    void searchByCategory(const std::vector<Expense> &expenses)
    {
        int categoryId = 0;

        std::cout << "Select category:" << std::endl;
        std::cout << "[1] Food" << std::endl;
        std::cout << "[2] Transportation" << std::endl;
        std::cout << "[3] Utilities" << std::endl;
        std::cout << "Enter category: ";

        if (!readInteger(categoryId) ||
            categoryId < FOOD_CATEGORY_ID ||
            categoryId > UTILITIES_CATEGORY_ID)
        {
            std::cout << "Invalid category selection." << std::endl;
            return;
        }

        displayMatchingExpenses(
            expenses,
            FOOD_CATEGORY_ID,
            "",
            categoryId);
    }

    void searchByDate(const std::vector<Expense> &expenses)
    {
        std::string date;

        std::cout << "Enter date in YYYY-MM-DD format: ";
        std::getline(std::cin, date);

        if (date.empty())
        {
            std::cout << "Date cannot be empty." << std::endl;
            return;
        }

        displayMatchingExpenses(
            expenses,
            TRANSPORTATION_CATEGORY_ID,
            date,
            0);
    }

    void searchById(const std::vector<Expense> &expenses)
    {
        int expenseId = 0;

        std::cout << "Enter expense ID: ";

        if (!readInteger(expenseId))
        {
            std::cout << "Invalid expense ID." << std::endl;
            return;
        }

        displayMatchingExpenses(
            expenses,
            UTILITIES_CATEGORY_ID,
            "",
            expenseId);
    }
}

void viewExpenses(const std::vector<Expense> &expenses)
{
    std::cout << "\nVIEW EXPENSES" << std::endl;
    std::cout << "-------------" << std::endl;

    if (expenses.empty())
    {
        std::cout << "No expenses have been recorded." << std::endl;
        return;
    }

    displayTableHeader();

    for (const Expense &expense : expenses)
    {
        displayExpense(expense);
    }
}

void searchExpenses(const std::vector<Expense> &expenses)
{
    if (expenses.empty())
    {
        std::cout << "No expenses are available to search." << std::endl;
        return;
    }

    int selectedOption = -1;

    while (selectedOption != 0)
    {
        std::cout << "\nSEARCH EXPENSES" << std::endl;
        std::cout << "---------------" << std::endl;
        std::cout << "[1] Search by Category" << std::endl;
        std::cout << "[2] Search by Date" << std::endl;
        std::cout << "[3] Search by Record ID" << std::endl;
        std::cout << "[0] Return to Main Menu" << std::endl;
        std::cout << "Select an option: ";

        if (!readInteger(selectedOption))
        {
            std::cout << "Invalid menu selection." << std::endl;
            continue;
        }

        switch (selectedOption)
        {
        case 1:
            searchByCategory(expenses);
            break;

        case 2:
            searchByDate(expenses);
            break;

        case 3:
            searchById(expenses);
            break;

        case 0:
            break;

        default:
            std::cout << "Invalid menu selection." << std::endl;
            break;
        }
    }
}