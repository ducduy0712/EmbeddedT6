# EmbeddedT6

## COMPLIER

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/d03da076-4778-42dc-a42d-9f2a76c4be35)

Compiler là quá trình được hiểu là biên dịch từ ngôn ngữ lập trình sang ngôn ngữ cho máy hiểu được ( từ file.c sang file.exe).
Qúa trình compiler bao gồm 4 giai đoạn: preprocesser(tiền xử lý), Compiler, Assembler, Linker.

**Preprocesser:** Là bước tiền xử lý của máy, dịch ra từ filec.c sang file.i (preprocessed source). Thay thế tất cả các include < thư viện > bằng các thư viện,
thay thế define bằng các giá trị, bỏ comments. Câu lệnh: `gcc -E file.c -o file.i.`

**Compiler:** Là bước chuyển file từ file.i sang file.s (assembly code). Câu lệnh: `gcc  file.i -S -o file.s.`

**Assembler:** Là bước chuyển file từ file.s sang file.o + librabries(hình ảnh, âm thanh). Câu lệnh: `gcc -c file.s -o file.o.`

**Linker:** Là bước liên kết  file.o và các librabries  sang file.exe (excutable) để có thể chạy trên máy tính, hoặc có thể tạo thành file.h (hex) để nạp vào các vi điều khiển.

**Lưu ý :**
+ Trong quá trình tiền xử lý, có include bao nhiêu file thì cũng chỉ ra 1 file.i chính.
+ Khi include file cần chú các biến của các file có giống nhau không để tránh xảy ra lỗi khi chạy.

## POINTER

**POINTER:** Là một biến đặc biệt, dùng để lưu địa chỉ của biến chứ không phải giá trị, được lưu trên ram. Kích thước của biến pointer phụ thuộc vào vi xử lý.

**NORMAL POINTER:** Là con trỏ dùng để lưu địa chỉ của biến đó, kiểu dữ liệu của con biến như thế nào thì kiểu con trỏ cũng vậy.

Ví dụ:

```sh
int a = 10 // giả sử có địa chỉ là 0x01
int *ptr = &a = 0x01 // * ptr ở đây là biến con trỏ ptr, do quy tắc đặt tên biến pointer phải có dấu * ở trước.
printf("Dia chi: %p,ptr); // Dia chi 0x01.
printf("Gia tri: %d, *ptr);// * ptr là giá trị của con trỏ ptr trỏ đến.
```

**VOID POINTER:** Là con trỏ có thể lưu địa chỉ của tất cả các biến có dữ liệu tùy ý, khi trả về giá trị thì nó không hiểu, muốn trả về thì phải ép kiểu cho nó.

Ví dụ: 
```sh
*(kiểu dữ kiệu*)(biến) = *(int*)(ptr)

int a = 10;
char b = 'c';
double d = 10.4;

void *ptr;
ptr = &a
printf("Dia chi cua a %p, gia tri cua a %d, ptr, *(int*)(ptr);// dia chi cua a 0x.., gia tri cua a 10
printf("Dia chi cua b %p, gia tri cua b %c, ptr, *(char*)(ptr);
printf("Dia chi cua c %p, gia tri cua c %f, ptr, *(float*)(ptr);
```

**NULL POINTER:** Là con trỏ có dữ liệu và địa chỉ bằng 0, dùng trong trường hợp mà con trỏ chúng ta đã khai báo chưa sử dụng tới hoặc đã sử dụng xong.

Ví dụ : `int * ptr = NULL;`

**FUNCTION POINTER:** Là con trỏ lưu địa chỉ của hàm, nó có thể trỏ đến địa chỉ các hàm có cùng cấu trúc.

Ví dụ:

```sh
void tong(int a, int b);
{printf("tong: %d\n,a+b);
}
int main(){
void(*ptr)(int, int) = &tong;// trỏ đến hàm tong có cùng cấu trúc input và parameter.
ptr(8,9);// tong: 17
return 0;}
```
**POINTER TO POINTER:** Là con trỏ lưu địa chỉ của một con trỏ khác.
Ví dụ: 
```sh
int a = 10; // có địa chỉ 0x01
int *ptr = &a = 0x01 // có địa chỉ 0xc1
int **ptp = &ptr = 0xc1
```
**Lưu ý:** Khi khai báo một con trỏ hàm mà không có giá trị, nó sẽ trỏ đến một giá trị bất kì trong chương trình => RẤT NGUY HIỂM.

## PHÂN VÙNG NHỚ

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/1d85fffc-da0a-483c-a2c6-673b827d90ac)

**TEXT:** 
+ Có quyền truy cập read và chứa lệnh thực thi nên tránh sửa đổi ( Ví dụ như nạp một file.hex cho vi điều khiển, thì file.hex nằm ở bộ nhớ flash, khi chạy sẽ copy chương trình này tại bộ nhớ ram tại phân vùng text).
+ Chứa khai báo hằng số trong chương trình VD : `const int a = 10;`
+ Lưu ý: Data nào nằm ở phân vùng text chỉ đọc chứ không sửa được.

