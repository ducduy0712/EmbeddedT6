# EmbeddedT6

# C

## MACRO & FUNCTION

**MACRO:** 
+ Macro là quá trình tiền xử lý, thay thế phần được định nghĩa vào.
+ Lệnh define để tạo macro. muốn xuống dòng trong macro sử dụng dấu \
  Ví dụ :
  ```sh
  #include <stdio.h>
  #define MAX 10
  #define CREATE_FUNC(name_func,cmd)\
  void name_func(){
    printf("%s\n",(char*)cmd;\
    }
  ```

 **FUNCITON:**
  + Hàm được sử dụng khi cần giải quyết một vấn đề nhiều lần trong chương trình.  Program counter có tác dụng đếm giá trị trong chương trình, khi đến giá trị của hàm thì trỏ đến vị trí của stack pointer( lưu những địa chỉ không theo quy luật) để lấy giá trị trong hàm.
    Ví dụ :
    ```sh
    #include <stdio.h>
    void tong(int a, int b){ // 0xc1 
    printf("tong %d",a+b);
    }
    int main (){          // program counter 0x09 
    A // 0x01 0x02 0x03     // stack pointer co dia chi 0x09 =>> program counter tro vao toi dia chi 0xc1 de 
                                thuc hien ham tong sau do ve dia 0x09 roi dem tiep
    B // 0x04 0x05 0x06
    C // 0x07 0x08
    tong (7,9); 0x09
    return 0;
    ```
**Ưu và nhược điểm:**
|MACRO|FUNCTION|
|----------------------|----------------------|
|Nhanh do program counter đếm liên tục, nhưng lại tốn thêm bộ nhớ để lưu trữ.|Chậm do program counter phải vào địa chỉ lưu hàm để đọc, nhưng tối ưu được kích thước do chỉ lưu 1 lần.|

## STRUCT & UNION
Kiểu dữ liệu do người dùng tự định nghĩa
**STRUCT:** 
+ Lấy kích thước của member lớn nhất để sắp xếp bộ nhớ.
+ Có địa chỉ giống với member đầu tiên, các member có địa chỉ khác nhau.
+ Sử dụng khi muốn lấy nhiều member 1 lúc.
+ Kích thước bằng tổng kích thước member.
  Ví dụ
  ```sh
  struct{
  uint8_t var1 // 1 byte // 1 byte dư 7 byte
  uint64_t var 3 // 4 byte // 8 byte dư 0
  uint32_t var2 // 2 byte // 2 byte dư 6
  // Lấy kích thước lớn nhất là 8 byte để lưu =>> cần 24 byte

  struc{
  uint8_t var1 // 1 byte // 1 byte dư 7 byte, lấy 2 byte ở dưới đắp lên là 3 dư 5
  uint32_t var2 // 2 byte // 2 byte 
   uint64_t var 3 // 4 byte // 8 byte dư 0
  // Lấy kích thước lớn nhất là 8 byte để lưu =>> cần 16 byte
  ```
**UNION:**
+ Kích thước bằng với kích thước của member lớn nhất.
+ Có địa chỉ giống với địa chỉ member =>> thay đổi từng member làm thay đổi các member khác.
+ Sử dụng khi chỉ cần lấy 1 member.
  Ví dụ
```sh
  #include <stdio.h>
typedef union{
unit8_t var1[6]; // kich thuoc 6 byte = kich thuoc cua union
uint8_t var2[4]; // kich thuoc 4 byte
uint8_t var3[2]; // kich thuoc 2 byte
}typeData;

int main(){

typeData data;

for (int i =0; i<6 ; i++){
data.var1[i] = i; // 0 ,1,2,3,4,5
}

for (int i =0; i<4 ; i++){
data.var1[i] = 2*i; // 0 ,2,4,6
}

for (int i =0; i<2 ; i++){
data.var1[i] = 3*i; // 0 ,3
}

printf("%d",data.var1[i]); // in ra 0,3,4,6,5 do thay doi gia tri cua tung member cung anh huong den member khac
```
**Ứng dụng:**
Kết hợp struct và union để gôm lại các giá trị và gửi đi 1 lần
Ví dụ:
```sh
tydef union{
struct{
char Id[2];
char Data[3];
char Cs[1];
}data;
uint8_array[6];
}Dataframe;

int main(){
Dataframe dataframe;

dataframe.data.Id[0] = 0x01;
dataframe.data.Id[1] = 0x02;

dataframe.data.Data[0] = 0xc1;
dataframe.data.Data[1] = 0xc2;
dataframe.data.Data[2] = 0xc3;

dataframe.data.Cs[0] = 0xc8; // lúc này mảng array = {0x01,0x02,0xc1,0xc2,0xc3,0xc8}

return 0;
}
```

  
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
## BIẾN BẬC CAO

**BIẾN STATIC CỤC BỘ :**
+ Chỉ được khởi tạo một lần, được sử dụng cho đến vòng đời của chương trình và được lưu lại giá trị sử dụng gần nhất.
+ Chỉ được sử dụng trong hàm chứa nó.

**BIẾN STATIC TOÀN CỤC**:
+ Chỉ được khởi tạo một lần, được sử dụng cho đến vòng đời của chương trình, và được lưu lại giá trị sử dụng gần nhất.
+ Chỉ sử dụng được trong file chứa nó, không include hoặc extern qua file khác.

**BIẾN VOLATILE:**
+ Được sử dụng khi giá trị của biến có thể thay đổi không báo trước, tránh việc sai sót do tính năng optimize của compiler ( nhìn code không thay đổi bỏ qua luôn).
  Ví dụ ```volatile int data = readADC();// Báo cho compiler không được optimize biến này```
+ Được sử dụng cho các biến thay đổi data, giá trị liên tục.

# C++

## OOP (Object-Oriented Programming)

