#include "pch.h"
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
	double rental_fee;
	int num_of_copies;

public:
	Items() {}
	Items(string ID, string Title, string rental_type, string loanType, int num_of_copies, double rental_fee) {
		this->ID = ID;
		this->Title = Title;
		this->rental_type = rental_type;
		this->loanType = loanType;
		this->rental_fee = rental_fee;
	}
	~Items() {}
	// Getter
	string getID() { return ID; }
	string getTitle() { return Title; }
	string getRentalType() { return rental_type; }
	string getLoanType() { return loanType; }
	double getRentalFee() { return rental_fee; }
	int get_num_of_copies() { return num_of_copies; }


	// Setter
	void setID(string id) { ID = id; }
	void setTitle(string title) { Title = title; }
	void setloanType(int loan_type) { loanType = loan_type; }
	void setRentalFee(double rentalFee) { rental_fee = rentalFee; }
	void set_num_of_copies(int num_of_copies) { num_of_copies = num_of_copies; }

	string toString() {
		return ID + "," + Title + "," + rental_type + "," + loanType + "," + to_string(rental_fee);
	}
};


class Movie : public Items {
private:
	string Genre;
public:
	Movie(string ID, string Title, int loanType, double rental_fee) {
		setID(ID);
		setTitle(Title);
		setloanType(loanType);
		setRentalFee(rental_fee);
	}
	~Movie() {}
	string setGenre(string& genre) { Genre = genre; }
	string toString() {
		return this->getID() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getRentalFee()) + "," + Genre;
	}
};

class DVD : public Items {
private:
	string Genre;
public:
	DVD(string ID, string Title, int loanType, double rental_fee) {
		setID(ID);
		setTitle(Title);
		setloanType(loanType);
		setRentalFee(rental_fee);
	}
	~DVD() {}
	string setGenre(string& genre) { Genre = genre; }
	string toString() {
		return this->getID() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getRentalFee()) + "," + Genre;
	}
};

class Game : public Items {
public:
	Game(string ID, string Title, int loanType, double rental_fee) {
		setID(ID);
		setTitle(Title);
		setloanType(loanType);
		setRentalFee(rental_fee);
	}
	~Game() {}
};

void displayItems(Items* item) {
	cout << item->toString() << endl;
}

void getRentalsFromFile() {
	fstream itemRentals;
	itemRentals.open("items.txt", ios::in | ios::out);
	string temp_line;

	while (getline(itemRentals, temp_line)) {
		string itemAttributes[7];
		int attribute_order = 0;
		char current_char = NULL;

		if (temp_line[0] == '#') {
			continue;
		}

		for (int i = 0; i < temp_line.length(); i++) {
			current_char = temp_line[i];
			if (current_char == ',') {
				attribute_order++;
			}
			else {
				itemAttributes[attribute_order] += current_char;
			}
		}
		displayItems(new Items(itemAttributes[0], itemAttributes[1], itemAttributes[2], itemAttributes[3], stoi(itemAttributes[4]), stod(itemAttributes[5])));
	}

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
}
