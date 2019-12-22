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
		this->num_of_copies = num_of_copies;
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
	virtual string getGenre() { return "Dummy"; }


	// Setter
	void setID(string id) { ID = id; }
	void setTitle(string title) { Title = title; }
	void setloanType(string loan_type) { loanType = loan_type; }
	void setRentalFee(double rentalFee) { rental_fee = rentalFee; }
	void set_num_of_copies(int num_of_copies) { this->num_of_copies = num_of_copies; }
	void setRentalType(string rentalType) { rental_type = rentalType; };
	virtual void setGenre(string genre) { }

	virtual string toString() {
		return ID + "," + Title + "," + rental_type + "," + loanType + "," + to_string(num_of_copies) + "," + to_string(rental_fee);
	}
};


class Movie : public Items {
private:
	string Genre;
public:
	Movie(string ID, string Title, string rental_type, string loanType, int num_of_copies, double rental_fee, string genre) {
		setID(ID);
		setTitle(Title);
		setRentalType(rental_type);
		setloanType(loanType);
		set_num_of_copies(num_of_copies);
		setRentalFee(rental_fee);
		Genre = genre;
	}
	~Movie() {}
	virtual string getGenre() { return Genre; }
	virtual void setGenre(string genre) { Genre = genre; }
	virtual string toString() {
		return this->getID() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->get_num_of_copies()) + "," + to_string(this->getRentalFee()) + "," + Genre;
	}
};

class DVD : public Items {
private:
	string Genre;
public:
	DVD(string ID, string Title, string rental_type, string loanType, int num_of_copies, double rental_fee, string genre) {
		setID(ID);
		setTitle(Title);
		setRentalType(rental_type);
		setloanType(loanType);
		set_num_of_copies(num_of_copies);
		setRentalFee(rental_fee);
		Genre = genre;
	}
	~DVD() {}
	virtual string getGenre() { return Genre; }
	virtual void setGenre(string genre) { Genre = genre; }
	virtual string toString() {
		return this->getID() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->get_num_of_copies()) + "," + to_string(this->getRentalFee()) + "," + Genre;
	}
};

class Game : public Items {
public:
	Game(string ID, string Title, string rental_type, string loanType, int num_of_copies, double rental_fee) {
		setID(ID);
		setTitle(Title);
		setRentalType(rental_type);
		setloanType(loanType);
		set_num_of_copies(num_of_copies);
		setRentalFee(rental_fee);
	}
	~Game() {}
};

bool checkItemID(string ID) {
	if (ID.length() != 9 || ID[0] != 'I' || !isdigit(ID[1]) || !isdigit(ID[2]) || !isdigit(ID[3]) || ID[4] != '-' || !isdigit(ID[5]) || !isdigit(ID[6]) || !isdigit(ID[7]) || !isdigit(ID[8])) {
		return false;
	}
	return true;
}

bool checkDuplicateItemID(Items** item_list, string ID, int item_list_size) {
	for (int i = 0; i < item_list_size; i++) {
		if (item_list[i]->getID() == ID) {
			return true;
		}
	}
	return false;
}

bool checkRentalType(string rental_type) {
	if (rental_type != "Record" && rental_type != "DVD" && rental_type != "Game") {
		return false;
	}
	return true;
}

bool checkLoanType(string loan_type) {
	if (loan_type != "1-week" && loan_type != "2-day") {
		return false;
	}
	return true;
}

bool checkNumOfCopies(string num_of_copies) {
	for (int i = 0; i < num_of_copies.length(); i++) {
		if (!isdigit(num_of_copies[i])) {
			return false;
		}
	}
	return true;
}

bool isDouble(const char* str)
{
	char* endptr = 0;
	strtod(str, &endptr);

	if (*endptr != '\0' || endptr == str)
		return false;
	return true;
}

bool checkGenre(string genre) {
	if (genre != "Action" && genre != "Horror" && genre != "Dramma" && genre != "Comedy") {
		return false;
	}
	return true;
}

int searchItemID(Items** item_list, int item_list_size) {
	string ID;
	cout << "Enter Item ID: ";
	getline(cin, ID);
	for (int i = 0; i < item_list_size; i++) {
		if (item_list[i]->getID() == ID) {
			return i;
		}
	}
	return -1;
}

