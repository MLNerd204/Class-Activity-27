#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    int quantity;
    double price;

    Book(string t, string a, string i, int q, double p)
        : title(t), author(a), isbn(i), quantity(q), price(p) {}

    bool operator==(const Book& other) const {
        return isbn == other.isbn;
    }

    friend ostream& operator<<(ostream& out, const Book& book) {
        out << "Title: " << book.title << "\n"
            << "Author: " << book.author << "\n"
            << "ISBN: " << book.isbn << "\n"
            << "Quantity: " << book.quantity << "\n"
            << "Price: $" << book.price << endl;
        return out;
    }
};

class Bookstore {
private:
    vector<Book> inventory;

public:
    void addBook(const Book& book) {
        auto it = find(inventory.begin(), inventory.end(), book);
        if (it != inventory.end()) {
            it->quantity += book.quantity;
        } else {
            inventory.push_back(book);
        }
    }

    Book* findBook(const string& isbn) {
        for (auto& book : inventory) {
            if (book.isbn == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    
    void displayInventory() const {
        if (inventory.empty()) {
            cout << "The bookstore inventory is empty.\n";
        } else {
            for (const auto& book : inventory) {
                cout << book << endl;
            }
        }
    }
};

int main() {
    Bookstore bookstore;

    bookstore.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "9780316769488", 10, 15.99));
    bookstore.addBook(Book("1984", "George Orwell", "9780451524935", 5, 12.99));
    bookstore.addBook(Book("To Kill a Mockingbird", "Harper Lee", "9780061120084", 7, 14.99));

    cout << "Current Inventory:\n";
    bookstore.displayInventory();

    bookstore.addBook(Book("1984", "George Orwell", "9780451524935", 3, 12.99));

    cout << "\nInventory after adding more copies of '1984':\n";
    bookstore.displayInventory();

    string searchIsbn = "9780316769488";
    Book* foundBook = bookstore.findBook(searchIsbn);
    if (foundBook) {
        cout << "\nBook found with ISBN " << searchIsbn << ":\n" << *foundBook;
    } else {
        cout << "\nBook with ISBN " << searchIsbn << " not found.\n";
    }

    return 0;
}
