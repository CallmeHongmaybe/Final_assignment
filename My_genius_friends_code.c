#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWERCASE_A_ASCII 97
#define LOWERCASE_Z_ASCII 122
#define UPPERCASE_A_ASCII 65
#define UPPERCASE_Z_ASCII 90
#define DOT_SYMBOL_ASCII 46
#define DIGIT_ZERO_ASCII 48
#define DIGIT_NINE_ASCII 57

#define TYPE_DIGIT 0
#define TYPE_LETTER 1
#define TYPE_BREAK 2
#define TYPE_SPACE 3
#define TYPE_FLOATING_POINT 4
#define TYPE_OTHER 5
#define TYPE_ANY 6

#define CHAR_SPACE ' '
#define CHAR_DOT '.'
#define CHAR_NEW_LINE '\n'

#define TRUE 1
#define FALSE 0

#define TYPE_INTEGER 0
#define TYPE_DOUBLE 1

#define MAXCHAR 255

#define NEGATIVE -1
#define POSITIVE 1

const char* ORDER_KEY_WORD = "order";
const char* ERROR_MESSAGE = "Wrong query format. Usage: ./find from_age to_age from_weight to_weight order by [age/weight] [ascending/descending] \n";
const char* FILE_NAME = "bigdata.txt";
#define BY_KEY_WORD "by"
#define AGE_KEY_WORD "age"
#define WEIGHT_KEY_WORD "weight"
#define ASCENDING_KEY_WORD "ascending"
#define DESCENDING_KEY_WORD "descending"

#define FIRST_AGE_INDEX 1
#define SECOND_AGE_INDEX 2
#define FIRST_WEIGHT_INDEX 3
#define SECOND_WEIGHT_INDEX 4
#define ORDER_INDEX 5
#define BY_INDEX 6
#define SORT_TYPE_INDEX 7
#define SORT_ORDER_INDEX 8

#define RESULT_ERROR 0
#define RESULT_SUCCEED 1

#define READ_FLAG "r"

#define NAME_STATE 0
#define AGE_STATE 1
#define WEIGHT_STATE 2

#define MAX_MEM_ALLOC 100000

#define SORT_BY_AGE 0
#define SORT_BY_WEIGHT 1

#define ORDER_ASCENDING 0
#define ORDER_DESCENDING 1

#define WEIGHT_SCALE 10000

#define VALID_ARG_NUMBER 9

int GLOBAL_COMPARE_TYPE = SORT_BY_AGE;
int GLOBAL_SORT_ORDER = ORDER_ASCENDING;

// Define the structure outside the main() so that other functions can use
struct person {
	char name[MAXCHAR];
	double age;
	double weight;
	long int id;
};

//// Define the structure outside the main() so that other functions can use
struct filter_criteria {
	double lower_bound_age;
	double upper_bound_age;
	double lower_bound_weight;
	double upper_bound_weight;
	int sort_type;
	int order_by;
};

// Define the structure outside the main() so that other functions can use
struct person_list {
	struct person* person_arr;
	int person_count;
};

// Functions definitions
int validate (int argc, char const *argv[]);
int get_current_char_type(char c);
int validate_number (const char* str, int type);
struct person handle_line(char* s);
void remove_space(char* source);
double castToDouble(char* str);
void process_input_file(const char* FILE_NAME, struct filter_criteria criteria);
double castConstToDouble(const char* str);
struct person_list filter_array_by_criteria(struct person* person_db, struct filter_criteria criteria);
struct filter_criteria get_filter_criteria(char const* argv[]);
struct person_list* merge(struct person_list* dest, struct person_list* addition_list);
void print_person(struct person* p);
void sort_and_print(struct person_list* p);

// Functions to remove space characters and new lines in string
void remove_space(char* source) {
	char* i = source;
	char* j = source;
	while (*j != 0)
	{
		*i = *j++;
		if (*i != CHAR_SPACE && *i != CHAR_NEW_LINE) {
			i++;
		}
	}
	*i = 0;
}

// Function to convert a string to double
double castToDouble(char* str) {
	double ddd;
	ddd = atof(str);
	return ddd;
}

//// Function to convert a string to double
double castConstToDouble(const char* str) {
	char* new_str = strdup(str);
	return castToDouble(new_str);
}

// Function taking its character and return its type
int get_current_char_type(char c) {
	if (c >= DIGIT_ZERO_ASCII && c <= DIGIT_NINE_ASCII)
		return TYPE_DIGIT;
	if ((c >= UPPERCASE_A_ASCII && c <= UPPERCASE_Z_ASCII) ||
	        (c >= LOWERCASE_A_ASCII && c <= LOWERCASE_Z_ASCII))
		return TYPE_LETTER;
	if (c == CHAR_SPACE )
		return TYPE_SPACE;
	if (c == CHAR_DOT)
		return TYPE_FLOATING_POINT;
	return TYPE_OTHER;
}