**CLASS:** Class hay lớp là một mô tả trừu tượng (abstract) của nhóm các đối tượng (object) có cùng bản chất, ngược lại mỗi một đối tượng là một thể hiện cụ thể (instance) cho những mô tả trừu tượng đó. Một class trong C++ sẽ có các đặc điểm sau:
+ Một class bao gồm các thành phần dữ liệu (thuộc tính hay property) và các phương thức (hàm thành phần hay method).
+ Class thực chất là một kiểu dữ liệu do người lập trình định nghĩa.
+ Trong C++, từ khóa class sẽ chỉ điểm bắt đầu của một class sẽ được cài đặt.
Ví dụ:
```sh
class Person {
 public:
 string firstName; // property
 string lastName; // property
 int age; // property
 void fullname() { // method
 cout << firstName << ' ' << lastName;
 }
```
Cú pháp tạo object của một class và sử dụng các thuộc tính và phương thức:
```sh
Person person;
person.firstName = "Khiem";
person.lastName = "Le";
person.fullname(); // sẽ in ra màn hình là "Khiem Le
```
**Access modifiers & properties declaration:** là phạm vi truy cập của các thuộc tính và phương thức sẽ được khai
báo bên dưới nó. Có 3 phạm vi truy cập trong C++ là public, private và protected.
+ Các thuộc tính và phương thức khai báo public thì có thể được truy cập trực tiếp thông qua instance của class đó.Các thuộc tính nên khai báo là public nếu bạn không có ràng buộc điều kiện trước khi gán (người dùng có thể thoải mái gán giá trị) hoặc bạn không cần xử lý trước khi trả về giá trị thuộc tính.
+ Các thuộc tính private thường được sử dụng khi bạn không mong muốn người khác có thể tùy ý gán giá trị hoặc là bạn muốn xử lý trước khi trả về giá trị.
+ Đối với protected, các phương thức và thuộc tính chỉ có thể truy cập qua các class kế thừa nó hoặc chính nó.
Ví dụ
```sh
class MyClass
{
pubic:
  int public_property;
private:
  int private_property;
protected:
  int protected_property;
}
```
**METHOD:** Phương thức cũng giống như một hàm bình thường.Đối với phương thức thì có hai cách định nghĩa thi hành: định nghĩa thi hành trong lúc định nghĩa class và định nghĩa thi hành bên ngoài class.
Ví dụ
```sh
class Animal {
 public:
 string sound;
 void makeNoise()
{
 cout << sound; // định nghĩa bên trong class
}
};
void Animal::makeNoise() {
 cout << sound; // định nghĩa bên ngoài class
}
```
**Constructor:** Constructor hay hàm dựng là một hàm đặc biệt, nó sẽ được gọi ngay khi chúng ta khởi tạo một object. 

**Destructor:** Có nhiệm vụ thu hồi lại bộ nhớ được cấp phát cho đối tượng thuộc lớp.
Ví dụ :
```sh
class Person {
public:
 string firstName;
 string lastName;
 int age;
 Person(string _firstName, string _lastName, int _age)/// CONSTRUCTOR
 {
 firstName = _firstName;
 lastName = _lastName;
 age = _age;
 }
 void fullname() {
cout << firstName << ' ' << lastName;
 }
~Person(){ // DESTRUCTOR
....
};
```
**STATIC MEMBER:** Static member hay thành viên tĩnh trong class C++, bạn có thể khai báo nhiều object, mỗi object các thuộc tính
của nó đều khác nhau nhưng riêng static thì chỉ có một và static member tồn tại trong suốt chương trình cho dù có hay không có object nào của nó hay nói ngắn gọn là dùng chung một biến static.

## ĐẶC TÍNH CỦA LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG

**Inheritance (Tính kế thừa ):** trong lập trình hướng đối tượng , một class có thể kế thừa các thuộc tính của một class khác đã tồn tại trước đó.

Khi một class con được tạo ra bởi việc kế thừa thuộc tính của class cha thì chúng ta sẽ gọi class con đó là subclass trong C++, và class cha chính là superclass trong C++.

Có 3 kiểu tính kế thừa:
+ Kiểu pubic:
  
  Class cha ( public) -> class con (public)
  
  Class cha (protected) -> class con ( protected)
  
  Class cha (private) -> ko kế thừa đc
  
+ Kiểu protected:
 
  Class cha (public)-> class con (protected)
  
  Class cha (protected) -> class con (protected)
  
  private tương tự
  
+ Kiểu pirave :
 
  Class cha ( public) -> class con (private)
  
  Class cha (protected) -> class con (private)

**Abstraction (Tính trừu tượng):** trong lập trình hướng đối tượng là một khả năng mà chương trình có thể bỏ qua sự phức tạp bằng cách tập trung vào cốt lõi của thông tin cần xử lý.

Có nghĩa là sử dụng một method ( nằm trong private hoặc protected), thông qua nó thì một method chính mới có được kết quả. giống như nâng cấp của tính đóng gói

**Polymorphism (Tính đa hình) :** trong lập trình hướng đối tượng là một khả năng mà một phương thức trong class có thể đưa ra các kết quả hoàn toàn khác nhau, tùy thuộc vào dữ liệu được xử lý.
Ví dụ : 
```sh
class TinhTong
  public:
  void Tong( int a , int b){
      cout << a +b << endl;
  void Tong ( float a , float b){
      cout << a +b << endl;
  void Tong ( int a , int b , int c){
      cout << a+ b +c<<endl;
```
      
**Encapsulation (Tính đóng gói):** trong lập trình hướng đối tượng có ý nghĩa không cho phép người sử dụng các đối tượng thay đổi trạng thái nội tại của một đối tượng, mà chỉ có phương thức nội tại của đối tượng có thể thay đổi chính nó.

Điều đó có nghĩa, dữ liệu và thông tin sẽ được đóng gói lại, giúp các tác động bên ngoài một đối tượng không thể làm thay đổi đối tượng đó, nên sẽ đảm bảo tính toàn vẹn của đối tượng, cũng như giúp dấu đi các dữ liệu thông tin cần được che giấu =>> CÁC PROPERTY phải nằm ở trong protected hoặc private. 

**TEMPLATE:**
+ Template (khuôn mẫu) là một từ khóa trong C++, và là một kiểu dữ liệu trừu tượng tổng quát hóa cho các kiểu dữ liệu int, float, double, bool...
+ Template trong C++ có 2 loại đó là function template & class template.
+ Template giúp người lập trình định nghĩa tổng quát cho hàm và lớp thay vì phải nạp chồng (overloading) cho từng hàm hay phương thức với những kiểu dữ liệu khác nhau
Ví dụ : cũng mang tính chất đa hình.
```sh
template <typename bien>

bien tong(bien a, bien b){
  return (bien)(a+b);
}
int main{
tong ( 6 ,7); // kq la 13
```

**NAMESPACE:** Namespace là từ khóa trong C++ được sử dụng để định nghĩa một phạm vi nhằm mục đích phân biệt các hàm, lớp, biến, ... cùng tên trong các thư viện khác nhau.

Tình huống sử dụng: có 2 file A và B có cùng tên hàm hoặc biến ( nhưng giá trị khác nhau) thì phải sử dụng namespace để cho compiler hiểu , tránh bị lỗi.

Có thể sử dụng cú pháp using namespace fileA để sử dụng trực tiếp các biến hoặc hàm trong fileA, không cần phải thông qua fileA::biến.

