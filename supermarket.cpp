#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
class Product {
protected:
    string name;
    double price;
    int expirationYear;
    int expirationMonth;
    int expirationDay;

public:
    Product(const string& n, double p, int year, int month, int day)
        : name(n), price(p), expirationYear(year), expirationMonth(month), expirationDay(day) {}

    virtual void display() const {
        cout << setw(20) << left << name << setw(10) << right << price;
    }

    virtual double calculateCost(int quantity) const {
        return price * quantity;
    }

    virtual string getExpirationDate() const {
        return to_string(expirationDay) + "/" + to_string(expirationMonth) + "/" + to_string(expirationYear);
    }

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

class Supermarket {
private:
    vector<Product*> products;
    vector<pair<string, int>> customerBasket;

public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    void displayProducts() const {
        cout << setw(20) << left << "Product Name" << setw(10) << right << "Price" << setw(20) << right << "Expiry Date" << endl;
        cout << string(60, '-') << endl;

        for (const auto& product : products) {
            product->display();
            cout << setw(20) << right << product->getExpirationDate() << endl;
        }
    }

    void addToBasket(const string& productName, int quantity) {
        customerBasket.emplace_back(productName, quantity);
    }

    void displayBasket() const {
        cout << "\nItems in Your Basket:" << endl;
        cout << setw(20) << left << "Product Name" << setw(10) << right << "Quantity" << setw(10) << right << "Price" << endl;
        cout << string(40, '-') << endl;

        for (const auto& item : customerBasket) {
            for (const auto& product : products) {
                if (product->getName() == item.first) {
                    cout << setw(20) << left << item.first << setw(10) << right << item.second << setw(10) << right
                         << product->calculateCost(item.second) << endl;
                    break;
                }
            }
        }
    }

    double calculateTotalCost() const {
        double totalCost = 0.0;

        for (const auto& item : customerBasket) {
            for (const auto& product : products) {
                if (product->getName() == item.first) {
                    totalCost += product->calculateCost(item.second);
                    break;
                }
            }
        }

        return totalCost;
    }

    void adminAddProducts() {
        int numProducts;
        cout << "Enter the number of products to add: ";
        cin >> numProducts;

        for (int i = 0; i < numProducts; ++i) {
            string name;
            double price;
            int expirationYear, expirationMonth, expirationDay;

            cout << "Product Name: ";
            cin >> name;

            cout << "Product Price: $";
            cin >> price;

            do {
                cout << "Expiration Year (between 1 and 9999): ";
                cin >> expirationYear;
            } while (expirationYear < 1 || expirationYear > 9999);

            do {
                cout << "Expiration Month (between 1 and 12): ";
                cin >> expirationMonth;
            } while (expirationMonth < 1 || expirationMonth > 12);

            do {
                cout << "Expiration Day (between 1 and 30): ";
                cin >> expirationDay;
            } while (expirationDay < 1 || expirationDay > 30);

            addProduct(new Product(name, price, expirationYear, expirationMonth, expirationDay));
        }

        cout << "Products added successfully.\n";
    }

    // ... (rest of the class remains the same)
};

int main() {
    Supermarket supermarket;

    cout << "Are you the owner or a customer? (owner/customer): ";
    string userType;
    cin >> userType;

    if (userType == "owner") {
        supermarket.adminAddProducts();
        supermarket.displayProducts();
    } else if (userType == "customer") {
        // Implement customer functionality
        // ...

    }

    return 0;
}