Items** deleteItem(Items** item_list, int item_list_size) {
	int index = searchItemID(item_list, item_list_size);
	if (index == -1) {
		cerr << "No match item found" << endl;
	}
	else {
		Items** temp_item_list = new Items * [item_list_size];
		for (int i = 0; i < index; i++) {
			temp_item_list[i] = item_list[i];
		}
		for (int i = index; i < item_list_size - 1; i++) {
			temp_item_list[i] = item_list[i+1];
		}
		temp_item_list[item_list_size-1] = NULL;
		delete[] item_list;
		item_list = temp_item_list;
	}
	cout << "Item deleted" << endl;
	return item_list;
}

Items** addItem(Items** item_list, int item_list_size) {
	string ID, Title, rental_type, loan_type, rental_fee, number_of_copies, genre;
	cout << "Enter item ID (e.g., I201-1999): ";
	getline(cin, ID);
	if (!checkItemID(ID)) {
		cerr << "Invalid item ID format !" << endl;
		return item_list;
	}
	else if (checkDuplicateItemID(item_list, ID, item_list_size)) {
		cerr << "Duplicate item ID !" << endl;
		return item_list;
	}
	cout << "Enter Title: ";
	getline(cin, Title);
	cout << "Enter rental type (Record/DVD/Game): ";
	getline(cin, rental_type);
	if (!checkRentalType(rental_type)) {
		cerr << "Invalid rental type !" << endl;
		return item_list;
	}
	cout << "Enter loan type (1-week/2-day): ";
	getline(cin, loan_type);
	if (!checkLoanType(loan_type)) {
		cerr << "Invalid loan type !" << endl;
		return item_list;
	}
	cout << "Enter number of copies: ";
	getline(cin, number_of_copies);
	if (!checkNumOfCopies(number_of_copies)) {
		cerr << "Invalid number of copies !" << endl;
		return item_list;
	}
	cout << "Enter rental fee: ";
	getline(cin, rental_fee);
	if (!isDouble(rental_fee.c_str())) {
		cerr << "Invalid rental fee !" << endl; 
		return item_list;
	}
	if (rental_type == "Record") {
		cout << "Enter genre: ";
		getline(cin, genre);
		if (!checkGenre(genre)) {
			cerr << "Invalid genre !" << endl;
			return item_list;
		}
		item_list[item_list_size] = new Movie(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee), genre);
	} else if (rental_type == "DVD") {
		cout << "Enter genre: ";
		getline(cin, genre);
		if (!checkGenre(genre)) {
			cerr << "Invalid genre !" << endl;
			return item_list;
		}
		item_list[item_list_size] = new DVD(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee), genre);
	}
	else {
		item_list[item_list_size] = new Game(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee));
	}
	Items** temp_item_list = new Items * [item_list_size + 2];
	for (int i = 0; i < item_list_size+1; i++) {
		temp_item_list[i] = item_list[i];
	}
	temp_item_list[item_list_size + 1] = NULL;
	delete[] item_list;
	item_list = temp_item_list;
	cout << "Item added" << endl;
	return item_list;
}

void displayOutOfStock(Items** item_list, int item_list_size) {
	cout << "Out of stocks items: " << endl;
	for (int i = 0; i < item_list_size; i++) {
		if (item_list[i]->get_num_of_copies() == 0) {
			cout << item_list[i]->toString() << endl;
		}
	}
}