**VIRTUAL FUNCTION:** Hàm ảo được sử dụng trong trường hợp một method trong class cha được class con kế thừa và muốn sử dụng override ( thay đổi method đó) =>> đặc tính overload.

Ví dụ
```sh
class Sinhvien{
  protected:
    virtual char *comment(){
    return (char*)"class sinh vien";
  }
  public
  void display(){
  printf("%s\n",comment());
    }
};
class hocsinh : pubic Sinhvien{
  private:
    char *comment(){
    return (char*)"class hoc sinh";
};
int main(){
  hocsinh hs;
hs.display; // in ra class hoc sinh
return 0;
}
```

*CHÚ Ý:* 
+ Con trỏ của lớp cơ sở có thể chứa địa chỉ của đối tượng thuộc lớp dẫn xuất, nhưng ngược lại thì không được.

+ Hàm ảo chỉ khác hàm thành phần thông thường khi được gọi từ một con trỏ. Sử dụng hàm ảo khi muốn con trỏ đang trỏ tới đối tượng của lớp nào thì hàm thành phần của lớp đó sẽ được gọi mà không xem xét đến kiểu của con trỏ.

**VECTOR:** LÀ MỘT CLASS.
+ Giống như là mảng (array), vector trong C++ là một đối tượng dùng để chứa các đối tượng khác, và các đối tượng được chứa này cũng được lưu trữ một cách liên tiếp trong vector.

+ Tuy nhiên, nếu như số lượng phần tử (size) của một mảng là cố định, thì ở vector, nó hoàn toàn có thể thay đổi trong suốt quá trình làm việc của chương trình.

Ví dụ:
```sh
int main(){
vector<int> array;

array.push_back(18);

array.push_back(1);

array.push_back(2);

array.push_back(3);

array.insert(array.begin()+1,35);

for ( int = 0; i < array.size(); i++){
  cout<< array[i]<<endl;
}
for ( int item : array){
  count << item << endl; }// for cải tiến của c ++ tương tự như thằng trên
```
**LIST:** Cũng tương tự như array nhưng mỗi địa chỉ của member trong list là riêng biệt, không liền kề nhau.

Khi làm việc với list muốn thay đổi giá trị phải thông qua interator.

Ví dụ
```sh
int main(){

list<int> array;

array.push_back(18);

array.push_back(1);

array.push_back(2);

array.push_back(3);

list <int>::interator it;
int i = 0;
// Xuat gia tri trong list
for ( it = array.begin; it != array.end(); it ++){
  cout << *it<< endl;
}
// Chen vao vi tri bat ky
for ( it = array.begin; it != array.end(); it ++){
if (i = 2){
array.insert(it, 30);
} i++;
};
```

**LAMBDA:** là một hàm được tạo ra để sử dụng ngay lập tức để tránh tình trạng lãng phí bộ nhớ.

Ví dụ
```sh
#include <iostream>
using namespcate std;

int main(){

int a = 10;
int f = 30;
int k = 40;

auto func = [=]( int a , int b) -> int{
  return a +b +c +k;
};

cout << func( 18 ,2 )<<endl; // kq la 90
return 0;
}

```
## C++ NÂNG CAO

**Cấp phát động:** 
Ví dụ:
```sh
int *ptr = new int; // cấp phát 1 địa chỉ lưu trên ram

int *aray = new int[4] // tạo ra 1 mảng để cấp phát gồm 4 phần từ

for (int i = 0; i < 4; i++){
array[i] = i; /// tạo ra 1 mảng array = {0,1,2,3}
delete[] array; // xóa mảng (tương tự như free bên c)
}
```
**Smart pointer:** Cũng cấp phát động nhưng tự động thu hồi lại bộ nhớ khi thoát khỏi block code, không cần xài delete, nằm trong thư viện memory.
Ví dụ:
```sh
#include <memory>
#include <iostream>

using namespace std;
void test(){
  unique_ptr<int> array(new int(5)); // cấp phát 1 địa chỉ lưu = 5
cout << *array << endl;
}

void test1(){
  shared_ptr<int> array(new int(5)); // cấp phát 1 địa chỉ lưu = 5
  shared_ptr<int> = array; // cũng tương tự như unique nhưng các shared_ptr  trỏ đến cùng 1 địa chỉ.
}
```

**Đa luồng:** Các chương trình có thể chạy song song với nhau, không theo tuần tự trên xuống. Sử dụng thư viện thread.
Ví dụ:
```sh
#include <thread>
#include <chrono>

using namespace std;

void func1(){
while(1){
  this_thread::sleep_for(chrono::seconds(1));// trong second là hàm delay
  cout << "id wait 1s" << endl;
}
}

void func2(){
while(1){
  this_thread::sleep_for(chrono::seconds(2));// trong second là hàm delay
  cout << "id wait 2s" << endl;
}
}
int main(){
  thread t1(func1);
  thread t2(func2);
  t1.join();
  t2.join(); /// 2 hàm chạy song song với nhaunhau
return 0;
}
```
**Mutex:** Cũng mang tính đa luồng nhưng khi  sử dụng lock mutex thì chỉ 1 trong số nhưng hàm đó đc chạy, hàm này chạy xong thì hàm kia mới chạy tiếp. Sử dụng thư viện mutex.
Ví dụ:
```sh
#include <mutex>
#include <thread>

int bank_account = 100;
mutex account_mutex;
void func(){
  lock_guard <mutex> lock (account_mutex);
  bank_acount++;
}
void func2(){
  lock_guard <mutex> lock (account_mutex);
  bank_acount--;
}
int main(){
  thread t1(func1);
  thread t2(func2);
  t1.join();
  t2.join(); /// 2 hàm chạy song song với nhau nhau, nhưng func chạy xong mới đến func2
return 0;
}
```
**Condition_variable:** Biến điều kiện, sử dụng trong đa luồng và có mutex, muốn một hàm khác chạy khi hàm kia chưa chạy xong bằng biến điều kiện. Sử dụng thư viện condition_variable.
Ví dụ:
```
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

int value;
bool check = false;
mutex mtx;
condition_variable cond_var;

void writer(){
  this_thread::sleep_for(chrono::seconds(2));
  lock_guard <mutex> lock (mtx);
  value = 23;
  check = true;
  cond_var.notify_one(); // báo trạng thái 
}
void reader(){
  unique_lock<mutex> lock(mtx);// check khóa
  cond_var.wait(lock,[] {return check;}); // cứ gọi cond_var.notify thì nó sẽ check, khi nào check = true thì sẽ mở khóa
  cout << "value: " << value;
}
```
# NHÚNG
**GIAO THỨC SPI:** (Serial Peripheral Interface) là một chuẩn truyền thông nối tiếp tốc độ cao do Motorola đề xuất.

