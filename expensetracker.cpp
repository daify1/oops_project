#include <iostream>
#include <string>
#include <vector>
#include <limits>    // for numeric_limits

using namespace std;

// Base Class: Expense
class Expense {
protected:
    string category;
    double amount;
    string date;

public:
    Expense(const string& c = "", double a = 0.0, const string& d = "")
        : category(c), amount(a), date(d) {}

    virtual void displayExpense() const {
        cout << category << " Expense: Rs." << amount << " on " << date << endl;
    }

    double getAmount() const { return amount; }
    string getCategory() const { return category; }

    virtual ~Expense() {
        // Destructor for cleanup (if needed later)
    }
};

// Derived Classes
class FoodExpense : public Expense {
public:
    FoodExpense(double a, const string& d) : Expense("Food", a, d) {}
    void displayExpense() const override {
        cout << "🍔 Food Expense: Rs." << amount << " on " << date << endl;
    }
};

class TravelExpense : public Expense {
public:
    TravelExpense(double a, const string& d) : Expense("Travel", a, d) {}
    void displayExpense() const override {
        cout << "🚗 Travel Expense: Rs." << amount << " on " << date << endl;
    }
};

class UtilityExpense : public Expense {
public:
    UtilityExpense(double a, const string& d) : Expense("Utilities", a, d) {}
    void displayExpense() const override {
        cout << "💡 Utility Expense: Rs." << amount << " on " << date << endl;
    }
};

// Manager Class
class ExpenseManager {
    vector<Expense*> expenses;

public:
    void addExpense(Expense* e) {
        expenses.push_back(e);
        cout << "✅ Expense added successfully!\n";
    }

    void showAllExpenses() const {
        if (expenses.empty()) {
            cout << "\nNo expenses recorded yet.\n";
            return;
        }

        cout << "\n----- All Recorded Expenses -----\n";
        for (const auto& e : expenses)
            e->displayExpense();
    }

    void showTotal() const {
        double total = 0.0;
        for (const auto& e : expenses)
            total += e->getAmount();
        cout << "\n💰 Total Expenses: Rs." << total << endl;
    }

    ~ExpenseManager() {
        for (auto e : expenses)
            delete e;
        // optional friendly message
        cout << "\nMemory cleared. Thank you for using Expense Tracker!\n";
    }
};

// Utility function to read a valid double amount
double readAmount() {
    double amt;
    while (true) {
        if (cin >> amt && amt >= 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
            return amt;
        } else {
            cout << "Invalid amount. Enter a non-negative number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Utility function to read a date string (allows spaces if user types)
string readDate() {
    string d;
    getline(cin, d);
    if (d.empty()) {
        // if previous extraction left newline, prompt again
        getline(cin, d);
    }
    return d;
}

// Main Function
int main() {
    ExpenseManager manager;
    int choice = 0;

    do {
        cout << "\n========== EXPENSE TRACKER SYSTEM ==========\n";
        cout << "1. Add Food Expense\n";
        cout << "2. Add Travel Expense\n";
        cout << "3. Add Utility Expense\n";
        cout << "4. View All Expenses\n";
        cout << "5. View Total Expenses\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // consume newline before reading strings
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice >= 1 && choice <= 3) {
            cout << "Enter amount (Rs.): ";
            double amt = readAmount();

            cout << "Enter date (DD/MM/YYYY): ";
            string date = readDate();

            switch (choice) {
                case 1:
                    manager.addExpense(new FoodExpense(amt, date));
                    break;
                case 2:
                    manager.addExpense(new TravelExpense(amt, date));
                    break;
                case 3:
                    manager.addExpense(new UtilityExpense(amt, date));
                    break;
            }
        } else if (choice == 4) {
            manager.showAllExpenses();
        } else if (choice == 5) {
            manager.showTotal();
        } else if (choice == 6) {
            cout << "Exiting... Goodbye!\n";
        } else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
