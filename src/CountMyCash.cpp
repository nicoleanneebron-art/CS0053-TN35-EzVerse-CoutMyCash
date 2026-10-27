#include "ExpenseInputModule.h"
#include "ExpenseManagementModule.h"
#include "ExpenseModificationModule.h"
#include "ExpenseSummaryModule.h"
#include "FileStorageModule.h"
#include <iostream>



int main()
{
    if (!initializeStorage())
    {
        std::cout << "Error: Could not initialize storage.\n";
        return 1;
    }

    std::cout << "Creating a Personal Expense Tracker..." << std::endl;
    return 0;
}