⦁	Các bit dữ liệu được truyền nối tiếp nhau và có xung clock đồng bộ.

⦁	Giao tiếp song công, có thể truyền và nhận cùng một thời điểm.

⦁	Khoảng cách truyền ngắn, được sử dụng để trao đổi dữ liệu với nhau giữa các chip trên cùng một bo mạch.

⦁	Tốc độ truyền khoảng vài Mb/s.

⦁	Các dòng vi điều khiển thường được tích hợp module giao tiếp SPI dùng để giao tiếp truyền dữ liệu với các vi điều khiển khác, hoặc giao tiếp với các ngoại vi bên ngoài như cảm biến, EEPROM, ADC, LCD, SD Card,…

Giao tiếp 1 Master với 1 Slave

Bus SPI gồm có 4 đường tín hiệu:

⦁	SCLK: Serial Clock

⦁	MOSI: Master Out, Slave In

⦁	MISO: Master In, Slave Out

⦁	SS: Slave Select

Cách truyền và nhận dữ liệu

 ![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/3870eb89-f056-4b77-9f12-c8f343f9d1a2)
 
 **Cấu tạo và chức năng các chân:**
 
⦁ SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.

⦁ MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master. Đường MISO phải được kết nối giữa thiết bị Master và Slave.

⦁ MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. Đường MOSI phải được kết nối giữa thiết bị Master và Slave.

⦁ SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân này đôi khi còn được gọi là CS (Chip Select). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.

**Qúa trình truyền dữ liệu:** 

⦁ Mỗi chip Master hay Slave đều có một thanh ghi dữ liệu 8 bits.

⦁ Quá trình truyền nhận giữa Master và Slave xảy ra đồng thời sau 8 chu kỳ đồng hồ, một byte dữ liệu được truyền theo cả 2 hướng 

⦁ Quá trình trao đổi dữ liệu bắt đầu khi Master tạo 1 xung clock từ bộ tạo xung nhịp (Clock Generator) và kéo đường SS của Slave mà nó truyền dữ liệu xuống mức Low.

⦁ Cứ 1 xung clock, Master sẽ gửi đi 1 bit từ thanh ghi dịch (Shift Register) của nó đến thanh ghi dịch của Slave thông qua đường MOSI. Đồng thời Slave cũng gửi lại 1 bit đến cho Master qua đường MISO.Như vậy sau 8 chu kỳ clock thì hoàn tất việc truyền và nhận 1 byte dữ liệu.

⦁ Dữ liệu của 2 thanh ghi được trao đổi với nhau nên tốc độ trao đổi diễn ra nhanh và hiệu quả.

**Chế độ hoạt động:** 
SPI có 4 chế độ hoạt động phụ thuộc vào cực của xung giữ (Clock Polarity – CPOL) và pha (Phase - CPHA).

CPOL dùng để chỉ trạng thái của chân SCK ở trạng thái nghỉ. Chân SCK giữ ở mức cao khi CPOL=1 hoặc mức thấp khi CPOL=0.

CPHA dùng để chỉ các mà dữ liệu được lấy mẫu theo xung. Dữ liệu sẽ được lấy ở cạnh lên của SCK khi CPHA=0 hoặc cạnh xuống khi CPHA=1.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/00fc3f25-d6a6-4323-a733-a03b9adeda0b)


Lưu ý: Khi giao tiếp SPI giữa vi điều khiển và các thiết bị ngoại vi khác như IC, cảm biến thì 2 bên bắt buộc hoạt động cùng Mode, nếu không dữ liệu truyền nhận có thể bị đọc sai.

**GIAO THỨC I2C:** 
2C ( Inter – Integrated Circuit) là 1 giao thức giao tiếp nối tiếp đồng bộ được phát triển bởi Philips Semiconductors, sử dụng để truyền nhận dữ liệu giữa các IC với nhau chỉ sử dụng hai đường truyền tín hiệu.

Các bit dữ liệu sẽ được truyền từng bit một theo các khoảng thời gian đều đặn được thiết lập bởi 1 tín hiệu đồng hồ. 

Bus I2C thường được sử dụng để giao tiếp ngoại vi cho rất nhiều loại IC khác nhau như các loại vi điều khiển, cảm biến, EEPROM, … 

**Cấu tạo:**
I2C sử dụng 2 đường truyền tín hiệu:

	SCL -  Serial Clock Line : Tạo xung nhịp đồng hồ do Master phát đi

	SDA - Serial Data Line : Đường truyền nhận dữ liệu.

 ![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/a0b99771-f319-44ba-9472-38f36175ddb6)

Giao tiếp I2C bao gồm quá trình truyền nhận dữ liệu giữa các thiết bị chủ tớ, hay Master - Slave. 

Thiết bị Master là 1 vi điều khiển, nó có nhiệm vụ điều khiển đường tín hiệu SCL và gửi nhận dữ liệu hay lệnh thông qua đường SDA đến các thiết bị khác.
Các thiết bị nhận các dữ liệu lệnh và tín hiệu từ thiết bị Master được gọi là các thiết bị Slave. Các thiết bị Slave thường là các IC, hoặc thậm chí là vi điều khiển.

**Khung truyền:** 

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/f13ab944-e90d-4f59-82d3-180e5043e7ed)

o  Khối bit địa chỉ :

Thông thường quá trình truyền nhận sẽ diễn ra với rất nhiều thiết bị, IC với nhau. Do đó để phân biệt các thiết bị này, chúng sẽ được gắn 1 địa chỉ vật lý 7 bit cố định.

o  Bit Read/Write:

Bit này dùng để xác định quá trình là truyền hay nhận dữ liệu từ thiết bị Master. Nếu Master gửi dữ liệu đi thì ứng với bit này bằng ‘0’, và ngược lại, nhận dữ liệu khi bit này bằng ‘1’.

o  Bit ACK/NACK: 

Viết tắt của Acknowledged / Not Acknowledged. Dùng để so sánh bit địa chỉ vật lý của thiết bị so với địa chỉ được gửi tới. Nếu trùng thì Slave sẽ được đặt bằng ‘0’ và ngược lại, nếu không thì mặc định bằng ‘1’.

o  Khối bit dữ liệu: 

Gồm 8 bit và được thiết lập bởi thiết bị gửi truyền đến thiết bị nhân. Sau khi các bit này được gửi đi, lập tức 1 bit ACK/NACK được gửi ngay theo sau để xác nhận rằng thiết bị nhận đã nhận được dữ liệu thành công hay chưa. Nếu nhận thành công thì bit ACK/NACK được set bằng ‘0’ và ngược lại.

