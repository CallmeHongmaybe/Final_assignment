#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Items {
private:
    string ID;
    string Title;
    string rental_type;
    string loanType;
    string rental_fee;
    string num_of_copies;
    string genre;

public:
    // for
    Items() {};

//    string getID() {return ID;};
//    string getTitle() {return Title;};
//    string getLoanType() {return loanType;};
//    double getRentalFee() {return rental_fee;};
//    int get_num_of_copies() {return num_of_copies;};
//    string getGenre() {return genre;};

    // for updating and retrieving data
    void setID(string &id) {ID = id;}
    void setTitle(string &title) {Title = title;}
    void setRentalType(string &rentalType) { rental_type = rentalType;}
    void setloanType(string &loan_type){ loanType = loan_type;};
    void setRentalFee(string &rentalFee) {rental_fee = rentalFee;};
    void set_num_of_copies (string &numOfCopies) { num_of_copies = numOfCopies;};
    void setGenre(string &Genre) {genre = Genre;};

    string toString() {
        return ID + " , " + Title + " , " + rental_type + " , " + loanType  + " , " + rental_fee + " , " + num_of_copies + genre;
    }

    ~Items() {cout << "Item destructed" << endl;};
};

void displayItems(Items *);

void getRentalsFromFile() {
    fstream itemRentals;
    itemRentals.open("items.txt", ios::in | ios::out);
    string temp_line;
    string itemAttributes[7];

    int attribute_order = 0;
    while (getline(itemRentals, temp_line)) {
        if (temp_line[0] == '#') {
            continue;
        }
        else {
            for (char i : temp_line) {
                itemAttributes[attribute_order] += i;
                if (i == ',') {
                    attribute_order++;
                }
            }

            if (attribute_order == 6) {
                auto *newItem = new Items();
                newItem->setID(itemAttributes[0]);
                newItem->setTitle(itemAttributes[1]);
                newItem->setRentalType(itemAttributes[2]);
                newItem->setloanType(itemAttributes[3]);
                newItem->set_num_of_copies(itemAttributes[4]);
                newItem->setRentalFee(itemAttributes[5]);
                newItem->setGenre(itemAttributes[6]);
                displayItems(newItem);
            }
        }
    }
}

void displayItems(Items *item) {
    cout << item->toString() << endl;
}


int main() {
//    int choice;
//    cout << "Welcome to Genie's video store. Please choose any option below." << endl;
//    cout << "1. Add a new item." << endl;
//    cout << "2. Update an existing item." << endl;
//    cout << "3. Delete an item." << endl;
//    cout << "4. Rent an item" << endl;
//    cout << "5. Return an item. " << endl;
//    cout << "6. Search for an item." << endl;
//    cin >> choice;
//    switch(choice) {
//        case 1:
//            string type;
//            cout << "May I ask for the item type ? " << endl;
//            cin >> type;
//            cout << "To add an item, please enter the ID, title, item type, loan type, number of copies to add and rental fee" << endl;
//            if (type != "game") {
//                cout << "Also give me the genre" << endl;
//            }
//            else if (type == "movie") {
//                cout << "move" << endl;
//            }
//            else if (type == "dvd") {
//                cout << "ded" << endl;
//            }
//    }
    getRentalsFromFile();
    return 0;
};
