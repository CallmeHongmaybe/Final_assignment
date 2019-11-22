#include <iostream> 
using namespace std; 

void checkForFloats(string); 
int convertToInt(string); 
int pow(int, int); 

int main() {
    string expr; 
    cout << "Enter a number: "; 
    getline(cin, expr); 
//.erase(0, expr.find(endingRegex) + endingRegex.length); 
  cout << pow( convertToInt(expr) , 3) << endl; 
}

// void checkForFloats(string expr) {
//      for (int i = 0; i < expr.length(); i++) {
//         if (int(expr[i]) == 46) {
//             cout << "Syntax error: Found float number: " << expr[i - 1] << expr[i] << expr[i + 1] << endl; 
//             break;  
//         }
//         else if (i == expr.length() - 1) {
//             cout << "Everything looks good" << endl; 
//         }   
//     }
// }

int convertToInt(string number) {
	int toint = 0;
	int start_digit = 0;
	if (number[0] == '-' || number[0] == '+') {
		start_digit = 1;
	}
	int i = start_digit;
	while (number[i] >= '0' && number[i] <= '9') {
		toint *= 10;
		toint += number[i] - '0';
		i++;
	}
	if (number[0] == '-') {
		return (-1 * toint);
	}
	else {
		return toint;
	}
}

int pow(int base, int n) { 
    int ans = 1; 
    for (int i = 1; i <= n; i++) {
        ans *= base; 
    }
    return ans; 
}