**Qúa trình truyền dữ liệu:** 

Bắt đầu: Thiết bị Master sẽ gửi đi 1 xung Start bằng cách kéo lần lượt các đường SDA, SCL từ mức 1 xuống 0. 

Tiếp theo đó, Master gửi đi 7 bit địa chỉ tới Slave muốn giao tiếp cùng với bit Read/Write.

Slave sẽ so sánh địa chỉ vật lý với địa chỉ vừa được gửi tới. Nếu trùng khớp, Slave sẽ xác nhận bằng cách kéo đường SDA xuống 0 và set bit ACK/NACK bằng ‘0’. Nếu không trùng khớp thì SDA và bit ACK/NACK đều mặc định bằng ‘1’.

Thiết bị Master sẽ gửi hoặc nhận khung bit dữ liệu. Nếu Master gửi đến Slave thì bit Read/Write ở mức 0. Ngược lại nếu nhận thì bit này ở mức 1.

Nếu như khung dữ liệu đã được truyền đi thành công, bit ACK/NACK được set thành mức 0 để báo hiệu cho Master tiếp tục.

Sau khi tất cả dữ liệu đã được gửi đến Slave thành công, Master sẽ phát 1 tín hiệu Stop để báo cho các Slave biết quá trình truyền đã kết thúc bằng các chuyển lần lượt SCL, SDA từ mức 0 lên mức 1.

**Các chế độ hoạt động của I2C:**

Chế độ chuẩn (standard mode) với tốc độ 100 kBit/s.

Chế độ tốc độ thấp (low speed mode) với tốc độ 10 kBit/s.

Ngoài ra, khác với giao tiếp SPI chỉ có thể có 1 Master, giao tiếp I2C cho phép chế độ truyền nhận dữ liệu giữa nhiều thiết bị Master khác nhau với thiết bị Slave. Tuy nhiên quá trình này có hơi phức tạp vì thiết bị Slave có thể nhận 1 lúc nhiều khung dữ liệu từ các thiết bị Master khác nhau, điều đó đôi khi dẫn đến xung đột hoặc sai sót dữ liệu nhận được.

Để tránh điều đó, khi làm việc ở chế độ này, mỗi thiết bị Master cần phát hiện xem đường SDA đang ở trạng thái nào. 

Nếu SDA ở mức 0, nghĩa là đang có 1 thiết bị Master khác đang có quyền điều khiển và phải chờ đến khi truyền xong. 

Ngược lại nếu SDA ở mức 1, nghĩa là đường truyền SDA đã an toàn và có sử dụng .

 
**GIAO THỨC URAT:**

UART hay bộ thu-phát không đồng bộ đa năng là một trong những hình thức giao tiếp kỹ thuật số giữa thiết bị với thiết bị đơn giản và lâu đời nhất. Bạn có thể tìm thấy các thiết bị UART trong một phần của mạch tích hợp (IC) hoặc dưới dạng các thành phần riêng lẻ. Các UART giao tiếp giữa hai nút riêng biệt bằng cách sử dụng một cặp dẫn và một nối đất chung.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/e4691c5f-a78a-4e9e-8566-58c8e41a8ae6)

Trong một sơ đồ giao tiếp UART:

1. Chân Tx (truyền) của một chip kết nối trực tiếp với chân Rx (nhận) của chip kia và ngược lại. Thông thường, quá trình truyền sẽ diễn ra ở 3.3V hoặc 5V. UART là một giao thức một master, một slave, trong đó một thiết bị được thiết lập để giao tiếp với duy nhất một thiết bị khác.
 

2. Dữ liệu truyền đến và đi từ UART song song với thiết bị điều khiển (ví dụ: CPU).
 

3. Khi gửi trên chân Tx, UART đầu tiên sẽ dịch thông tin song song này thành nối tiếp và truyền đến thiết bị nhận.
 

4. UART thứ hai nhận dữ liệu này trên chân Rx của nó và biến đổi nó trở lại thành song song để giao tiếp với thiết bị điều khiển của nó.

**Các chế độ truyền:**

UART truyền dữ liệu nối tiếp, theo một trong ba chế độ:

- Full duplex: Giao tiếp đồng thời đến và đi từ mỗi master và slave

- Half duplex: Dữ liệu đi theo một hướng tại một thời điểm

- Simplex: Chỉ giao tiếp một chiều

Dữ liệu truyền qua UART được tổ chức thành các gói. Mỗi gói chứa 1 bit bắt đầu, 5 đến 9 bit dữ liệu (tùy thuộc vào UART), một bit chẵn lẻ tùy chọn và 1 hoặc 2 bit dừng.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/e2981fc5-e4ac-47dc-8909-dc044d5d941f)

*Bit bắt đầu*

Đường truyền dữ liệu UART thường được giữ ở mức điện áp cao khi không truyền dữ liệu. Để bắt đầu truyền dữ liệu, UART truyền sẽ kéo đường truyền từ mức cao xuống mức thấp trong một chu kỳ clock. Khi UART nhận phát hiện sự chuyển đổi điện áp cao xuống thấp, nó bắt đầu đọc các bit trong khung dữ liệu ở tần số của tốc độ truyền.

*Khung dữ liệu*

Khung dữ liệu chứa dữ liệu thực tế được chuyển. Nó có thể dài từ 5 bit đến 8 bit nếu sử dụng bit chẵn lẻ. Nếu không sử dụng bit chẵn lẻ, khung dữ liệu có thể dài 9 bit. Trong hầu hết các trường hợp, dữ liệu được gửi với bit ít quan trọng nhất trước tiên.

*Bit chẵn lẻ*

Bit chẵn lẻ là một cách để UART nhận cho biết liệu có bất kỳ dữ liệu nào đã thay đổi trong quá trình truyền hay không. Bit có thể bị thay đổi bởi bức xạ điện từ, tốc độ truyền không khớp hoặc truyền dữ liệu khoảng cách xa. Sau khi UART nhận đọc khung dữ liệu, nó sẽ đếm số bit có giá trị là 1 và kiểm tra xem tổng số là số chẵn hay lẻ. Nếu bit chẵn lẻ là 0 (tính chẵn), thì tổng các bit 1 trong khung dữ liệu phải là một số chẵn. Nếu bit chẵn lẻ là 1 (tính lẻ), các bit 1 trong khung dữ liệu sẽ tổng thành một số lẻ. Khi bit chẵn lẻ khớp với dữ liệu, UART sẽ biết rằng quá trình truyền không có lỗi. Nhưng nếu bit chẵn lẻ là 0 và tổng là số lẻ; hoặc bit chẵn lẻ là 1 và tổng số là chẵn, UART sẽ biết rằng các bit trong khung dữ liệu đã thay đổi.

