#include <stdio.h>

const int N; //number of variables
const char dash = '-';
int str_len;

int num_diff_chars(int* a, int* b) {
    int c = 0;
    for (int i=0; i<N; i++) {
        if (a[i] != b[i]) c++;
    }
    return c;
}

char* string(char* a) {
    static char s[52];
    int s_ind = 0;

    for (int i=0; i<N; i++) {
        if (a[i] == '0') {
            s[s_ind] = 97+i;
            s[s_ind+1] = 39;
            s_ind+= 2;
        } else if (a[i] == '1') {
            s[s_ind] = 97+i;
            s_ind++;
        } else if (a[i] == dash) {
            //add nothing to s
        } else {
            printf("ERROR: value is other than 0, 1 or -\n");
            printf("Value is: %c.\n", a[i]);
            char x = 'X';
            char* ew = &x;
            return ew;
        }
    }

    str_len = s_ind;

    return s;
}

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
