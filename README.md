# EmbeddedT6
# COMPLIER
![image](https://github.com/ducduy0712/EmbeddedT6/assets/136168376/d03da076-4778-42dc-a42d-9f2a76c4be35)

Compiler là quá trình được hiểu là biên dịch từ ngôn ngữ lập trình sang ngôn ngữ cho máy hiểu được ( từ file.c sang file.exe).
Qúa trình compiler bao gồm 4 giai đoạn: preprocesser(tiền xử lý), Compiler, Assembler, Linker.

Preprocesser: Là bước tiền xử lý của máy, dịch ra từ filec.c sang file.i (preprocessed source). Thay thế tất cả các include < thư viện > bằng các thư viện,
thay thế define bằng các giá trị, bỏ comments. Câu lệnh: gcc -E file.c -o file.i.

Compiler: Là bước chuyển file từ file.i sang file.s (assembly code). Câu lệnh: gcc  file.i -S file.s.

Assembler: Là bước chuyển file từ file.s sang file.o + librabries(hình ảnh, âm thanh). Câu lệnh: gcc -c file.s -o file.o.

Linker: Là bước liên kết  file.o và các librabries  sang file.exe (excutable) để có thể chạy trên máy tính, hoặc có thể tạo thành file.h (hex) để nạp vào các vi điều khiển.

Lưu ý : 
+ Trong quá trình tiền xử lý, có include bao nhiêu file thì cũng chỉ ra 1 file.i chính.
+ Khi include file cần chú các biến của các file có giống nhau không để tránh xảy ra lỗi khi chạy.