*Bit dừng*

Để báo hiệu sự kết thúc của gói dữ liệu, UART gửi sẽ điều khiển đường truyền dữ liệu từ điện áp thấp đến điện áp cao trong ít nhất khoảng 2 bit.

Có thể tóm tắt lại như sau. Quá trình truyền dữ liệu diễn ra dưới dạng các gói dữ liệu, bắt đầu bằng một bit bắt đầu, đường mức cao được kéo xuống đất. Sau bit bắt đầu, năm đến chín bit dữ liệu truyền trong khung dữ liệu của gói, theo sau là bit chẵn lẻ tùy chọn để xác minh việc truyền dữ liệu thích hợp. Cuối cùng, một hoặc nhiều bit dừng được truyền ở nơi đường đặt ở mức cao. Như vậy là kết thúc một gói.

UART là giao thức không đồng bộ, do đó không có đường clock nào điều chỉnh tốc độ truyền dữ liệu. Người dùng phải đặt cả hai thiết bị để giao tiếp ở cùng tốc độ. Tốc độ này được gọi là tốc độ truyền, được biểu thị bằng bit trên giây hoặc bps. Tốc độ truyền thay đổi đáng kể, từ 9600 baud đến 115200 và hơn nữa. Tốc độ truyền giữa UART truyền và nhận chỉ có thể chênh lệch khoảng 10% trước khi thời gian của các bit bị lệch quá xa.

**GIAO THỨC CAN:**

Controller Area Network (CAN hoặc CAN Bus) là công nghệ mạng nối tiếp, tốc độ cao, bán song công, hai dây. Ban đầu CAN được thiết kế dành cho ngành công
nghiệp ô tô, tuy nhiên hiện nay CAN cũng đã trở thành một tiêu chuẩn phổ biến trong tự động hóa công nghiệp và các ngành khác.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/fae69f91-e418-4228-92ee-4d06e0ee2706)

**CAN TRANSCEIVER:**

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/5db8c022-1cb2-4b72-877d-90bccf78e34b)

Truyền dữ liệu: Đi từ MCU ra 2 chân CANTX ra 2 chân CANH hoặc CANL để truyền dữ liệu, chỉ truyền ra không nhận lại trên TX vì có diot.

Nhận dữ liệu: Nhận dữ liệu từ 2 chân từ CANH hoặc CANL truyền qua chân CANRX vào MCU.

*CANH và CANL được bắt xoắn dây với nhau để tránh hiện tượng nhiễu làm sai lệch dữ liệu truyền nhận*

BUS CAN gồm 2 trạng thái là dominent và recessive, tương ứng với trạng thái 0 và 1

Dominent gồm 2 dạng truyền là CAN SLOW SPEED và CAN HIGH SPEED

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/44c0367c-78e5-495e-81f4-9f240189a501)

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/8a2c7a2c-63ee-4beb-a23c-f2e9695b35be)


Ví dụ: Khi MCU muốn truyền bit 0 cho các node khác ở chế độ slow speed, nó sẽ truyền bit 0 cho CAN CONTROLER, CAN CONTROLER -> Transceiver sẽ biến điện áp ở CANH = 4V và CANL = 1V, ngược lại muốn truyền bit 1 thì CANH = 1.75V, CANL = 3.25V.

Khi đọc dữ liệu, transceiver sẽ tính trị tuyệt đối giữa CANH và CANL, nếu CANH - CANL > = 3V sẽ hiểu là bit 0 , <=1.75 là bit 1.

Mỗi CAN sẽ có 1 ID khác nhau, mỗi ID sẽ có mức độ ưu tiên khác nhau, nếu ID nào có độ ưu tiên lớn hơn sẽ truyền trước.

Ví dụ: Khi có 3 ID cùng đang truyền =>> tín hiệu transceiver nhận được ở CANH và CANL không phải là điện áp quy định =>> nhận ra có nhiều thằng truyền 1 lúc (ID càng nhỏ độ ưu tiên càng lớn)

DATAFRAME CAN

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/e3c199c9-e187-44dd-b941-e3909219a4c3)

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/f782c2e3-8aca-4d4f-8af0-51a4a0929dbd)


**1. Trường bắt đầu khung (Start Of Frame Field – SOF)**

Với cả 2 định dạng của chuẩn CAN 2.0 thì trường bắt đầu là vị trí của bit đầu tiên trong khung. Trường này chiếm 1 bit dữ liệu. Bit đầu tiên này là một Dominant Bit (mức logic 0) đánh dấu sự bắt đầu của một Data Frame.

**2. Trường xác định quyền ưu tiên (Arbitration Field)**

Định dạng vùng xác định quyền ưu tiên là khác nhau đối với dạng khung chuẩn và khung mở rộng.

● Định dạng chuẩn: vùng xác định quyền ưu tiên có độ dài 12 bit, bao gồm 11 bit ID và 1 bit RTR.

● Định dạng mở rộng: trường xác định quyền ưu tiên có độ dài 32 bit, bao gồm có 29 bit ID, 1 bit SRR, 1 bit IDE và 1 bit RTR.

Trong đó:

*Bit RTR (Remote Transmission Request)*

● Là bit dùng để phân biệt khung là Data Frame hay Remote Frame.
● Nếu là Data Frame, bit này luôn bằng 0 (Dominant Bit).
● Nếu là Remote Frame, bit này luôn bằng 1 (Recessive Bit).
● Vị trí bit này luôn nằm sau bit ID.

Trường hợp nếu Data Frame và Remote Frame có cùng ID được gửi đi đồng thời thì Data Frame sẽ được ưu tiên hơn.

*Bit SRR (Substitute Remote Request)*

● Bit này chỉ có ở khung mở rộng.
● Bit này có giá trị là 1 (Recessive Bit).
● So với vị trí tương ứng trong khung chuẩn thì bit này trùng với vị trí của bit
RTR nên còn được gọi là bit thay thế (Substitute).

Giả sử có hai Node cùng truyền, một Node truyền Data Frame chuẩn, một Node truyền Data Frame mở rộng có ID giống nhau thì Node truyền khung chuẩn sẽ thắng phân xử quyền ưu tiên vì đến vị trí sau ID, khung chuẩn là bit RTR = 0, còn khung mở rộng là bit SRR = 1. Như vậy, khung chuẩn chiếm ưu thế hơn so với khung mở rộng khi có ID như nhau.

*Bit IDE (Identifier Extension)*

