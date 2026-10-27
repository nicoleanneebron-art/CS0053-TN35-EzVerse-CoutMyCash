
#include "ExpenseInputModule.h"

#include <iostream>
#include <limits>
#include <string>

void addExpense()
{
    std::string description;
    int categoryId;

    std::cout << "\n===== ADD EXPENSE =====\n";

    std::cout << "Enter expense description: ";
    std::getline(std::cin >> std::ws, description);

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
        std::cout << "Invalid category. Please choose 1, 2, or 3.\n";
        return;
    }

    std::cout << "\nDescription: " << description << '\n';
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
}
