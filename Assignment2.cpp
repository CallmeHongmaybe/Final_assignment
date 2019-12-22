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
    string getRentalType() {return rental_type;};
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
        return ID + "," + Title + "," + rental_type + "," + loanType  + "," + num_of_copies  + "," + rental_fee + "," + genre;
    }

    ~Items() {};
};

void displayItems(Items *, int listSize);
int searchForItem(Items *, int listSize, const string &basicString);
void updateItem(Items *, int listSize);
//void autoSaver(Items *item, int list_size, ofstream fileWriter);
void printMenu();

int main() {
    ifstream itemRentals;
    string itemFile = "items.txt";
    itemRentals.open(itemFile.c_str(), ios::in);
    string temp_line;
    string itemAttributes[7];

    int item_list_size = 1;
    auto *itemsList = new Items[1];

    while (getline(itemRentals, temp_line)) {
            string delimiter = ",";     // initialize a delimiter and the token
            string itemAttribute;

            size_t pos = 0;
            int attribute_order = 0;
            while ((pos = temp_line.find(delimiter)) != string::npos) {     // npos here means until the end of a string
                itemAttribute = temp_line.substr(0, pos);              // extract attribute first
                itemAttributes[attribute_order] = itemAttribute;
                attribute_order++;                                          // prints attribute
                temp_line.erase(0, pos + delimiter.length());       // deletes the token with its delimiter and move to the next attribute
            }
            string lastAttribute = temp_line; // the last of temp_line to attribute no.7 and erasing trailing \r
            if (itemAttributes[5].empty()) {
                itemAttributes[5] = lastAttribute;
                itemAttributes[6] = "";
            }
            else itemAttributes[6] = lastAttribute;


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
            auto dummyList = new Items[item_list_size + 1];
            for (int i = 0; i < item_list_size; i++) {
                dummyList[i] = itemsList[i];
            }
            delete[] itemsList;
            itemsList = dummyList;
            item_list_size++;
        }
    item_list_size--;
    itemRentals.close();

//    ofstream fileWriter;
//    fileWriter.open(itemFile.c_str(), ios::out);

        string choice;
        while(choice != "Exit") {
            printMenu();
            cin >> choice;
            switch(stoi(choice)) {
                case 1:
                case 2:
                    updateItem(itemsList, item_list_size);
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                    displayItems(itemsList, item_list_size);
                    break;
                case 7:
                    string requestedID;
                    cout << "Can I ask for the ID please? " << endl;
                    cin >> requestedID;
                    int index = searchForItem(itemsList, item_list_size, requestedID);
                    cout << itemsList[index].toString() << endl;
                    break;
            }
//            for (int i = 0; i < item_list_size; i++) {
//                fileWriter << itemsList[i].toString() << endl;
//            }
        }

//        if (choice == "Exit") {
//            fileWriter.close();
//        }


    return 0;
};

void displayItems(Items *item, int list_size) {
    for (int i = 0; i < list_size ; i++) {
        cout << item[i].toString() << endl;
    }
}

int searchForItem(Items *item, int list_size, const string& requestedID) {
    int found = 0;
    int index = 0;
    for (int i = 0; i < list_size ; i++) {
        string id = item[i].getID();                         // getting the id firsthand
//        string trimmedID = id.erase(id.length() - 2);   // trimming spaces in between
        if (id == requestedID) {
            found++;
            break;
        }
        else {
            index++;
        }
    }
    if (found == 0) {
        cout << "No item matches your query" << endl;
    }
    return index;
}

void updateItem(Items *item, int list_size) {
    string ID;
    cout << "Tell me the ID of a product you want to edit" << endl;
    cin >> ID;
    cout << "Enter each field accordingly. Enter to skip the part you don't want to edit." << endl;
    string prompts[7] = {"ID", "Title", "Rental type", "Loan type", "No. of copies", "Rental fee", "Genre"};
    string itemData[7];

    int index = searchForItem(item, list_size, ID);
    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            cin.ignore();
        }
        cout << prompts[i] << " = ";
        getline(cin, itemData[i]);
    }

    if (!itemData[0].empty()) item[index].setID(itemData[0]);
    if (!itemData[1].empty()) item[index].setTitle(itemData[1]);
    if (!itemData[2].empty()) item[index].setRentalType(itemData[2]);
    if (!itemData[3].empty()) item[index].setloanType(itemData[3]);
    if (!itemData[4].empty()) item[index].set_num_of_copies(itemData[4]);
    if (!itemData[5].empty()) item[index].setRentalFee(itemData[5]);
    if (!itemData[6].empty()) item[index].setGenre(itemData[6]);
}

void printMenu() {
    cout << "#################" << endl;
    cout << "Welcome to Genie's video store. Please choose any option below." << endl;
    cout << "1. Add a new item." << endl;
    cout << "2. Update an existing item." << endl;
    cout << "3. Delete an item." << endl;
    cout << "4. Rent an item" << endl;
    cout << "5. Return an item. " << endl;
    cout << "6. Display all items" << endl;
    cout << "7. Search for an item." << endl;
    cout << "################" << endl;
}





