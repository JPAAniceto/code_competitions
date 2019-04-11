#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGITS_N 16

float solve(char* test_case, int size);
int find_most_significant_odd(char *test_case, int size);
float count_plus(char* number, int end, int current_index, int size, int carry_in);
float count_minus(char* number, int end, int current_index, int size, int carry_in);
int compare_string(char *src, char *dst);
void copy_string(char *src, char *dst);
int get_string_size(char * str);
float string_to_float(char* str, int size);

int main(){

    int nr_test_cases;
    char* test_case[32];
    // do
    // {
    scanf("%d",&nr_test_cases);
    //     if(nr_test_cases==0){
    //         break;
    //     }
    for (int i =0 ; i <nr_test_cases; i++){
        int solution ;
        scanf("%s",test_case);
        solution = (int)(solve(test_case, get_string_size(test_case)));
        fprintf("Case #%d: %d\n",i+1, solution);
        fflush(stdout);
    }
    // }while(nr_test_cases>0);
    return 0;
}


float solve(char* test_case, int size)
{
    float nr_plus = 0,nr_minus = 0;
    char test_case_tmp[size];
    
    copy_string(test_case,test_case_tmp);
    int odd_index = find_most_significant_odd(test_case, size);

    if(test_case[odd_index] != '\0' && test_case[odd_index] != '\n' && odd_index < size)
    {
        nr_minus = count_minus(test_case_tmp, odd_index, size-1, size, 0);
        if (nr_minus == 1)
        {
            return nr_minus;
        }
    }

    while(test_case[odd_index] != '\0' && test_case[odd_index] != '\n' && odd_index < size)
    {
        nr_plus = count_plus(test_case_tmp, odd_index, size-1, size, 0);
        
        float new_test_case = string_to_float(test_case_tmp,size);
        new_test_case = nr_plus + new_test_case;
        
        char new_test_case_tmp[size+1];
        snprintf(new_test_case_tmp,sizeof(new_test_case_tmp) ,"%.0f", new_test_case);
        size = get_string_size(new_test_case_tmp);
        odd_index = find_most_significant_odd(new_test_case_tmp, size);
    }
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
float count_plus(char* number, int end, int current_index, int size, int carry_in)
{
    if(current_index <end)
    {
        return 0;
    }
    if(current_index == end)
    {
        // printf("Final Plus\n");
        int current_digit = number[current_index] - '0';
        if (carry_in == 1) return 0;
        else 
        {
            int exponent = (current_index+1) - size;
            float multiplier = pow(10 , abs(exponent));
            return  multiplier ;
        }
    }
    
    int current_digit = number[current_index] - '0';
    int nr_plus = 10- (current_digit+carry_in);
    int carry_out = (nr_plus != 10 ) ? 1 : 0;
    
    nr_plus = (nr_plus != 10) ? nr_plus : 0;

    int exponent = (current_index+1) - size;
    float multiplier = pow(10 , abs(exponent));

    return (multiplier*nr_plus) + count_plus(number, end, current_index-1, size, carry_out);
}

// Recursive function that counts the number of minus necessary to turn all digits even
// It iterates from the least significant digit to the most significant digit
float count_minus(char* number, int end, int current_index, int size, int carry_in)
{
    if(current_index <end)
    {
        return 0;
    }

    if(current_index == end)
    {
        // printf("Final minus!!!!!!!\n");
        int current_digit = number[current_index] - '0';
        if (carry_in == 1) return 0;
        else 
        {
            int exponent = (current_index+1) - size;
            float multiplier = pow(10 , abs(exponent));
            return  multiplier ;
        }
    }
    
    int current_digit = number[current_index] - '0';
    int nr_minus = (10+(current_digit-carry_in)) - 8;
    int carry_out = (nr_minus >=10) ? 0 : 1;
    
    nr_minus = (nr_minus >=10) ? nr_minus-10 : nr_minus;

    int exponent = abs((current_index+1) - size);
    float multiplier = pow(10 , exponent);
    return (multiplier*nr_minus) + count_minus(number, end, current_index-1, size, carry_out);
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