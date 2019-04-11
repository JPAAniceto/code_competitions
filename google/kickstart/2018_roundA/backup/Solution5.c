#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGITS_N 16

int solve(char* test_case, int size);
int find_most_significant_odd(char *test_case, int size);

void special_case(char* number, int current_index, int end, char* new_number);
void count_plus(char* number,  int current_index, int end, char* result);
void count_minus(char* number,  int current_index, int end, char* result);

int compare_string(char *src, char *dst);
void copy_string(char *src, char *dst);
int get_string_size(char * str);
float string_to_float(char* str, int size);

int main(int argc, char **argv){
     // Reading input file name
    if(argc<=1){
        fprintf(stderr, "%s\n", "Not enough args");
        exit(0);
    }

    FILE *f;
    f = fopen(argv[1], "r");
    fflush(stdin);
    char test_cases_buff[3];

    // Interpret First line
    fgets(test_cases_buff, 3 ,(FILE*)f);    
    fflush(stdin);
    int nr_test_cases = test_cases_buff[0] - '0';
    // printf("Nr test cases : %d\n", nr_test_cases);

    // Iterate test cases
    int solutions[nr_test_cases];
    char test_case_buff[MAX_DIGITS_N];

    for (int i =0 ; i <nr_test_cases; i++){
        memset(test_case_buff, '\0', MAX_DIGITS_N);
        fgets(test_case_buff, MAX_DIGITS_N ,(FILE*)f);
        fflush(stdin);
        // printf("##############################\n");
        // printf("Case #%d: %s ", i,test_case_buff);
        solutions[i] = solve(test_case_buff, get_string_size(test_case_buff));
    }
    fclose(f);
    for(int i =0 ; i <nr_test_cases; i++){
        printf("Case #%d: %d\n", i+1,solutions[i]);
        fflush(stdout);
    }

    // int nr_test_cases;
    // char* test_case;
    
    // scanf("%d",&nr_test_cases);
    
    // for (int i =1 ; i <=nr_test_cases; i++){
    //     int solution ;
    //     scanf("%s",test_case);
    //     solution = (int)(solve(test_case, get_string_size(test_case)));
    //     fprintf("Case #%d: %d\n",i, solution);
    //     fflush(stdout);
    // }
    
    return 0;
}


int solve(char* test_case, int size)
{
    int nr_plus = 0,nr_minus = 0;
    char result[32];
    
    int odd_index = find_most_significant_odd(test_case, size);

    if(test_case[odd_index] != '\0' && odd_index < size)
    {
        count_minus(test_case, odd_index, size,result);
        nr_minus = (int)string_to_float(test_case,size) - (int)string_to_float(result,size);
        printf("result : %s", result);
        if(nr_minus==1) return nr_minus;
        count_plus(test_case, odd_index, size,result);
        printf("result : %s", result);

        nr_plus = (int)string_to_float(result,size) - (int)string_to_float(test_case,size);
    }
    printf("%d       %d\n",nr_minus,nr_plus );
    return (nr_plus<nr_minus) ? nr_plus : nr_minus;
}

// Finds the index/class of the most significant odd digit
int find_most_significant_odd(char *test_case, int size)
{
    int index=0;

    while((test_case[index] - '0') % 2 == 0 && test_case[index] != '\0' && index < size)
    {
        index++;
    }
    return index;
}


// Recursive function that counts the number of plus necessary to turn all digits even
// It iterates from the least significant digit to the most significant digit
void count_plus(char* number, int current_index, int end, char* result)
{
    copy_string(number, result);
    if (result[current_index] == '9')
    {
        special_case(result, current_index,end,result);
    }
    else{
        int new_digit = (int)(result[current_index]-'0')+1;
        result[current_index] = new_digit + '0';
    }
    current_index++;

    while(current_index<end)
    {
        if( (result[current_index]-'0') % 2 != 0)
        {
            result[current_index] = '0';
        }
        current_index++;
    }
}

void special_case(char* number, int current_index, int end, char* new_number)
{
    number[current_index]='0';
    if (current_index==0)
    {
        for(int i = 0; i<end;i++){
            new_number[i+1]==number[i];
        }
        new_number[0]='2';
    }
    else{
        current_index--;
        while((number[current_index]-'0') % 2 == 0)
        {
            current_index--;
        }
        special_case(number,current_index,end,new_number);
    }
}

void count_minus(char* number, int current_index, int end, char* result)
{
    copy_string(number, result);
    int new_digit = (int)(result[current_index]-'0')-1;
    result[current_index] = new_digit + '0';

    current_index++;

    while(current_index<end)
    {
        if( (result[current_index]-'0') % 2 != 0)
        {
            result[current_index] = '8';
        }
        current_index++;
    }
}

// ######################## String Utils functions ##################

// 1 if same string, 0 if different string
int compare_string(char *src, char *dst)
{
    int state = 1;
    while(*src != '\0')
    {
        if(*dst != *src) {
            state = 0;
            break;
        }
        src++;
        dst++; 
    }

    return state;
}

void copy_string(char *src, char *dst){
    while(*src != '\0')
    {
        *dst = *src;
        src++;
        dst++; 
    }
}

int get_string_size(char * str){
    int size = 0;
    while(*str != '\0' && *str != '\n')
    {
        str++;
        size++;
    }
    return size;
}

float string_to_float(char* str, int size)
{
    float result=0;
    int index=size-1;

    while(index >= 0)
    {
        int exponent = (index+1) - size;
        float multiplier = pow(10 , abs(exponent));
        result += multiplier*(str[index]-'0');
        index--;
    }

    return result;
}