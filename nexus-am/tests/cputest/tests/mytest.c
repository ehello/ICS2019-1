#include "trap.h"

int main()
{
    char out[1024];
    //printf("%s", "hello");
    //int a = sprintf(out, "%s", "hello");
    //int a = sprintf(out, "hello");
    //printf("%d\n", a);
    nemu_assert(sprintf(out, "%9s", "hello") == 9);
    //nemu_assert(sprintf(out, "hello") == 5);
    for (int i = 0; i <= 10; i++) printf("%d\n", out[i]);
    //nemu_assert(strcmp(out, "hello") == 0);
}