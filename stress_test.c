#include <stdio.h>
#include <stdlib.h>

// I want you to change the increment and n and see at what point you end up with an extra loop

int main(int argc, char** argv)
{
    float i;
    float increment = 0.00000000000001; //Changing this around
    float n = 0.00000000000001; //changing this as well 
    int count = 1;

    for (i=0.0; i<n; i+=increment) {
        printf("Loop Number: %d\n", count);
        count++;
    }

    return 0;
}