**DATA:** 
+ Quyền truy cập read và write.
+ Chứa biến toàn cục hoặc biến static với giá trị khởi tạo khác không.
+ Được giải phóng khi kết thúc chương trình

Ví dụ : 
```sh
#include <stdio.h>

int i =10;// bien toan cuc nam o phan vung data
static int i =5;// bien static toan cuc nam o phan vung data
void tong()
{
int x;// bien cuc bo
static int c =5;// bien static cuc bo nam o phan vung data
}
```

**BSS:** 
+ Quyền truy cập read và write.
+ Chứa biến toàn cục hoặc biến static với giá trị khởi tạo bằng 0 hoặc không khởi tạo.
+ Được giải phóng khi kết thúc chương trình.

Ví dụ:
```sh
#include <stdio.h>

int i ;// bien toan cuc nam o phan vung bss (khong khoi tao gia tri)
static int i =0;// bien static toan cuc nam o phan vung bss ( bang 0)
void tong()
{
static int c;// bien static cuc bo nam o phan vung bss (khong khoi tao gia tri)
}
```

**STACK:** 
+ Quyền truy cập là read và write.
+ Được sử dụng cấp phát cho biến local, input parameter của hàm.
+ Sẽ được giải phóng khi thoát ra khỏi block code hàm.
  Ví dụ:
  
```sh
#include <stdio.h>

int tong(int a, int b);{ // a ,b duoc luu o phan vung stack
int c; // bien cuc bo luu o phan vung stack
c = a+b; // bien cuc bo luu o phan vung stack
return c;
}

int main(int argc, char const* argv[]){
int x = tong(5 ,7);// int a = 5 // 0x01
                    // int b = 7 // 0x02
                    // int c //0x03
                    //c =a+b
                    // return c; // khi thoat ra dia chi a,b,c bi thu hoi
tong (7, 10);// khi goi ra cung chay ra tuong tu nhung co the nam o dia chi khac do dia chi cu 
                da bi thu hoi
return 0;
}
```

Ứng dụng của con trỏ , Ví dụ :
```sh
#include <stdio.h>
  
void swap(int a, int b);{
int temp = a; //int a =10 // 0x01
a =b;          // int b = 20 //0x02
b = temp;
}

int main(int argc, char const* argv[]){
int x = 10; // 0xc1
int y = 20;//0xc2
swap (x,y);
printf("x =%d, y=%d,x,y);
return 0;
```
*Khi chạy hàm swap giá trị của a và b được gán cho x và y và được đổi giá trị cho nhau, nhưng sau khi kết thúc hàm thì giải phóng địa chỉ => reset lại nên chương trình vẫn trả về kq x= 10, y= 20*

```sh
#include <stdio.h>
  
void swap(int *a, int *b);{
int temp = *a; //int *a = 0xc1 // gán giá trị temp = giá trị của a là 10
*a =*b;          // int b = 0x02 // gán giá trị của a =b = 20
*b = temp; // gán giá trị của b = 10
}

int main(int argc, char const* argv[]){
int x = 10; // 0xc1
int y = 20;//0xc2
swap (&x,&y);
printf("x =%d, y=%d,x,y);
return 0;
```
*Khi chạy hàm swap địa chỉ của a và b được gán cho x và y và được đổi giá trị cho nhau,  sau khi kết thúc hàm thì do cùng địa chỉ nên giá trị của x và y được đổi cho nhau => trả về kq x= 20, y= 10*

**CHÂN LÝ:** Sử dụng biến khi muốn đọc giá trị của input và parameter, sử dụng biến con trỏ khi muốn thay đổi giá trị của input và parameter.

**HEAP:** 
+ Quyền truy cập read và write.
+ Được sử dụng để cấp phát bộ nhớ động như : Malloc(kieu con tro void), Calloc,...
+ Sẽ giải phóng khi gọi hàm free. VD `free(tenbien);`

**Lưu ý:** Địa chỉ của mảng giống địa chỉ của member đầu tiên, địa chỉ của mảng liền kề nhau, cách nhau mỗi đơn vị của mảng đó
Ví dụ `int array[] = {1,3,5,7};// dia chi array = array[1], moi dia chi cach nhau 4 byte`

Ví dụ
```sh
#include <stdio.h>
#include <stdint.h>
#inlcude <stdlib.h>

int main(int argc, char const* argv[]){
int *array = (int*)malloc(sizeof(int)*4); //gan ham malloc gia tri int, 4 ky tu // luu o heap
for (int i =0; i <4; i++)
{
array [i]=3*i; // gan gia tri cho ham array[4] = { 0,3,6,9);
}
array = (int*)realloc(array, sizeof(int)*7);// cap phat them gia tri, 7 ky tu // luu o heap
for (int i =0; i <7; i++)
{
array [i]=2*i; // gan gia tri cho ham array[7] = { 0,2,4,6,8,10,12);
}
return 0; }
```
