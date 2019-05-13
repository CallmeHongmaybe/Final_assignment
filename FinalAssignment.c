/*
  RMIT University Vietnam
  Course: EEET2448 Computing Engineering
  Semester: 2019A
  Assessment: Final Project
  Author:   Dang Truoong Nguyen Long
            Phan Quoc Binh
            Quan Vi Hong
            Dinh Quang Nhat
  ID:   s3757333 (Dang Truong Nguyen Long)
        s3715271 (Phan Quoc Binh)
        s3757165 (Quan Vi Hong)
        s3681446 (Dinh Quang Nhat)
  Created date: 12/05/2019
  Acknowledgement: Mr Tran Ngoc Quang and geeksforgeeks.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ERROR_MESSAGE[] = "Wrong query format. Usage: ./find from_age to_age from_weight to_weight order by [age/weight] [ascending/descending]";

struct record {
    char name[100];
    short age;
    float weight;
};

//swaping algorithm
void swaping (struct record *source1, struct record *source2) {
    struct record tempstruct;
    tempstruct = *source1;
    *source1 = *source2;
    *source2 = tempstruct;
}

int partition (struct record arr[], int low, int high, char *string) 
{
    int i, pivot;
    float pivot_float;
    if (strcmp(string, "age") == 0) {
        pivot = arr[high].age;    // pivot 
        i = (low - 1);  // Index of smaller element  
        for (int j = low; j <= high - 1; j++) { 
        // If current element is smaller than or 
        // equal to pivot 
            if (arr[j].age <= pivot) { 
                i++;    // increment index of smaller element 
                swaping(&arr[i], &arr[j]); 
            }
        } 
    } else if (strcmp(string, "weight") == 0) {
        pivot_float = arr[high].weight;    // pivot 
        i = (low - 1);  // Index of smaller element  
        for (int j = low; j <= high - 1; j++) { 
        // If current element is smaller than or 
        // equal to pivot 
            if (arr[j].weight <= pivot_float) { 
                i++;    // increment index of smaller element 
                swaping(&arr[i], &arr[j]); 
            }
        } 
    }
    swaping(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

/* The function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void QuickSort(struct record arr[], int low, int high, char *string) 
{ 
    if (low < high) { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high, string); 
  
        // Separately sort elements before 
        // partition and after partition 
        QuickSort(arr, low, pi - 1, string); 
        QuickSort(arr, pi + 1, high, string); 
    } 
} 

int number_checking (char const number[]) {
    int number_validation = 0;
    for (short i = 0; i < strlen(number); i++) {
        if ((number[i] >= '0' && number[i] <= '9') || number[i] == '.') {
            number_validation = 1;
        } else {
            number_validation = 0;
            break;
        }
    }
    return number_validation;
}

int main(int argc, char const *argv[]) {
    //Display ERROR_MESSAGE if the user input is in a wrong
    if (argc != 9) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strcmp(argv[5], "order") != 0) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strcmp(argv[6], "by") != 0) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strcmp(argv[7], "age") != 0 && strcmp(argv[7], "weight") != 0) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strcmp(argv[8], "ascending") != 0 && strcmp(argv[8], "descending") != 0) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (number_checking(argv[1]) != 1 || number_checking(argv[2]) != 1) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (number_checking(argv[3]) != 1 || number_checking(argv[4]) != 1) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strtol(argv[1], NULL, 10) > strtol(argv[2], NULL, 10)) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    } else if (strtof(argv[3], NULL) > strtof(argv[4], NULL)) {
        printf("%s\n", ERROR_MESSAGE);
        return -1;
    }     
    
    //File handling
    FILE *bigdata = fopen("bigdata.txt", "r");
    FILE *output = fopen("result.txt", "w");
    if (bigdata == NULL) {
        printf("Cannot open input file!\n");
        return -1;
    } else if (output == NULL) {
        printf("Cannot create output file!\n");
        return -1;
    }
    
    //Initialize variable
    struct record *record = (struct record*) malloc(10*sizeof(struct record));
    struct record tempstruct;
    short space_check = 0, i = 0, k = 0;
    char current_character, previous_character;
    long line = 0;
    char *temp = (char *) malloc(10);

    //Saving the line that satisfy the criteria from the user input into an array
    while (current_character != EOF) {
        current_character = fgetc(bigdata);

        //Name, age and weight are seperated by spaces.
        if (previous_character == ' ' && current_character <= '9' && current_character >= '0') {
            record[line].name[i - 1] = '\0';
            space_check++;
            //When space_check == 2, it means that the number character that temp cointain are the age
            if (space_check == 2) {
                temp[k] = '\0';
                record[line].age = strtol(temp, NULL, 10);
                k = 0;
                temp = (char *) realloc(temp, k + 1);
            }
        }

        if ((current_character <= '9' && current_character >= '0') || current_character == '.') {
            temp[k] = current_character;
            k++;
            temp = (char *) realloc(temp, k + 1);
        //When current_character = '\n, it means that the number character that temp cointain are the age
        } else if (current_character == '\n') {
            temp[k] = '\0';
            record[line].weight = strtof(temp, NULL);
            k = 0;
            temp = (char *) realloc(temp, k + 1);
            space_check = 0;
            i = 0;
            // If the weight and age are satisfied, the line will increase to store new line of value from bigdata to the array.
            // else the line will stay the same so that the new value from bigdata will overwrite the current value store in the array 
            if (record[line].age >= strtol(argv[1], NULL, 10) && record[line].age <= strtol(argv[2], NULL, 10)) {
                if (record[line].weight >= strtof(argv[3], NULL) && record[line].weight <= strtof(argv[4], NULL)) {
                    line++;
                    record = (struct record*) realloc(record, (line + 1)*sizeof(struct record));
                }
            }
        } else if (current_character == EOF) {
            record[line].weight = strtof(temp, NULL);
            // If the weight and age are satisfied, the line will stay the same to store the last line of value from bigdata to the array.
            // else the line will decrease by 1 to indicate that The last line of value from bigdata stored into the array is no longer used 
            if (record[line].age <= strtol(argv[1], NULL, 10) && record[line].age >= strtol(argv[2], NULL, 10)) {
                if (record[line].weight <= strtof(argv[3], NULL) && record[line].weight >= strtof(argv[4], NULL)) {
                    line--;
                    record = (struct record*) realloc(record, (line + 1)*sizeof(struct record));
                }
            }

        } else {
            record[line].name[i] = current_character;
            i++; 
        }

        previous_character = current_character;
    }

    //Sort the array in the ascending order
    if (strcmp(argv[7], "age") == 0) {
        QuickSort(record, 0, line - 1, "age");
    } else if (strcmp(argv[7], "weight") == 0) {
        QuickSort(record, 0, line - 1, "weight");
    }

    if (strcmp(argv[8], "ascending") == 0) {
        for (int i = 0; i < line; i++) {
            fprintf(output, "%s", record[i].name);
            fprintf(output, " %i", record[i].age);
            fprintf(output, " %.2f\n", record[i].weight);
        }
    //When the user ask for the descending order, we just need to print the sorted array in a reverse order
    } else if (strcmp(argv[8], "descending") == 0) {
        for (int i = line - 1; i >= 0; i--) {
            fprintf(output, "%s", record[i].name);
            fprintf(output, " %i", record[i].age);
            fprintf(output, " %.2f\n", record[i].weight);
        }
    }

    free(record);
    free(temp);
    record = NULL;
    temp = NULL;
    fclose(bigdata);
    fclose(output);
    return 0;
}