// Function validating number in the command ./find
int validate_number (const char* str, int type) {
	int isValid = TRUE;
	int has_floating_point = FALSE;
	for (int i = 0; i < strlen(str); i++) {
		if (get_current_char_type(str[i]) != TYPE_DIGIT) {
			if (type == TYPE_INTEGER) {
				isValid = FALSE;
			} else {
				if (get_current_char_type(str[i]) == TYPE_FLOATING_POINT && !has_floating_point) {
					has_floating_point = TRUE;
				} else {
					isValid = FALSE;
				}
			}
		}
	}
	return isValid;
}

// Function validating words in the command ./find
int validate(int argc, char const * argv[]) {
	if (argc != VALID_ARG_NUMBER) return 0;
	if (strcmp(argv[ORDER_INDEX], ORDER_KEY_WORD) != 0) return 0;
	if (strcmp(argv[BY_INDEX], BY_KEY_WORD) != 0)   return 0;
	if (strcmp(argv[SORT_TYPE_INDEX], AGE_KEY_WORD) && strcmp(argv[SORT_TYPE_INDEX], WEIGHT_KEY_WORD) != 0)    return 0;
	if (strcmp(argv[SORT_ORDER_INDEX], ASCENDING_KEY_WORD) && strcmp(argv[SORT_ORDER_INDEX], DESCENDING_KEY_WORD) != 0) return 0;
	if (!validate_number(argv[FIRST_AGE_INDEX], TYPE_INTEGER) || !validate_number(argv[SECOND_AGE_INDEX], TYPE_INTEGER) ) return 0;
	if (!validate_number(argv[FIRST_WEIGHT_INDEX], TYPE_DOUBLE) || !validate_number(argv[SECOND_WEIGHT_INDEX], TYPE_DOUBLE) ) return 0;
	return 1;
}

// To Do
int compare(const void *s1, const void *s2)
{
	struct person *e1 = (struct person *)s1;
	struct person *e2 = (struct person *)s2;
	double compare_val = 0;
	if (GLOBAL_COMPARE_TYPE == SORT_BY_AGE) {
		compare_val = e1->age - e2->age;
	} else if (GLOBAL_COMPARE_TYPE == SORT_BY_WEIGHT) {
		compare_val = (e1->weight - e2->weight) * WEIGHT_SCALE;
	}
	compare_val = ((GLOBAL_SORT_ORDER == ORDER_ASCENDING) ? POSITIVE  : (NEGATIVE)) * compare_val; // if and else
	return compare_val;
}

struct person handle_line(char* str) {
	struct person p;
	char *token;
	int current_state = NAME_STATE;
	int is_first_token = TRUE;
	const char s[2] = " ";
	token = strtok(str, s);
	char name[MAXCHAR] = " ";
	while (token != NULL) { // not found the space character to divide the string into apart
		remove_space(token);
		if (!validate_number(token, TYPE_DOUBLE)) {
			if (!is_first_token) strcat(name, s);
			strcat(name, token); // concat appends the current token to the end of the name string
			is_first_token = FALSE;
		} else {
			// if current token is a number
			if (current_state == NAME_STATE) {
				strcpy(p.name, name); // copy the name to the name strucre
				p.age = castToDouble(token);
				current_state = AGE_STATE;
			} else if (current_state == AGE_STATE) {
				p.weight = castToDouble(token);
				current_state = WEIGHT_STATE;
			}
		}
		token = strtok(NULL, s);
	}
	return p;
};

void sort_and_print(struct person_list* result) {
	qsort(result->person_arr, result->person_count, sizeof(struct person), compare);
	struct person* cP = result->person_arr;
	for (int i = 0; i < result->person_count; i++, cP++) {
		struct person p = *cP;
		print_person(&p);
	}
	printf("Total result: %i\n", result->person_count);
	free(result);
}

void process_input_file (const char* file_name, struct filter_criteria criteria) {
// Reading file
	int pagination = 0; // divide the bigdata file into pages to store the person index
	FILE *fp = fopen(FILE_NAME, READ_FLAG); // open file
	char str[MAXCHAR];
	if (fp == NULL) {
		printf("Could not open file %s", FILE_NAME);
	}
	// Pre-allocated memory area for the person array for future use
	struct person *ptr = malloc(sizeof(struct person) * MAX_MEM_ALLOC);
	// Create a empty Structure to hold the result
	struct person_list* result = malloc(sizeof(struct person_list));
	result->person_count = 0;
	result->person_arr = malloc(sizeof(struct person) * result->person_count);
	struct person_list temp;
	int index = 0; // counting the line of text file which is read
	while (fgets(str, MAXCHAR, fp) != NULL) // Loop the current page and filter the lines
	{
		if (index < MAX_MEM_ALLOC) {
			struct person p = handle_line(str);
			p.id = (pagination * MAX_MEM_ALLOC) + index + 1; // start page on C concept is 0, + 1 for the concept of normal reading
			*(ptr + index) = p;
			index++;
		} else {
			// finish checking total lines of the required page
			temp = filter_array_by_criteria(ptr, criteria);
			result = merge(result, &temp);
			index = 0;
			pagination++;
		}
	}

	temp = filter_array_by_criteria(ptr, criteria);
	result = merge(result, &temp);
	sort_and_print(result);
	printf("Matching criteria: Age [%3.0f, %3.0f], Weight [%.2f, %.2f] \n", criteria.lower_bound_age, criteria.upper_bound_age, criteria.lower_bound_weight, criteria.upper_bound_weight);
	fclose(fp);
}

