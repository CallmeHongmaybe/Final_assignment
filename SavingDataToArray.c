#include <stdio.h>
#include <stdlib.h>

typedef struct record {
    char name[100];
    long age;
    float weight;
} record;


int main(int argc, char const *argv[]) {
    FILE *bigdata = fopen("input.txt", "r");
    record record[100];
    char cha_check, prev_cha;
    int space_check = 0, line = 0, i = 0;
    char temp[20];
    int k = 0;
    while (cha_check != EOF) {
        cha_check = fgetc(bigdata);
        if (prev_cha == ' ' && cha_check <= '9' && cha_check >= '0') {
            space_check++;
            if (space_check == 2) {  
                //printf("%s\n", record[line].name);
                temp[k] = '\0';
                record[line].age = strtol(temp, NULL, 10);
                //printf("%li", record[line].age);
                k = 0;
            }
        }
        if ((cha_check <= '9' && cha_check >= '0') || cha_check == '.') {
            if (space_check == 1) {
                temp[k] = cha_check;
                k++;
            } else if (space_check == 2) {
                temp[k] = cha_check;
                k++;
            }
        } else if (cha_check == '\n') {
            record[line].name[i] = '\0';
            record[line].weight = strtof(temp, NULL);
            temp[k] = '\0';
            record[line].weight = strtof(temp, NULL);
            //printf(" %.2f\n", record[line].weight);
            k = 0;
            space_check = 0;
            i = 0;
            line++;
        } else if (cha_check == EOF) {
            record[line].weight = strtof(temp, NULL);
            //printf(" %.2f\n", record[line].weight);
            line++;
        } else {
            record[line].name[i] = cha_check;
            i++; 
        }
        prev_cha = cha_check;
    }
    printf("\n");
    return 0;
}
