#include <stdio.h>
#include "test.c"
#define MAX 10

void display(){
    printf("Hello World\n");
}
int main (int argc, char const*argv)
{
//this is function
display();
printf("MAX: %d\n",MAX);
test();
return 0;
}