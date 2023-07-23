#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include <fstream> // Include the header for file handling

struct Expense {
    std::string description;
    double amount;
};

// Function to add an expense
void AddExpense(std::vector<Expense>& expenses) {
    Expense NewExpense;
    std::cout << "Enter Expense Description: ";
    std::cin.ignore(); // Ignore the newline left in the buffer after previous input
    std::getline(std::cin, NewExpense.description);

    std::cout << "Enter Expense Amount: ";
    std::cin >> NewExpense.amount;

    expenses.push_back(NewExpense);
    std::cout << "Expense Added Successfully!\n";
}

// Function to load expenses from the file
void LoadExpensesFromFile(std::vector<Expense>& expenses) {
    std::ifstream inFile("expenses.txt");
    if (inFile.is_open()) {
        Expense expense;
        while (std::getline(inFile, expense.description, ',')) {
            inFile >> expense.amount;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the newline character
            expenses.push_back(expense);
        }
        inFile.close();
    }
}

// Function to save expenses to the file
void SaveExpensesToFile(const std::vector<Expense>& expenses) {
    std::ofstream outFile("expenses.txt");
    if (outFile.is_open()) {
        for (const auto& expense : expenses) {
            outFile << expense.description << "," << expense.amount << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Error: Unable to save the expenses to the file.\n";
    }
}

// Function to edit an expense
void EditExpense(std::vector<Expense>& expenses) {
    int index;
    std::cout << "Enter the index of the expense to edit (starting from 0): ";
    std::cin >> index;

    if (index >= 0 && index < expenses.size()) {
        std::cout << "Enter the new Expense Description: ";
        std::cin.ignore();
        std::getline(std::cin, expenses[index].description);

        std::cout << "Enter the new Expense Amount: ";
        std::cin >> expenses[index].amount;

        std::cout << "Expense Edited Successfully!\n";

        SaveExpensesToFile(expenses); // Save the updated expenses to the file
    } else {
        std::cout << "Invalid index. No expense found at the specified index.\n";
    }
}

// Function to delete an expense
void DeleteExpense(std::vector<Expense>& expenses) {
    int index;
    std::cout << "Enter the index of the expense to delete (starting from 0): ";
    std::cin >> index;

    if (index >= 0 && index < expenses.size()) {
        expenses.erase(expenses.begin() + index);
        std::cout << "Expense Deleted Successfully!\n";

        SaveExpensesToFile(expenses); // Save the updated expenses to the file
    } else {
        std::cout << "Invalid index. No expense found at the specified index.\n";
    }
}

// Function to calculate total expenses
double TotalExpenses(const std::vector<Expense>& expenses) {
    double total = 0.0;
    for (const auto& expense : expenses) {
        total += expense.amount;
    }
    return total;
}

// Function to display all expenses
void displayExpenses(const std::vector<Expense>& expenses) {
    std::cout << "------- Expenses -------\n";
    for (const auto& expense : expenses) {
        std::cout << "Description: " << expense.description << ", Amount: " << expense.amount << "\n";
    }
    std::cout << "------------------------\n";
}

// Function to convert currency
double convertCurrency(double amount, double exchangeRate) {
    return amount * exchangeRate;
}

int main() {
    std::vector<Expense> expenses;
    char choice;
    bool isFileLoaded = false;

    std::cout << "\nHello! I am MUKTADIR, Welcome to my 'Expense Tracker & Currency Converter'\n";

    // Load expenses from the file (if the file exists)
    LoadExpensesFromFile(expenses);
    isFileLoaded = true;

    do {
        std::cout << "\n'Expense Tracker & Currency Converter' Menu:\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. View Total Expenses\n";
        std::cout << "3. View All Expenses\n";
        std::cout << "4. Convert Currency\n";
        std::cout << "5. Edit Expense\n";
        std::cout << "6. Delete Expense\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice (1/2/3/4/5/6/7): ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                AddExpense(expenses);
                break;
            case '2':
                std::cout << "Total Expenses: TK " << TotalExpenses(expenses) << "\n";
                break;
            case '3':
                displayExpenses(expenses);
                break;
            case '4': {
                // Exchange rates (Fictional and Outdated - Replace with real-time rates)
                std::map<std::string, double> exchangeRates = {

                    {"AED",0.034},//United Arab Emirates dirham
                    {"AUD",0.014},//Australian Dollar
                    {"BRL",0.044},//Brazilian real
                    {"BDT",1},
                    {"CAD",0.012},//Canadian dollar
                    {"CYR",0.066},//  Chinese Yuan Renminbi
                    {"CHF",0.0080},//Swiss franc
                    {"EUR",0.0083},//The euro
                    {"EGP",0.28},// Egyptian Pound
                    {"GBP",0.0072},//British pound sterling
                    {"HKD",0.072},//Hong Kong Dollar
                    {"INR",0.763},//Indian rupee
                    {"IRR",0.0026},//Iranian Rial
                    {"JPY",0.765},//Japanese yen
                    {"NZD",0.015},//New Zealand dollar
                    {"PKR",2.64},//Pakistan Rupee
                    {"SAR",0.035},//Saudi Riyal
                    {"SRD",0.012},//Singapore Dollar
                    {"SLR",3.02},// Sri Lanka Rupee
                    {"TRY",0.25},//Turkish Lira
                    {"USD",0.0092},//United States dollar
                    {"hrn",0.34},// Ukraine Hryvnia
                };

                double amount;
                std::string fromCurrency, toCurrency;

                std::cout << "Currency Converter (with respect to Bangladeshi Taka - BDT)" << std::endl;

                std::cout << "Available Currencies:" << std::endl;
                for (const auto& rate : exchangeRates) {
                    std::cout << rate.first << " ";
                }
                std::cout << std::endl;

                std::cout << "Enter the amount: ";
                std::cin >> amount;

                std::cout << "Enter the currency to convert from (e.g., BDT): ";
                std::cin >> fromCurrency;

                std::cout << "Enter the currency to convert to (e.g., USD): ";
                std::cin >> toCurrency;

                if (exchangeRates.find(fromCurrency) == exchangeRates.end() || exchangeRates.find(toCurrency) == exchangeRates.end()) {
                    std::cout << "Invalid currency selection." << std::endl;
                    return 1;
                }

                double exchangeRateFrom = exchangeRates[fromCurrency];
                double exchangeRateTo = exchangeRates[toCurrency];

                double result = convertCurrency(amount / exchangeRateFrom, exchangeRateTo);

                std::cout << amount << " " << fromCurrency << " is equal to " << result << " " << toCurrency << "." << std::endl;
            }
            break;
            case '5':
                EditExpense(expenses);
                break;
            case '6':
                DeleteExpense(expenses);
                break;
            case '7':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '7');

    if (isFileLoaded) {
        SaveExpensesToFile(expenses); // Save the final expenses to the file before exiting
    }

    return 0;
}
