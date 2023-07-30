#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <cstring>
#include "C:\Users\duydu\code\QUANLYSV\Header\quanlysv.hpp"




using namespace std;





int main(){
    
    list <SinhVien> data_base;
     int chon;
     while (true)
     {
        cout << "1. Them sinh vien." << endl;
        cout << "2. Cap nhap thong tin sinh vien theo ID." << endl;
        cout << "3. Xoa sinh vien theo ID." << endl;
        cout << "4. Tim kiem sinh vien theo ten." << endl;
        cout << "5. Sap xep danh sach sinh vien theo diem trung binh ." << endl;
        cout << "6. Sap xep danh sach sinh vien theo ten." << endl;
        cout << "7. Hien thi danh sach sinh vien." << endl;
        cout << "8. Thoat chuong trinh." << endl;
        cout << "Chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:{
            themSV(data_base);
            break;
        }
        case 2:{
            Capnhattheoid(data_base);
            break;
        }
        case 3:{
            xoasinhvien(data_base);
            break;
        }
        case 4:{
            timsinhvientheoten(data_base);
            break;
        }
        case 5:{
            sapxeptheogpa(data_base);
            break;
        }
        case 6:{
            sapxeptheoten(data_base);
            break;
        }case 7:{
            hienthi(data_base);
            break;
        }
        case 8:{
            return 0;
        }
        }
     }
     

    
    return 0;
}