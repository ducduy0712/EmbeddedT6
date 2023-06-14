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

Ví dụ: ```sh
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

NULL POINTER: Là con trỏ có dữ liệu và địa chỉ bằng 0, dùng trong trường hợp mà con trỏ chúng ta đã khai báo chưa sử dụng tới hoặc đã sử dụng xong.

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