Items** updateItemList(Items** item_list, int item_list_size) {
	string ID, Title, rental_type, loan_type, rental_fee, number_of_copies, genre;
	int index = searchItemID(item_list, item_list_size);
	if (index == -1) {
		cerr << "No match item found" << endl;
	}
	else {
		cout << "Item information: " << item_list[index]->toString() << endl;
		cout << "Enter new item ID (e.g., I201-1999): ";
		getline(cin, ID);
		if (!checkItemID(ID)) {
			cerr << "Invalid item ID format !" << endl;
			return item_list;
		}
		else if (checkDuplicateItemID(item_list, ID, item_list_size)) {
			cerr << "Duplicate item ID !" << endl;
			return item_list;
		}
		cout << "Enter new Title: ";
		getline(cin, Title);
		cout << "Enter rental type (Record/DVD/Game): ";
		getline(cin, rental_type);
		if (!checkRentalType(rental_type)) {
			cerr << "Invalid rental type !" << endl;
			return item_list;
		}
		cout << "Enter new loan type (1-week/2-day): ";
		getline(cin, loan_type);
		if (!checkLoanType(loan_type)) {
			cerr << "Invalid loan type !" << endl;
			return item_list;
		}
		cout << "Enter new number of copies: ";
		getline(cin, number_of_copies);
		if (!checkNumOfCopies(number_of_copies)) {
			cerr << "Invalid number of copies !" << endl;
			return item_list;
		}
		cout << "Enter new rental fee: ";
		getline(cin, rental_fee);
		if (!isDouble(rental_fee.c_str())) {
			cerr << "Invalid rental fee !" << endl;
			return item_list;
		}
		if (rental_type == item_list[index]->getRentalType()) {
			if (rental_type == "Record" || rental_type == "DVD") {
				cout << "Enter new genre: ";
				getline(cin, genre);
				if (!checkGenre(genre)) {
					cerr << "Invalid genre !" << endl;
					return item_list;
				}
				item_list[index]->setGenre(genre);
			}
			item_list[index]->setID(ID);
			item_list[index]->setTitle(Title);
			item_list[index]->setRentalType(rental_type);
			item_list[index]->setloanType(loan_type);
			item_list[index]->set_num_of_copies(stoi(number_of_copies));
			item_list[index]->setRentalFee(stod(rental_fee));
		}
		else {
			if (rental_type == "Record") {
				cout << "Enter new genre: ";
				getline(cin, genre);
				if (!checkGenre(genre)) {
					cerr << "Invalid genre !" << endl;
					return item_list;
				}
				delete item_list[index];
				item_list[index] = new Movie(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee), genre);
			} else if (rental_type == "DVD") {
				cout << "Enter new genre: ";
				getline(cin, genre);
				if (!checkGenre(genre)) {
					cerr << "Invalid genre !" << endl;
					return item_list;
				}
				delete item_list[index];
				item_list[index] = new DVD(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee), genre);
			} else {
				delete item_list[index];
				item_list[index] = new Game(ID, Title, rental_type, loan_type, stoi(number_of_copies), stod(rental_fee));
			}
		}
	}
	cout << "Item updated" << endl;
	return item_list;
}

void displayItemList(Items** item_list, int item_list_size) {
	cout << "All items: " << endl;
	for (int i = 0; i < item_list_size; i++) {
		cout << item_list[i]->toString() << endl;
	}
}

int main() {
	fstream itemRentals;
	itemRentals.open("items.txt", ios::in | ios::out);
	string temp_line;
	Items** item_list = new Items*[1];
	int item_list_size = 1;	

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
		if (itemAttributes[2] == "Record") {
			item_list[item_list_size - 1] = new Movie(itemAttributes[0], itemAttributes[1], itemAttributes[2], itemAttributes[3], stoi(itemAttributes[4]), stod(itemAttributes[5]), itemAttributes[6]);
		}
		else if (itemAttributes[2] == "DVD") {
			item_list[item_list_size - 1] = new DVD(itemAttributes[0], itemAttributes[1], itemAttributes[2], itemAttributes[3], stoi(itemAttributes[4]), stod(itemAttributes[5]), itemAttributes[6]);
		}
		else {
			item_list[item_list_size - 1] = new Game(itemAttributes[0], itemAttributes[1], itemAttributes[2], itemAttributes[3], stoi(itemAttributes[4]), stod(itemAttributes[5]));
		}
		Items** temp_item_list = new Items*[item_list_size + 1];
		for (int i = 0; i < item_list_size; i++) {
			temp_item_list[i] = item_list[i];
		}
		temp_item_list[item_list_size] = NULL;
		delete[] item_list;
		item_list = temp_item_list;
		item_list_size++;
	}
	
	item_list_size--;

	string user_input;
	while (user_input != "Exit") {
		cout << "Enter an option: ";
		getline(cin, user_input);
		if (user_input == "1") { //Add/Update/Delete item
			string suboption;
			cout << "Add, update or delete an item (Add/Update/Delete): ";
			getline(cin, suboption);
			if (suboption == "Add") {
				item_list = addItem(item_list, item_list_size);
				if (item_list[item_list_size] != NULL) {
					item_list_size++;
				}
			} else if (suboption == "Delete") {
				item_list = deleteItem(item_list, item_list_size);
				if (item_list[item_list_size-1] == NULL) {
					item_list_size--;
				}
			} else if (suboption == "Update") {
				item_list = updateItemList(item_list, item_list_size);
				cout << typeid(*item_list[0]).name() << endl;
			}
		} else if (user_input == "2") { //search item
			int index = searchItemID(item_list, item_list_size);
			if (index == -1) {
				cerr << "No match item found" << endl;
			} else {
				cout << "Item information: ";
				cout << item_list[index]->toString() << endl;
			}
		} else if (user_input == "3") { //Print all items
			displayItemList(item_list, item_list_size);
		} else if (user_input == "4") { //Display out of stock items
			displayOutOfStock(item_list, item_list_size);
		} 
	}

	return 0;
}
