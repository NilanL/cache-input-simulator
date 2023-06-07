# Cache Input Simulator

## Background:<br/>
This project was created to introduce myself to the GitHub environment and workflow. The program itself was conceptualized when working on an assignment in the topic of processors and caches in a **Computer Logic and Organization** course. The task was to input a set of data values into a cache of an _n_ amount of blocks, and with a defined associativity. The quotient, _q_, of the _n_ blocks divided by the associativity was calculated to determine how many "sets" there would be within the cache. The _n_ amount of blocks would be distributed evenly throughout these "sets". Each data value would be divided by the _q_ quotient, and the _r_ remainder of that division would determine what "set" that data value would be inserted into. The specific block within that "set" that would hold the data value would be the first empty block, starting at zero. If there were no empty blocks, then the least recently used, LRU, block would have it's initial value replaced by the new data value. A cache hit would dictate a data value being inserted that is already stored within the cache, and a miss would be otherwise.

## Original Program:<br/>
Originally I created a simple looping program to calculate the remainder quickly. The program assumes an 8 block cache and 4-way set associativity, and was coded in C rather than C++

```
#include <stdio.h>

int main()
{
    int input;
    int continue_input = 1;

    while (continue_input != 0)
    {
        printf("input: ");
        scanf("%d", &input);
        
        printf("set # %d\n", input % 2);
        
        printf("continue: ");
        scanf("%d", &continue_input);
        
        printf("\n");
    }

    return 0;
}
```