● Đây là bit phân biệt giữa loại khung chuẩn và khung mở rộng: IDE = 0 quy định khung chuẩn, IDE = 1 quy định khung mở rộng.

● Bit này nằm ở trường xác định quyền ưu tiên với khung mở rộng và ở trường điều khiển với khung chuẩn.

**3. Trường điều khiển (Control Field)**

Khung chuẩn và khung mở rộng có định dạng khác nhau ở trường này:

● Khung chuẩn gồm IDE, r0 và DLC (Data Length Code).

● Khung mở rộng gồm r1, r0 và DLC.

Trong đó:

Bit IDE: Dùng phân biệt loại khung (đã được trình bày ở trên).

Bit r0, r1 (hai bit dự trữ)

Tuy hai bit này phải được truyền là Recessive Bit bởi bộ truyền nhưng bộ nhận không quan tâm đến giá trị 2 bit này. Bộ nhận có thể nhận được các tổ hợp 00, 01, 10 hoặc 11 của r1 và r0 nhưng không coi đó là lỗi mà bỏ qua và nhận thông điệp bình thường.

*DLC (Data Length Code)*

● Có độ dài 4 bit quy định số byte của trường dữ liệu của Data Frame

● Chỉ được mang giá trị từ 0 đến 8 tương ứng với trường dữ liệu có từ 0 đến 8 byte dữ liệu. Data Frame có thể không có byte dữ liệu nào khi DLC = 0.

● Giá trị lớn hơn 8 không được phép sử dụng. Hình dưới mô tả các loại mã bit mà DLC có thể chứa để quy định số byte của trường dữ liệu.

**4. Trường dữ liệu (Data Field)**

Trường này có độ dài từ 0 đến 8 byte tùy vào giá trị của DLC ở trường điều khiển

**5. Trường kiểm tra (Cyclic Redundancy Check Field – CRC)**

Trường kiểm tra hay trường CRC gồm 16 bit và được chia làm hai phần là:

● CRC Sequence: gồm 15 bit CRC tuần tự

● CRC Delimiter: là một Recessive Bit làm nhiệm vụ phân cách trường CRC với trường ACK

● Mã kiểm tra CRC phù hợp nhất cho các khung mà chuỗi bit được kiểm tra có chiều dài dưới 127 bit, mã này thích hợp cho việc phát hiện các trường hợp sai nhóm (Bus Error). Ở đây, tổng bit từ trường bắt đầu (SOF) đến trường dữ liệu (Data Field) tối đa là 83 bit (khung định dạng chuẩn) và 103 bit (khung định dạng mở rộng).

=> Trường CRC bảo vệ thông tin trong Data Frame và Remote Frame bằng cách thêm các bit kiểm tra dự phòng ở đầu khung truyền. Ở đầu khung nhận, cũng sẽ tính toán CRC như bộ truyền khi đã nhận dữ liệu và so sánh kết quả đó với CRC Sequence mà nó đã nhận được, nếu khác nhau tức là đã có lỗi, nếu giống nhau tức là đã nhận đúng từ trường SOF đến trường dữ liệu.

**6. Trường báo nhận (Acknowledge Field – ACK)**

Trường báo nhận hay trường ACK có độ dài 2 bit và bao gồm hai phần là ACK Slot và ACK Delimiter.

● ACK Slot: có độ dài 1 bit, một Node truyền dữ liệu sẽ thiết lập bit này là Recessive. Khi một hoặc nhiều Node nhận chính xác giá trị thông điệp (không có lỗi và đã so sánh CRC Sequence trùng khớp) thì nó sẽ báo lại cho bộ truyền bằng cách truyền ra một Dominant Bit ngay vị trí ACK Slot để ghi đè lên Recessive Bit của bộ truyền.

● ACK Delimiter: có độ dài 1 bit, nó luôn là một Recessive Bit. Như vậy, ta thấy rằng ACK Slot luôn được đặt giữa hai Recessive Bit là CRC Delimiter và ACK Delimiter.

**7. Trường kết thúc (End Of Frame Field – EOF)**

Trường EOF là trường thông báo kết thúc một Data Frame hay Remote Frame.

Trường này gồm 7 Recessive Bit.

# INTERRUPT, TIMER.
**Interrupt:** là một số sự kiện khẩn cấp bên trong hoặc bên ngoài bộ vi điều khiển xảy ra, buộc vi điều khiển tạm dừng thực hiện chương trình hiện tại, phục vụ ngay lập tức nhiệm vụ mà ngắt yêu cầu – nhiệm vụ này gọi là trình phục vụ ngắt (ISR: Interrupt Service Routine).

**Trình phục vụ ngắt:** Đối với mỗi ngắt thì phải có một trình phục vụ ngắt (ISR) hay trình quản lý ngắt để đưa ra nhiệm vụ cho bộ vi điều khiển khi được gọi ngắt. Khi một ngắt được gọi thì bộ vi điều khiển sẽ chạy trình phục vụ ngắt. Đối với mỗi ngắt thì có một vị trí cố định trong bộ nhớ để giữ địa chỉ ISR của nó. Nhóm vị trí bộ nhớ được dành riêng để lưu giữ địa chỉ của các ISR được gọi là bảng vector ngắt. 

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/02ee7272-93f5-4bfe-918b-b920fcf1d95f)

**Quy trình thực hiện một ngắt:**
- Nó hoàn thành nốt lệnh đang thực hiện và lưu địa chỉ của lệnh kế tiếp vào **Stack pointer**.

- Nó cũng lưu tình trạng hiện tại của tất cả các ngắt.

- Nó nhảy đến một vị trí cố định trong bộ nhớ được gọi là bảng vector ngắt, nơi lưu giữ địa chỉ của một trình phục vụ ngắt.

- Bộ vi điều khiển nhận địa chỉ ISR từ bảng vector ngắt và nhảy tới đó. Nó bắt đầu thực hiện trình phục vụ ngắt cho đến lệnh cuối cùng của ISR và trở về chương trình chính từ ngắt.

- Khi bộ vi điều khiển quay trở về nơi nó đã bị ngắt. Trước hết nó nhận địa chỉ của bộ đếm chương trình PC từ Stack pointer bằng cách kéo 02 byte trên đỉnh của Stack pointer vào PC. Sau đó bắt đầu thực hiện tiếp các lệnh từ địa chỉ đó.

**Các loại kiểu ngắt:**
- LOW: Kích hoạt liên tục khi trạng thái digital ở mức thấp.
- HIGH: Kích hoạt liên tục khi trạng thái digital ở mức cao.
- RISING: Kích hoạt khi trạng thái của chân digital chuyển từ mức điện áp thấp sang mức điện áp cao.
- FALLING: Kích hoạt khi trạng thái của chân digital chuyển từ mức điện áp cao sang mức điện áp thấp.



