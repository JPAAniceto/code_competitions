#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define N_MAX 6
#define T_MAX 3
#define PATH_MAX 50001

void solve(char* test_case, long int size, long int n, char* solution);
long int get_string_size(char * str);
long int string_to_lint(char* str, long int size);


int main(int argc, char **argv){
    int nr_test_cases;

    // Interpret First line
    scanf("%d",&nr_test_cases);

    // Iterate test cases
    long int n;
    char n_buff[N_MAX];
    char lydia_path_buff[PATH_MAX];
    char solution[PATH_MAX];

    for (int i =1 ; i <=nr_test_cases; i++){
        // grid dimention
        scanf("%ld",&n);
        fflush(stdin);
        
        // lydia path
        long int size = (2*n) - 2;
        scanf("%s",lydia_path_buff);
        fflush(stdin);

        // solution
        memset(solution, '\0', size+1);
        solve(lydia_path_buff, size,n,solution);

        printf("Case #%d: %s\n", i,solution);
        fflush(stdout);
    }

    // fclose(f);

    return 0;
}


void solve(char* test_case, long int size, long int n, char* solution){

    long int current_lydia[2] = {1,1};
    long int current_me[2] = {1,1};
    
    for(int i = 0 ;i<size;i++)
    {
        // check if we are at the same cell
        if(current_me[0] == current_lydia[0] && current_me[1] == current_lydia[1])
        {
            solution[i] = (test_case[i] == 'E') ? 'S' : 'E';
        }
        else{
            solution[i] = (solution[i-1] == 'E') ? 'S' : 'E';;
        }

        // update our current location
        if(solution[i] == 'E'){
            current_me[0] = current_me[0]+1;
            current_me[1] = current_me[1];
        }
        else
        {
            current_me[0] = current_me[0];
            current_me[1] = current_me[1]+1;
        }

        // update lydias current location
        if(test_case[i] == 'E'){
            current_lydia[0] = current_lydia[0]+1;
            current_lydia[1] = current_lydia[1];
        }
        else
        {
            current_lydia[0] = current_lydia[0];
            current_lydia[1] = current_lydia[1]+1;
        }
        if(current_me[0] == n && current_me[1] == n)
            break;
    }
    if(current_me[0] != n && current_me[1] != n)
    {
        printf("Error!! \n");
        printf("%ld %ld\n", current_me[0] , current_me[0]);
        exit(0);
    }

}

// String Utils Functions

long int get_string_size(char * str){
    long int size = 0;
    while(*str != '\0' && *str != '\n')
    {
        str++;
        size++;
    }
    return size;
}

long int string_to_lint(char* str, long int size)
{
    long int result=0;
    long int index=size-1;

    while(index >= 0)
    {
        long int exponent = (index+1) - size;
        long int multiplier = pow(10 , abs(exponent));
        result += multiplier*(str[index]-'0');
        index--;
    }

    return result;
}