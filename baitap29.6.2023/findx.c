#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

int random_number(int minN, int maxN){
 return minN + rand() % (maxN + 1 - minN);
}

uint16_t *createArray(uint16_t length){
    uint16_t *ptr = (uint16_t*)malloc(sizeof(uint16_t)*length);
    srand((int)time(0));
    for (uint16_t i = 0; i < length; i++)
    {
        ptr[i] = random_number(1, 10000);
    }
    return ptr; 
}

void sort(uint16_t arr[], uint64_t length)
{
    uint16_t i = 0;
    uint16_t temp;
    for (i = 0; i < length -1 ; i++){
        for (uint16_t j = i+1;j < length;j++){
        if (arr[i] > arr[j])
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    }
}

int timx(uint16_t arr[], int l, int r, int x)
{   if ( r>=l){
    int mid =  (r + l) / 2;
    if (arr[mid] == x ){
    return mid;}
    if (arr[mid] > x){
    return timx(arr ,l , mid -1, x);
    }else
    {return timx(arr, mid +1 ,r ,x);
    }
    }
    return -1;
}
int main(int argc, char const *argv[])
{
   uint16_t *array = createArray(10000);
   uint16_t test[] = {2, 3, 4, 10, 40};
   sort(array, 10000);
   int x = 1008;
   int ketqua = timx(array, 0 ,10000 , x);
   if (ketqua == -1)
   {
    printf("khong tim thay gia tri cua %d\n",x);
   }else{
    printf("tim thay gia tri cua x la %d tai vi tri %d\n",x,ketqua);
   }
    return 0;
}
