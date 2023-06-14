#include <stdio.h>

void tong(int a , int b){
    printf("tong %d va %d = %d\n",a , b, a+b);
}
void hieu(int a , int b){
    printf("hieu %d va %d = %d\n",a , b, a-b);
}
void tich(int a , int b){
    printf("tich %d va %d = %d\n",a , b, a*b);
}
double thuong(int a, int b){
    return (double)a/b;
}
void toanhoc(void(*ptr)(int , int ),int a, int b){
    printf("Chuong trinh tinh toan\n");
    ptr(a,b);
}

int main(int argc, char const* argv[]){

    //toanhoc(&tong, 4, 7);
    double d = 10.3;
    char string[] = "hello";
    void *array[] = {&toanhoc, &d, string};
    printf("gia tri: %f\n", *(double*)(array[1]));
    printf("gia tri: %s\n", (char*)(array[2]));
    for (int i = 0; i < strlen(string);i++){
        printf("gia tri cua string %d la %c\n",i,*(char*)(array[2]+i));
   }

   // void *ptr = &tong;
   // ((void(*)(int, int))ptr)(8,0);
    (*((void(*)(void(*ptr)(int , int ),int , int))(array[0])))(&tong, 5 , 7);
    (*((void(*)(void(*ptr)(int , int ),int , int))(array[0])))(&hieu, 5 , 7);
    (*((void(*)(void(*ptr)(int , int ),int , int))(array[0])))(&tich, 5 , 7);
    return 0;
}
