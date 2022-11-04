#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>

int main(int argc, char **argv) {
    int *p;

    // start the trace
    mtrace();
    p = (int *)malloc(sizeof(int)*10);
    *p = 2;

    printf("contents of P is %d\n", *p);
    free(p);
    return 0;
}