#include <stdio.h> 

void sort_ascending (int age[], int length) {
    int a;
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) {        
            if (age[i] > age[j]) {
                a = age[i]; 
                age[i] = age[j]; 
                age[j] = a; 
            }    
        }
    }
}

void sort_descending (int age[], int length) { 
    int a; 
    for (int i = 0; i < length; ++i) {
        for (int j = i + 1; j < length; ++j) { 
            if (age[i] < age[j]) {    
                a = age[j]; 
                age[j] = age[i]; 
                age[i] = a; 
            }
        }
    }
}

int main() {
    int age[] = {12,44,32,45,18,123,36,55,48,23,54,34,66,77,88};  // assume the array comes from Long's code
    int n, option; 
    n = sizeof(age); 
    int arrlen = n / sizeof(int); 
    printf("Please choose your option. 1 to ascend and 0 to descend"); 
    scanf("%i",&option);
    if (option == 1) {
        sort_ascending (age,arrlen); 
    }
    else if (option == 0) {
        sort_descending(age,arrlen);
    }
    else {
    printf("Not a valid option\n"); 
    return (-1); 
    }
    for (int i = 0; i < arrlen; ++i) {
        printf(" %d ", age[i]);
    }
    return 0;
}