**Timer:** Bộ đếm/Bộ định thời: Đây là các ngoại vi được thiết kế để thực hiện một nhiệm vụ đơn giản: đếm các xung nhịp. Mỗi khi có thêm một xung nhịp tại đầu vào đếm thì giá trị của bộ đếm sẽ được tăng lên 01 đơn vị (trong chế độ đếm tiến/đếm lên) hay giảm đi 01 đơn vị (trong chế độ đếm lùi/đếm xuống).
Xung nhịp đưa vào đếm có thể là một trong hai loại:

- Xung nhịp bên trong IC: Đó là xung nhịp được tạo ra nhờ kết hợp mạch dao động bên trong IC và các linh kiện phụ bên ngoài nối với IC. Trong trường hợp sử dụng xung nhịp loại này, người ta gọi là các bộ định thời (timers). Do xung nhịp bên loại này thường đều đặn nên ta có thể dùng để đếm thời gian một cách khá chính xác.

- Xung nhịp bên ngoài IC: Đó là các tín hiệu logic thay đổi liên tục giữa 02 mức 0-1 và không nhất thiết phải là đều đặn. Trong trường hợp này người ta gọi là các bộ đếm (counters). Ứng dụng phổ biến của các bộ đếm là đếm các sự kiện bên ngoài như đếm các sản phầm chạy trên băng chuyền, đếm xe ra/vào kho bãi…

Một khái niệm quan trọng cần phải nói đến là sự kiện “tràn” (overflow). Nó được hiểu là sự kiện bộ đếm đếm vượt quá giá trị tối đa mà nó có thể biểu diễn và quay trở về giá trị 0. Với bộ đếm 8 bit, giá trị tối đa là 255 (tương đương với FF trong hệ Hexa) và là 65535 (FFFFH) với bộ đếm 16 bit.


# PROJECT: TPMS

Hệ thống giám sát nhiệt độ và áp suất của từng bánh xe, hiển thị và cảnh báo cho người dùng thông qua màn hình monitoring. 

Hệ thống bao gồm : 
+ 4 cảm biến TPS gắn vào 4 bánh xe, trong mỗi TPS bao gồm : cảm biến nhiệt độ, cảm biến áp suất, pin, bộ RF transmit.
+ ECU: RF receiver, mcu nhận thông tin từ RF.
+ Màn hình hiển thị: kết nối giao tiếp với ecu, giao thức : ....

Khi hoạt động ECU sẽ gửi tín hiệu remote frame cho các TPS, TPS sẽ gửi lại data frame cho ECU bao gồm : trạng thái lốp, thông số áp suất.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/dabfc299-1730-4eac-a2a8-5dc540698b6d)

Áp suất tiêu chuẩn: 
+ Sedan: 32psi - 35psi (220kpa - 240kpa)
+ SUV : 35psi - 45 psi (240kpa - 310kpa)

Sau khi nhận được thông số từ TPS, ECU sẽ so sánh thông số nhận được với thông số tiêu chuẩn đã thiết lập trong chương trình
VD : nếu áp suất < áp suất tiêu chuẩn 20% sẽ cảnh báo, thấp hơn nữa sẽ buộc dừng xe (< 20 %)

Sẽ có một thẻ nhớ để lưu các thông tin của xe -> ktv có thể cắm máy test để nhận được thông tin này.

# AUTONOMUS PARKING SYSTEM

Hệ thống đỗ xe tự động là hệ thống hỗ trợ cho xe tự động tìm vị trí đỗ xe phù hợp và thực hiện thao tác đỗ mà không cần đến sự can thiệp của người lái.
Hệ thống này hoạt động thông qua việc kết hợp giữa máy tính trên xe và các cảm biến, camera để xác định vị trí, khoảng cách, hướng đi, hỗ trợ chiếc xe hoặc tìm kiếm nơi đỗ phù hợp nhất.
Sử dụng camera để xác định khoảng cách, nhận diện chướng ngại vật, nhận diện vị trí thích hợp, biển báo, ....

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/316920df-94c0-4149-a91e-c08423faf51d)

Trước khi tự động đậu vào bãi xe, để xác định khoảng cách. Đầu tiên camera sẽ xác định điểm ảnh (điểm làm mốc) trong open cv, sẽ có 2 điểm làm mốc để tính khoảng cách này.

Sử dụng thuật toán FIST.

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/c5597ae2-471c-4e95-8b5b-a954211ef94c)

Đầu tiên sẽ chụp một bức ảnh, chương trình sẽ đọc ảnh, tiếp theo sẽ khởi tạo một ma trận điểm ảnh, mỗi pixel sẽ cấu tạo thành 1 bức ảnh, mỗi pixel sẽ có cường độ màu sắc từ 0 -> 1. Khởi tạo 1 detector.

Tiếp theo sẽ tìm điểm mốc trên ảnh, thuật toán này đã được training trước (tìm keypoints).

Sau đó sẽ vẽ 1 đường thẳng từ camera ra điểm mốc và tính khoảng cách. CT tính d = FxW_real/W_image

Trong dó d: khoảng cách
F: Tiêu cự camera (bao nhiêu pixel)
W_real: Chiều rộng điểm ảnh thực tế ngoài đời
W_image: Chiều rộng điểm ảnh trên hình

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/805ce71f-ee6e-48fb-8b22-0a1ad24ee878)

W_real, F có sẵn, W_image từ trong hàm của opencv tính ra được =>> tính ra đc d.

Tiếp theo sẽ có thuật toán để xác định chữ số, vị trí vật thể để tính khoảng cách

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/806458ad-942c-489f-a586-f3b6c75f9f45)

Khởi tạo HOG descriptor để xác định chữ số

Khởi tạo hàm hog.detectMultiSacle();

Sau đó sẽ có hàm tính khoảng cách từ xe đến mỗi chứ số.

Tiếp theo sẽ có cảm biến lidar xác định khoảng cách trung bình

Camera và Lidar kết nối với MCU bằng USB. cả cụm là ECU đo khoảng cách. trả về ECU chính bằng CAN

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/a62501cf-c801-45f9-b18b-5328eb8e68cb)

![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/22266dda-e4df-4f8f-9eb2-c3faf3cd79ea)

Nhiệm vụ chính của Camera là để xác định khoảng cách, xác định số và vật thể.

Nhiệm vụ của Lidar là phát ra sóng siêu âm để đo khoảng cách trung bình với vật thể xung quanh, hiệu chỉnh với khoảng cách từ camera để tính d chính xác nhất.
	




