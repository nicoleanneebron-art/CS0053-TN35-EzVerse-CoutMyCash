
#include "ExpenseInputModule.h"

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

bool isValidDate(const std::string& date)
{
    if (date.length() != 10 ||
        date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    int year, month, day;
    char firstDash, secondDash;

    std::istringstream dateStream(date);

    if (!(dateStream >> year >> firstDash >> month
                     >> secondDash >> day))
    {
        return false;
    }

    if (firstDash != '-' || secondDash != '-')
    {
        return false;
    }

    if (year < 1 || month < 1 || month > 12)
    {
        return false;
    }

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool isLeapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    if (isLeapYear)
    {
        daysInMonth[1] = 29;
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

void addExpense()
{
    std::string description;
    std::string amountInput;
    std::string date;
    int categoryId;
    double amount;

    std::cout << "\n===== ADD EXPENSE =====\n";

    std::cout << "Enter expense description: ";
    std::getline(std::cin >> std::ws, description);

    if (description.find_first_not_of(" \t\r\n") ==
        std::string::npos)
    {
        std::cout << "Description cannot be empty.\n";
        return;
    }

    std::cout << "\nSelect category:\n";
    std::cout << "1. Food\n";
    std::cout << "2. Transportation\n";
    std::cout << "3. Utilities\n";
    std::cout << "Enter category number: ";

    if (!(std::cin >> categoryId))
    {
        std::cout << "Invalid category input.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (categoryId < 1 || categoryId > 3)
    {
        std::cout << "Invalid category. Choose 1, 2, or 3.\n";
        return;
    }

    std::cout << "Enter amount: ";
    std::cin >> amount;

    if (std::cin.fail())
    {
        std::cout << "Amount must be numeric.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (!std::isfinite(amount) ||
        amount <= 0 ||
        amount > 1000000000.0)
    {
        std::cout << "Amount must be greater than 0 and at most 1,000,000,000.\n";
        return;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    if (!isValidDate(date))
    {
        std::cout << "Invalid date. Use a real date in YYYY-MM-DD format.\n";
        return;
    }

    std::cout << "\nExpense input validated successfully!\n";
    std::cout << "Description: " << description << '\n';
    std::cout << "Category: ";

    switch (categoryId)
    {
    case 1:
        std::cout << "Food\n";
        break;
    case 2:
        std::cout << "Transportation\n";
        break;
    case 3:
        std::cout << "Utilities\n";
        break;
    }

    std::cout << "Amount: " << std::fixed
              << std::setprecision(2) << amount << '\n';
    std::cout << "Date: " << date << '\n';
}
