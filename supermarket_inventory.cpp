#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class for storing product information
class Product
{
private:
    int id;
    string name;
    int quantity;
    int minimumStock;
    string expiryDate;          // format DD/MM/YYYY
    string storageRequirement;

public:
    // Constructor
    Product(int i, string n, int q, int minStock,
            string expiry, string storage)
    {
        id = i;
        name = n;
        quantity = q;
        minimumStock = minStock;
        expiryDate = expiry;
        storageRequirement = storage;
    }

    // Display product details
    void display()
    {
        cout << "\nProduct ID: " << id;
        cout << "\nName: " << name;
        cout << "\nQuantity: " << quantity;
        cout << "\nMinimum Stock: " << minimumStock;
        cout << "\nExpiry Date: " << expiryDate;
        cout << "\nStorage: " << storageRequirement << endl;
    }

    // Getters
    int getId() { return id; }
    string getName() { return name; }
    int getQuantity() { return quantity; }
    int getMinimumStock() { return minimumStock; }
    string getExpiryDate() { return expiryDate; }
    string getStorageRequirement() { return storageRequirement; }

    // Check whether product is low in stock
    bool isLowStock()
    {
        return quantity <= minimumStock;
    }

    // Update quantity
    void updateQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }
};


// Convert DD/MM/YYYY into an approximate number of days
// (simple method: 1 month = 30 days, 1 year = 365 days)
int dateToDays(string date)
{
    int day   = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year  = stoi(date.substr(6, 4));

    return year * 365 + month * 30 + day;
}


// Function to add a new product
void addProduct(vector<Product>& products)
{
    int id, quantity, minimumStock;
    string name, expiryDate, storageRequirement;

    cout << "\nEnter Product ID: ";
    cin >> id;
    cin.ignore();                       // clear the Enter key

    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "Enter Minimum Stock Level: ";
    cin >> minimumStock;
    cin.ignore();

    cout << "Enter Expiry Date (DD/MM/YYYY): ";
    getline(cin, expiryDate);

    cout << "Enter Storage Requirement (e.g. Cold, Dry): ";
    getline(cin, storageRequirement);

    Product p(id, name, quantity, minimumStock,
              expiryDate, storageRequirement);

    products.push_back(p);

    cout << "\nProduct added successfully!\n";
}


// Function to display all products
void displayProducts(vector<Product>& products)
{
    if (products.empty())
    {
        cout << "\nNo products available.\n";
        return;
    }

    cout << "\n========== ALL PRODUCTS ==========\n";

    for (int i = 0; i < products.size(); i++)
    {
        products[i].display();
        cout << "--------------------------------\n";
    }
}


// Function to search for a product
void searchProduct(vector<Product>& products)
{
    int id;

    cout << "\nEnter Product ID to search: ";
    cin >> id;

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].getId() == id)
        {
            cout << "\nProduct Found!\n";
            products[i].display();
            return;
        }
    }

    cout << "\nProduct not found.\n";
}


// Function to update product quantity
void updateStock(vector<Product>& products)
{
    int id;
    int newQuantity;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].getId() == id)
        {
            cout << "Enter new quantity: ";
            cin >> newQuantity;

            products[i].updateQuantity(newQuantity);

            cout << "\nStock updated successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found.\n";
}


// Function to display low-stock products
void showLowStock(vector<Product>& products)
{
    bool found = false;

    cout << "\n========== LOW STOCK PRODUCTS ==========\n";

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].isLowStock())
        {
            products[i].display();
            cout << "--------------------------------\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No low-stock products.\n";
    }
}


// Function to show expired products and products close to expiry
void showExpiryProducts(vector<Product>& products)
{
    string today;
    int daysLimit;

    cout << "\nEnter today's date (DD/MM/YYYY): ";
    cin >> today;

    cout << "Show products expiring within how many days? ";
    cin >> daysLimit;

    int todayDays = dateToDays(today);
    bool found = false;

    cout << "\n========== EXPIRY CHECK ==========\n";

    for (int i = 0; i < products.size(); i++)
    {
        int difference = dateToDays(products[i].getExpiryDate()) - todayDays;

        if (difference < 0)
        {
            cout << "\n*** EXPIRED ***";
            products[i].display();
            cout << "--------------------------------\n";
            found = true;
        }
        else if (difference <= daysLimit)
        {
            cout << "\n*** EXPIRING SOON (" << difference << " days left) ***";
            products[i].display();
            cout << "--------------------------------\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No expired or near-expiry products.\n";
    }
}


// Function to generate restocking requirements
void generateRestockReport(vector<Product>& products)
{
    bool found = false;

    cout << "\n========== RESTOCKING REPORT ==========\n";

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].isLowStock())
        {
            cout << "\nProduct: " << products[i].getName();
            cout << "\nCurrent Quantity: " << products[i].getQuantity();
            cout << "\nMinimum Required: " << products[i].getMinimumStock();
            cout << "\nQuantity to Restock: "
                 << products[i].getMinimumStock() - products[i].getQuantity();
            cout << "\n--------------------------------\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "No products need restocking.\n";
    }
}


// Function to delete a product
void deleteProduct(vector<Product>& products)
{
    int id;

    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].getId() == id)
        {
            products.erase(products.begin() + i);

            cout << "\nProduct deleted successfully!\n";
            return;
        }
    }

    cout << "\nProduct not found.\n";
}


// Main function
int main()
{
    vector<Product> products;
    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n   SUPERMARKET INVENTORY SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Add Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Search Product";
        cout << "\n4. Update Stock";
        cout << "\n5. Show Low Stock Products";
        cout << "\n6. Check Expiry";
        cout << "\n7. Generate Restocking Report";
        cout << "\n8. Delete Product";
        cout << "\n9. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        // If the user types a letter instead of a number
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice)
        {
        case 1: addProduct(products); break;
        case 2: displayProducts(products); break;
        case 3: searchProduct(products); break;
        case 4: updateStock(products); break;
        case 5: showLowStock(products); break;
        case 6: showExpiryProducts(products); break;
        case 7: generateRestockReport(products); break;
        case 8: deleteProduct(products); break;
        case 9: cout << "\nThank you for using the system!\n"; break;
        default: cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
