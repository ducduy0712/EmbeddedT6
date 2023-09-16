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
##C++ NÂNG CAO

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
