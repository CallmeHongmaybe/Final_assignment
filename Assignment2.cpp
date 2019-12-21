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

    string getID() {return ID;};
    string getTitle() {return Title;};
    string getLoanType() {return loanType;};
    string getRentalFee() {return rental_fee;};
    string get_num_of_copies() {return num_of_copies;};
    string getGenre() {return genre;};

    // for updating and retrieving data
    void setID(string &id) {ID = id;}
    void setTitle(string &title) {Title = title;}
    void setRentalType(string &rentalType) { rental_type = rentalType;}
    void setloanType(string &loan_type){ loanType = loan_type;};
    void setRentalFee(string &rentalFee) {rental_fee = rentalFee;};
    void set_num_of_copies (string &numOfCopies) { num_of_copies = numOfCopies;};
    void setGenre(string &Genre) {genre = Genre;};

    string toString() {
        return ID + " , " + Title + " , " + rental_type + " , " + loanType  + " , " + num_of_copies  + " , " + rental_fee + " , " + genre;
    }

    ~Items() {};
};

void displayItems(Items *, int i);

void getRentalsFromFile(ifstream &rentalStream) {      // returns item list from file
    string temp_line;
    string itemAttributes[7];

    int item_list_size = 1;

    auto *itemsList = new Items[item_list_size];

    while (getline(rentalStream, temp_line)) {
        if (temp_line[0] == '#') {
            continue;
        }
        else {
            string delimiter = ",";     // initialize a delimiter and the token
            string itemAttribute;
//
            size_t pos = 0;
            int attribute_order = 0;
            while ((pos = temp_line.find(delimiter)) != string::npos) {     // npos here means until the end of a string
                itemAttribute = temp_line.substr(0, pos);              // extract attribute first
                itemAttributes[attribute_order] = itemAttribute;
                attribute_order++;                                          // prints attribute
                temp_line.erase(0, pos + delimiter.length());       // deletes the token with its delimiter and move to the next attribute
            }
                if (itemAttributes[5].empty()) {
                    itemAttributes[5] = temp_line.erase(temp_line.length() - 1);
                    itemAttributes[6] = "";
                }
                else itemAttributes[6] = temp_line.erase(temp_line.length() - 1);  // assign the last of temp_line to attribute no.7 and erasing trailing \r


            // initialize a new item
            auto newItem = new Items();
            newItem->setID(itemAttributes[0]);
            newItem->setTitle(itemAttributes[1]);
            newItem->setRentalType(itemAttributes[2]);
            newItem->setloanType(itemAttributes[3]);
            newItem->set_num_of_copies(itemAttributes[4]);
            newItem->setRentalFee(itemAttributes[5]);
            newItem->setGenre(itemAttributes[6]);
            // add item into item list
                itemsList[item_list_size - 1] = *newItem;
                item_list_size++;
        }
        // export item list
                displayItems(itemsList, item_list_size);
                item_list_size--;
    }

}


int main() {
    ifstream itemRentals;
    string itemFile = "items.txt";
    itemRentals.open(itemFile.c_str(), ios::in | ios::out);
    getRentalsFromFile(itemRentals);
    itemRentals.close();
    return 0;
};

void displayItems(Items *item, int list_size) {
    for (int i = 0; i < list_size ; i++) {
        cout << item[i].toString() << endl;
    }
}

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



