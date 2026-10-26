#include "FileStorageModule.h"

#include <filesystem>
#include <exception>
#include <fstream>
#include <iomanip>
#include <string>
#include <system_error>
#include <vector>

namespace
{
    const std::string EXPENSES_FILE_PATH = "data/expenses.csv";
    const std::string CSV_HEADER = "expenseId,description,categoryId,amount,date";

    std::string escapeCsvField(const std::string& value)
    {
        std::string escapedValue = "\"";

        for (char character : value)
        {
            if (character == '\"')
            {
                escapedValue += "\"\"";
            }
            else
            {
                escapedValue += character;
            }
        }

        escapedValue += "\"";
        return escapedValue;
    }

    bool parseCsvLine(const std::string& line, std::vector<std::string>& fields)
    {
        fields.clear();
        std::string field;
        bool insideQuotes = false;

        for (std::size_t index = 0; index < line.length(); ++index)
        {
            const char character = line[index];

            if (character == '\"')
            {
                if (insideQuotes && index + 1 < line.length() && line[index + 1] == '\"')
                {
                    field += '\"';
                    ++index;
                }
                else
                {
                    insideQuotes = !insideQuotes;
                }
            }
            else if (character == ',' && !insideQuotes)
            {
                fields.push_back(field);
                field.clear();
            }
            else
            {
                field += character;
            }
        }

        if (insideQuotes)
        {
            return false;
        }

        fields.push_back(field);
        return true;
    }

    bool createExpenseFromFields(const std::vector<std::string>& fields, Expense& expense)
    {
        if (fields.size() != 5)
        {
            return false;
        }

        try
        {
            std::size_t parsedCharacters = 0;
            expense.expenseId = std::stoi(fields[0], &parsedCharacters);
            if (parsedCharacters != fields[0].length())
            {
                return false;
            }

            expense.categoryId = std::stoi(fields[2], &parsedCharacters);
            if (parsedCharacters != fields[2].length())
            {
                return false;
            }

            expense.amount = std::stod(fields[3], &parsedCharacters);
            if (parsedCharacters != fields[3].length())
            {
                return false;
            }
        }
        catch (const std::exception&)
        {
            return false;
        }

        expense.description = fields[1];
        expense.date = fields[4];
        return true;
    }
}

bool initializeStorage()
{
    std::error_code error;
    std::filesystem::create_directories("data", error);

    if (error)
    {
        return false;
    }

    if (std::filesystem::exists(EXPENSES_FILE_PATH, error))
    {
        return !error;
    }

    std::ofstream expensesFile(EXPENSES_FILE_PATH);
    if (!expensesFile)
    {
        return false;
    }

    expensesFile << CSV_HEADER << '\n';
    return expensesFile.good();
}

bool loadExpenses(std::vector<Expense>& expenses)
{
    if (!initializeStorage())
    {
        return false;
    }

    std::ifstream expensesFile(EXPENSES_FILE_PATH);
    if (!expensesFile)
    {
        return false;
    }

    std::string line;
    if (!std::getline(expensesFile, line) || line != CSV_HEADER)
    {
        return false;
    }

    std::vector<Expense> loadedExpenses;
    std::vector<std::string> fields;

    while (std::getline(expensesFile, line))
    {
        if (!parseCsvLine(line, fields))
        {
            return false;
        }

        Expense expense;
        if (!createExpenseFromFields(fields, expense))
        {
            return false;
        }

        loadedExpenses.push_back(expense);
    }

    expenses = loadedExpenses;
    return true;
}

bool saveExpenses(const std::vector<Expense>& expenses)
{
    if (!initializeStorage())
    {
        return false;
    }

    std::ofstream expensesFile(EXPENSES_FILE_PATH);
    if (!expensesFile)
    {
        return false;
    }

    expensesFile << CSV_HEADER << '\n';
    expensesFile << std::fixed << std::setprecision(2);

    for (const Expense& expense : expenses)
    {
        expensesFile << expense.expenseId << ','
                     << escapeCsvField(expense.description) << ','
                     << expense.categoryId << ','
                     << expense.amount << ','
                     << escapeCsvField(expense.date) << '\n';
    }

    return expensesFile.good();
}
