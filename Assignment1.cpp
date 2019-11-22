#include "pch.h"
#include <iostream>

using namespace std;

//int converToInt(char *number) {
//	int toint = 0;
//	int start_digit = 0;
//	if (number[0] == '-' || number[0] == '+') {
//		start_digit = 1;
//	}
//	int i = start_digit;
//	while (number[i] >= '0' && number[i] <= '9') {
//		toint *= 10;
//		toint += number[i] - '0';
//		i++;
//	}
//	if (number[0] == '-') {
//		return (-1 * toint);
//	}
//	else {
//		return toint;
//	}
//}

bool isInt(char *number) {
	bool isdot = false;
	int start_digit = 0;
	if (number[0] != '-' && number[0] != '+' && number[0] != '.' && !isdigit(number[0])) {
		return false;
	} else if (number[0] == '-' || number[0] == '+') {
		start_digit = 1;
	}
	for (char i = start_digit; i < strlen(number); i++) {
		if (!isdot) {
			if (number[i] == '.') {
				isdot = true;
			} else if (!isdigit(number[i])) {
				return false;
			}
		} else if (number[i] != '0') {
			return false;
		}
	}
	return true;
}

//bool isOp(char *number) {
//	if (strlen(number) > 1) {
//		return false;
//	} else if (number[0] != '%' && number[0] != '/' && number[0] != '+' && number[0] != '-' && number[0] != '*' && number[0] != '^') {
//		return false;
//	}
//}
//
//bool checkArgument(char *item, char *prev_item, bool isnum) {
//	if (isnum) {
//		if (!isInt(item)) {
//			cout << "Invalid Integer" << endl;
//			return false;
//		} else if (converToInt(item) < -32768 || converToInt(item) > 32767) {
//			cout << "Integer out of range" << endl;
//			return false;
//		} else if (strcmp(item, "0") == 0 && strcmp(prev_item, "/") == 0) {
//			cout << "Division by 0" << endl;
//			return false;
//		}
//	} else if (!isOp(item)) {
//		cout << "Invalid operator!" << endl;
//		return false;
//	} else {
//		return true;
//	}
//}
//
//bool checkParen(char *item) {
//	if (item[0] != '-' || item[0] != '+' || item[0] != ' ' || item[0] != NULL) {
//		cout << "Wrong grammar" << endl;
//		return false;
//	}
//}

bool findChar(char c, char *line) {
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == c) {
			return true;
		}
	}
	return false;
}

bool checkNum(char *num) {
	if (isInt(num)) {
		if (atoi(num) >= -32768 && atoi(num) <= 32767) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool checkParen(char *paren_s, char paren_type) {
	if (paren_type == ')') {
		if (strlen(paren_s) > 1) {
			return false;
		} else {
			return true;
		}
	} else if (paren_type == '(') {
		if (strlen(paren_s) > 2) {
			return false;
		} else if (strlen(paren_s) == 2) {
			if (paren_s[0] != '+' && paren_s[0] != '-') {
				return false;
			} else {
				return true;
			}
		} else {
			return true;
		}
	}
}

bool checkOp(char *op) {
	if (strlen(op) > 1) {
		return false;
	} else if (op[0] != '%' && op[0] != '/' && op[0] != '+' && op[0] != '-' && op[0] != '*' && op[0] != '^') {
		return false;
	} else {
		return true;
	}
}

int main() {
	char user_input[100];
	char *token = NULL;
	char *next_token = NULL;
	while (strcmp(user_input, "Exit") != 0) {
		int i = 0;
		int open_par = 0;
		char current_op = ' ';
		cout << "Enter arithmetic expression: ";
		cin.getline(user_input, 101);
		token = strtok_s(user_input, " ", &next_token);
		while (token != NULL) {
			if (findChar('(', token)) {
				if (i > 0 && i % 2 != 0) {
					cerr << "Invalid expression!" << endl;
					break;
				} else if (!checkParen(token, '(')) {
					cerr << "Invalid expression!" << endl;
					break;
				} else {
					open_par++;
				}
			} else if (findChar(')', token)) {
				if (!checkParen(token, ')')) {
					cerr << "Invalid expression!" << endl;
					break;
				}
				else {
					open_par--;
				}
			} else if (i % 2 == 0) {
				if (!checkNum(token)) {
					cerr << "Invalid number input" << endl;
					i = 1;
					break;
				} else if (current_op == '/' && atoi(token) == 0) {
					cerr << "Divided by zero!" << endl;
					i = 1;
					break;
				} else {
					i++;
				}
			} else {
				if (!checkOp(token)) {
					cerr << "Invalid operator input!" << endl;
					break;
				} else {
					current_op = token[0];
					i++;
				}
			}
			token = strtok_s(NULL, " ", &next_token);
		}
		if (open_par != 0) {
			cout << "Invalid expression" << endl;
			continue;
		} else if (i % 2 == 0) {
			cout << "Invalid expression" << endl;
			continue;
		}
	}
	/*int prev_element = 0;
	while (strcmp(argument, "Exit") != 0) {
		bool open_par = false;
		bool close_par = false;
		bool isnum = false;
		int current_cha = 0;
		char current_item[100] = "";
		char prev_item[100] = "";
		cout << "Enter arithmetic expression: ";
		cin.getline(argument, 99);
		for (int next_element = 0; next_element <= strlen(argument); next_element++) {
			if (argument[next_element] == '(') {
				current_item[current_cha] = '(';
				current_item[current_cha + 1] = '\0';
				cout << current_item;
				if (checkParen(current_item)) {
					break;
				}
				current_cha = 0;
				current_item[0] = '\0';
				open_par = true;
			}
			if (argument[next_element] != ' ' && argument[next_element] != '\0') {
				if (argument[next_element] >= '0' && argument[next_element] <= '9' || argument[next_element] == '.') {
					isnum = true;
				}
				current_item[current_cha] = argument[next_element];
				current_cha++;
			}  else {
				current_item[current_cha] = '\0';
				if (!checkArgument(current_item, prev_item, isnum)) {
					break;
				}
				open_par = false;
				close_par = false;
				isnum = false;
				strcpy_s(prev_item, current_item);
				current_cha = 0;
				current_item[0] = '\0';
			}
			prev_element++;
		}
	}*/
	return 0;
}
// Important note: implement a priority. if in paren priority + 1. then sort priority