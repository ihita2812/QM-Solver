#include <stdio.h>
#include "solver.h"

int main() {
    scanf("%d", &N);
    
    //-----------------------------FOR TESTING STRING() FUNCTION-----------------------------
    char arr[4];
    arr[0] = '1';
    arr[1] = '0';
    arr[2] = dash;
    arr[3] = '0';

    char* ans = string(arr);
    for (int i=0; i<str_len; i++) {
        printf("%c", *(ans+i));
    }
    printf("\n");
    //---------------------------------------------------------------------------------------

    return 0;
}
