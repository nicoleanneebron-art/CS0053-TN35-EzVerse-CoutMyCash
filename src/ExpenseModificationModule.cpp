#include "ExpenseModificationModule.h"
#include "Expense.h"

#include <vector>

using namespace std;

// Find the position of an expense using its ID
static int findExpenseById(const vector<Expense>& expenses, int expenseId){
    for (int i = 0; i < static_cast<int>(expenses.size()); i++)
    {
        if (expenses[i].expenseId == expenseId)
        {
            return i;
        }
    }

    return -1;
}