//
struct filter_criteria get_filter_criteria(char const* argv[]) {
	struct filter_criteria c;
	const char* sort_type_str = argv[SORT_TYPE_INDEX];
	const char* order_type_str = argv[SORT_ORDER_INDEX];
	if (strcmp(sort_type_str, WEIGHT_KEY_WORD)) {
		GLOBAL_COMPARE_TYPE = SORT_BY_AGE;
		c.sort_type = SORT_BY_AGE;
	} else if (strcmp(sort_type_str, AGE_KEY_WORD)) {
		GLOBAL_COMPARE_TYPE = SORT_BY_WEIGHT;
		c.sort_type = SORT_BY_WEIGHT;
	}
	if (strcmp(order_type_str, ASCENDING_KEY_WORD)) {

		GLOBAL_SORT_ORDER = ORDER_DESCENDING;
		c.order_by = ORDER_DESCENDING;
	} else if (strcmp(order_type_str, DESCENDING_KEY_WORD)) {
		GLOBAL_SORT_ORDER = ORDER_ASCENDING;
		c.order_by = ORDER_ASCENDING;
	}

	// Conver elements of array argument to double
	c.lower_bound_age = castConstToDouble(argv[FIRST_AGE_INDEX]);
	c.upper_bound_age = castConstToDouble(argv[SECOND_AGE_INDEX]);
	c.lower_bound_weight = castConstToDouble(argv[FIRST_WEIGHT_INDEX]);
	c.upper_bound_weight = castConstToDouble(argv[SECOND_WEIGHT_INDEX]);
	return c;
}
// TO DO
struct person_list filter_array_by_criteria(struct person* person_db, struct filter_criteria criteria) {
	int result_count = 0;
	struct person_list result_holder;
	struct person *result = malloc(sizeof(struct person) * MAX_MEM_ALLOC);
	struct person *res_ptr = result;
	struct person* currentPtr = person_db;
	for (int i = 0; i < MAX_MEM_ALLOC; i++, currentPtr++) {
		int is_valid_age = (currentPtr->age >= criteria.lower_bound_age) && (currentPtr->age <= criteria.upper_bound_age);
		int is_valid_weight = (currentPtr->weight >= criteria.lower_bound_weight) && (currentPtr->weight <= criteria.upper_bound_weight);
		if (is_valid_age && is_valid_weight) {
			*res_ptr = *currentPtr;
			result_count++;
			res_ptr ++;
		}
	}
// Realloc the person array get from previous function with correct size
	struct person* temp = realloc(result, sizeof(struct person) * result_count);
	//printf("Result count: %i\n", result_count);
	//result_holder.person_arr = result;
	result_holder.person_arr = temp;

	result_holder.person_count = result_count;
	return result_holder;
}
// Merging 2 structures person list then returning the pointer to the result
//35 40 60.3 70.8
struct person_list* merge(struct person_list* dest, struct person_list* addition_list) {
	//printf("Begin merge. \n");
	int old_size = dest->person_count;
	int new_size = dest->person_count + addition_list->person_count;
	dest->person_count = new_size;
	//printf("New size: %i\n", new_size);
	// dest->person_arr
	struct person* temp = realloc(dest->person_arr, sizeof(struct person) * new_size);

	dest->person_arr = temp;
	struct person* current_ptr = dest->person_arr;
	for (int i = 0; i < old_size; i++, current_ptr++); // Loop through old values of the first array
	// Copy the values form the second array to the newly allocated memory of the first array
	for (int i = 0; i < addition_list->person_count; i++, current_ptr++) {
		struct person* p = addition_list->person_arr + i;
		//printf("%i addition_list %s %f %f\n", i, p->name, p->age, p->weight);
		*current_ptr = *(addition_list->person_arr + i);
	}
	//free(addition_list);
	//printf("End merge. \n");
	return dest;
}
// Beauty format of priting the result (counting space charaters needed to be filled)
void print_person(struct person* p) {
	int targetStrLen = 50;           // Target output length
	const char *padding = "                                        ";

	int padLen = targetStrLen - strlen(p->name); // Calc Padding length
	if (padLen < 0) padLen = 0;   // Avoid negative length

	printf("[%s ]%*.*s", p->name, padLen, padLen, padding);  // RIGHT Padding
	printf("|Age: %3.0f | Weight: %.2f| Line: %li\n", p->age, p->weight, p->id);
}

int main(int argc, char const * argv[]) {
	if (validate(argc, argv)) {
		struct filter_criteria criteria = get_filter_criteria(argv); // Copy the values form array argument to the filter structrue
		process_input_file(FILE_NAME, criteria); // Input the File required
	} else {
		printf("%s\n", ERROR_MESSAGE);
	}
	return 0;
}
