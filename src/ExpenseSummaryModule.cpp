#include "ExpenseSummaryModule.h"

#include <iomanip>
#include <iostream>
#include <string>

namespace
{
    const std::string FOOD_CATEGORY = "Food";
    const std::string TRANSPORTATION_CATEGORY = "Transportation";
    const std::string UTILITIES_CATEGORY = "Utilities";
    const std::string UNKNOWN_CATEGORY = "Unknown";

    std::string getCategoryName(int categoryId)
    {
        switch (categoryId)
        {
        case 1:
            return FOOD_CATEGORY;
        case 2:
            return TRANSPORTATION_CATEGORY;
        case 3:
            return UTILITIES_CATEGORY;
        default:
            return UNKNOWN_CATEGORY;
        }
    }

    void displayCategoryTotal(
        const ExpenseSummary& summary,
        const std::string& categoryName)
    {
        const auto categoryTotal = summary.categoryTotals.find(categoryName);
        const double amount = categoryTotal == summary.categoryTotals.end()
                                  ? 0.0
                                  : categoryTotal->second;

        std::cout << categoryName << ": " << amount << '\n';
    }
}

ExpenseSummary generateSummary(const std::vector<Expense>& expenses)
{
    ExpenseSummary summary;
    summary.categoryTotals[FOOD_CATEGORY] = 0.0;
    summary.categoryTotals[TRANSPORTATION_CATEGORY] = 0.0;
    summary.categoryTotals[UTILITIES_CATEGORY] = 0.0;

    for (const Expense& expense : expenses)
    {
        summary.totalAmount += expense.amount;
        ++summary.expenseCount;
        summary.categoryTotals[getCategoryName(expense.categoryId)] +=
            expense.amount;
    }

    return summary;
}

void displaySummary(const ExpenseSummary& summary)
{
    std::cout << "\n===== EXPENSE SUMMARY =====\n";
    std::cout << "Number of expenses: " << summary.expenseCount << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total spent: " << summary.totalAmount << "\n\n";
    std::cout << "By category:\n";

    displayCategoryTotal(summary, FOOD_CATEGORY);
    displayCategoryTotal(summary, TRANSPORTATION_CATEGORY);
    displayCategoryTotal(summary, UTILITIES_CATEGORY);

    if (summary.categoryTotals.find(UNKNOWN_CATEGORY) !=
        summary.categoryTotals.end())
    {
        displayCategoryTotal(summary, UNKNOWN_CATEGORY);
    }
}
