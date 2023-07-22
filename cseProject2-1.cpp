#include <iostream>
#include <vector>
#include <string>
#include <map>

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
std::cout << "\nHello! I am MUKTADIR, Welcome to my 'Expense Tracker & Currency Converter'\n";
    do {
        std::cout << "\n'Expense Tracker & Currency Converter' Menu:\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. View Total Expenses\n";
        std::cout << "3. View All Expenses\n";
        std::cout << "4. Convert Currency\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1/2/3/4/5): ";
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

                    {"AED",29.533},//United Arab Emirates dirham
                    {"AUD",72.993},//Australian Dollar
                    {"BRL",22.7},//Brazilian real
                    {"BDT",1},
                    {"CAD",81.989},//Canadian dollar
                    {"CYR",15.09},//  Chinese Yuan Renminbi
                    {"CHF",125.278},//Swiss franc
                    {"EUR",120.717},//The euro
                    {"EGP",3.524},// Egyptian Pound
                    {"GBP",139.472},//British pound sterling
                    {"HKD",13.87},//Hong Kong Dollar
                    {"INR",1.323},//Indian rupee
                    {"IRR",0.0026},//Iranian Rial
                    {"JPY",0.765},//Japanese yen
                    {"NZD",67.016},//New Zealand dollar
                    {"PKR",0.3785},//Pakistan Rupee
                    {"SAR",28.94},//Saudi Riyal
                    {"SRD",81.52},//Singapore Dollar
                    {"SLR",0.3307},// Sri Lanka Rupee
                    {"TRY",4.021},//Turkish Lira
                    {"USD",108.475},//United States dollar
                    {"hrn",2.953},// Ukraine Hryvnia
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
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '5');

    return 0;
}
