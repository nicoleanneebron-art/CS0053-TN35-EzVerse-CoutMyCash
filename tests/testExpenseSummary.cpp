#include "ExpenseSummaryModule.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    bool nearlyEqual(double first, double second)
    {
        return std::fabs(first - second) < 0.00001;
    }

    void testEmptySummary()
    {
        const ExpenseSummary summary = generateSummary({});

        assert(summary.expenseCount == 0);
        assert(nearlyEqual(summary.totalAmount, 0.0));
        assert(nearlyEqual(summary.categoryTotals.at("Food"), 0.0));
        assert(nearlyEqual(summary.categoryTotals.at("Transportation"), 0.0));
        assert(nearlyEqual(summary.categoryTotals.at("Utilities"), 0.0));
    }

    void testCategoryTotals()
    {
        const std::vector<Expense> expenses = {
            {1, "Lunch", 1, 120.50, "2026-10-20"},
            {2, "Bus Fare", 2, 50.00, "2026-10-21"},
            {3, "Electricity", 3, 850.00, "2026-10-22"},
            {4, "Snack", 1, 30.00, "2026-10-22"},
            {5, "Uncategorized", 99, 5.00, "2026-10-23"}
        };

        const ExpenseSummary summary = generateSummary(expenses);

        assert(summary.expenseCount == expenses.size());
        assert(nearlyEqual(summary.totalAmount, 1055.50));
        assert(nearlyEqual(summary.categoryTotals.at("Food"), 150.50));
        assert(nearlyEqual(summary.categoryTotals.at("Transportation"), 50.00));
        assert(nearlyEqual(summary.categoryTotals.at("Utilities"), 850.00));
        assert(nearlyEqual(summary.categoryTotals.at("Unknown"), 5.00));
    }

    void testDisplaySummary()
    {
        const ExpenseSummary summary = generateSummary({
            {1, "Lunch", 1, 120.00, "2026-10-20"}
        });

        std::ostringstream displayedSummary;
        std::streambuf* const originalOutput =
            std::cout.rdbuf(displayedSummary.rdbuf());

        displaySummary(summary);
        std::cout.rdbuf(originalOutput);

        const std::string output = displayedSummary.str();
        assert(output.find("Number of expenses: 1") != std::string::npos);
        assert(output.find("Total spent: 120.00") != std::string::npos);
        assert(output.find("Food: 120.00") != std::string::npos);
        assert(output.find("Transportation: 0.00") != std::string::npos);
        assert(output.find("Utilities: 0.00") != std::string::npos);
    }
}

int main()
{
    testEmptySummary();
    testCategoryTotals();
    testDisplaySummary();

    std::cout << "Expense summary tests passed.\n";
    return 0;
}
