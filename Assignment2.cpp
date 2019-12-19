// Items side 
class Items {
private:
    string ID;
    string Title;
    string rental_type;
    int loanType;
    double rental_fee;
    int num_of_copies;
    string genre;

public:
    // for
    string getID() {return ID;};
    string getTitle() {return Title;};
    int getLoanType() {return loanType;};
    double getRentalFee() {return rental_fee;};
    int get_num_of_copies() {return num_of_copies;};
    string getGenre() {return genre;};

    // for updating and retrieving data
    void setID(string id) {ID = id;};
    void setTitle(string title) {Title = title;};
    void setloanType(int loan_type){ loanType = loan_type;};
    void setRentalFee(double rentalFee) {rental_fee = rentalFee;};
    void set_num_of_copies (int num_of_copies) {num_of_copies = num_of_copies;};

    string toString() {
        return this->ID + " " + this->Title + " " + to_string(this->loanType)  + " " + to_string(this->rental_fee) + " " + to_string(this->borrowed);
    }
};


class Movie: public Items {
private:
    string Genre;
public:
    Movie(string ID, string Title, int loanType, double rental_fee) {
        setID(ID);
        setTitle(Title);
        setloanType(loanType);
        setRentalFee(rental_fee);
    };
    ~Movie() {};
    string setGenre(string &genre) {Genre = genre;}
};

class DVD: public Items {
private:
public:
    DVD(string ID, string Title, int loanType, double rental_fee) {
        setID(ID);
        setTitle(Title);
        setloanType(loanType);
        setRentalFee(rental_fee);
    }
    string setGenre(string &genre) {Genre = genre;}
};

class Game: public Items {
private:
    string rentalType = "Game";
public:
    Game(string ID, string Title, int loanType, double rental_fee) {
        setID(ID);
        setTitle(Title);
        setloanType(loanType);
        setRentalFee(rental_fee);
    }
    string getRentalType() {
        return rentalType;
    }

};

void getRentalsFromFile() {
    fstream itemRentals;
    itemRentals.open("items.txt", ios::in | ios::out);
    string temp_line;
    string itemAttributes[6];

    int attribute_order = 0;
    while (getline(itemRentals, temp_line)) {
        if (temp_line[0] == '#') {
            continue;
        }
        for (int i = 0; i <= temp_line.length() - 1; ++i) {
            itemAttributes[attribute_order] += temp_line[i];
            if (temp_line[i] == ',') {
                attribute_order++;
                break;
            }
        }

        if (itemAttributes[2] == "game") {
            displayItems(new Items(itemAttributes[0], itemAttributes[1], itemAttributes[2], itemAttributes[3], itemAttributes[4], itemAttributes[5], itemAttributes[6]));
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
