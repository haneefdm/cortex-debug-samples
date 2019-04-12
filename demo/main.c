
#include <stdio.h>

volatile int glob = 93;

int main()
{
    // NOTE: make sure you build with -O0 so these aren't optimized out by the compiler. :)
    volatile int i = 0;
    int counter = 0;
    i = 42;
    for(;;)
    {
        i = i ^ (i + glob);
        counter++;
        glob++;
    }

    return i;
}
