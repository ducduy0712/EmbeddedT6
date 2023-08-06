
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <cstring>
#include "C:\Users\duydu\code\QUANLYSV\Header\quanlysv.hpp"
using namespace std;

SinhVien::SinhVien(string ten, string gioi_tinh, int Tuoi, double diemtoan, double diemly, 
double diemhoa){
    static int id = 1000;
    GIOI_TINH = gioi_tinh;
    tuoi = Tuoi;
    ID = id;
    id++;
    TEN = ten;
    diem_toan = diemtoan;
    diem_hoa = diemhoa;
    diem_ly = diemly;

// cac ham get
int SinhVien::getid(){
    return ID;
}

double SinhVien::getdiem_toan(){
    return diem_toan;
}
double SinhVien::getdiem_ly(){
    return diem_ly;
}
double SinhVien::getdiem_hoa(){
    return diem_hoa;
}

double SinhVien::getdiem_tb(){
    return diem_tb();
}

string SinhVien::get_ten(){
    return TEN;
}

int SinhVien::gettuoi(){
    return tuoi;
}

string SinhVien::get_ten(){
    return TEN;
}

TypeHocLuc SinhVien::HOC_LUC(){
    if (diem_tb() < 5)
    {
        return YEU;
    }else if(diem_tb() < 6.5){
        return TRUNG_BINH;
    }else if(diem_tb() < 8){
        return KHA;
    }else{
        return GIOI;
    };
}
TypeHocLuc SinhVien::getHocLuc(){
    return HOC_LUC();
}
string SinhVien::getGioiTinh(){
    return GIOI_TINH;
}
// cac ham set
void SinhVien ::set_gioitinh(string gioitinh){
    GIOI_TINH = gioitinh;
}
void SinhVien::set_tuoi(int Tuoi){
    tuoi = Tuoi;
}
void SinhVien::set_ten(string ten){
    TEN = ten;
}
void SinhVien::set_diemtoan(int diemtoan){
    diem_toan = diemtoan;
}

void SinhVien::set_diemly(int diemly){
    diem_toan = diemly;
}
void SinhVien::set_diemhoa(int diemhoa){
    diem_toan = diemhoa;
}
// cac ham them sv, cap nhat sv theo id, xoa sv theo id, tim theo ten, sap xep theo diem tb, sap xep theo ten, hien thi
//them sv
void themSV(list<SinhVien> &database){
    int  tuoi;
    double diem_toan, diem_ly, diem_hoa;
    string GIOI_TINH;
    string TEN;

    cout<<"TEN SV:"; cin>>TEN;
    cout <<"NHAP GIOI TINH: "; cin >> GIOI_TINH;
    cout<<"TUOI :"; cin >> tuoi;
    cout<<"Diem toan:"; cin >> diem_toan;
    cout << "Diem ly: "; cin >> diem_ly;
    cout << "Diem hoa:"; cin >> diem_hoa;
    assert (!TEN.empty() && "Ten khong duoc bo trong");
    assert ( !GIOI_TINH.empty()   && "khong duoc bo trong gioi tinh");
    assert ( tuoi > 0 && "Tuoi phai lon hon 0");
    assert (diem_toan >= 0 && diem_toan <=10 && "Diem toan tu 0 toi 10");
    assert (diem_ly >= 0 && diem_ly <=10 && "Diem ly tu 0 toi 10");
    assert (diem_hoa >= 0 && diem_hoa <=10 && "Diem hoa tu 0 toi 10");
    SinhVien sv (TEN, GIOI_TINH, tuoi, diem_toan, diem_ly, diem_hoa);
    
    database.push_back(sv);

}
//cap nhat sv theo id
void Capnhattheoid(list<SinhVien> &database){
    list <SinhVien>::iterator it;
    int Id;
    cout << "Nhap ID can tim : " << endl;
    cin >> Id;
     bool kiemtraID = 1;

    for (it = database.begin(); it != database.end(); it++)
    {
        if ((*it).getid() == Id )
        {       int chon;
                cout << "Thong tin sinh vien hien tai:" << endl;
                cout << "Ten: " << (*it).get_ten() << endl;
                cout << "Gioi tinh:   " << (*it).getGioiTinh() << endl;
                cout << "Tuoi: " << (*it).gettuoi() << endl;
                cout << "Diem toan: " << (*it).getdiem_toan() << endl;
                cout << "Diem ly: " << (*it).getdiem_toan() << endl;
                cout << "Diem hoa: " << (*it).getdiem_toan() << endl;

                cout << "Thong tin muon cap nhat" << endl;
                cout << " 1. Ten" << endl;
                cout << " 2. Gioi tinh" << endl;
                cout << " 3. Tuoi" << endl;
                cout << " 4. Diem toan" << endl;
                cout << " 5. Diem ly" << endl;
                cout << " 6. Diem hoa" << endl;
                cout << " Chon" << endl;
                cin >> chon;
                
                switch(chon){
                    case 1:{
                        cout << "Nhap ten moi"<< endl;
                        string tenmoi;
                        cin >> tenmoi;
                        (*it).set_ten(tenmoi);
                        break;
                    }
                    case 2:{
                        cout << "Nhap gioi tinh" << endl;
                        string Gioitinh;
                        cin >> Gioitinh;
                        (*it).set_gioitinh(Gioitinh);
                        break;
                    }
                    case 3:{
                        cout << "Nhap Tuoi" << endl;
                        int tuoimoi;
                        cin >> tuoimoi;
                        (*it).set_tuoi(tuoimoi);
                        break;
                    }
                    case 4 :{
                        cout << " Nhap diem toan" << endl;
                        int diemtoanmoi;
                        cin >> diemtoanmoi;
                        (*it).set_diemtoan(diemtoanmoi);
                        break;
                    }
                    case 5 : {
                        cout << " Nhap diem ly" << endl;
                        int diemlymoi;
                        cin >> diemlymoi;
                        (*it).set_diemtoan(diemlymoi);
                        break;
                    }
                    case 6 : {
                        cout << " Nhap diem hoa" << endl;
                        int diemhoamoi;
                        cin >> diemhoamoi;
                        (*it).set_diemtoan(diemhoamoi);
                        break;
                    }
                }

                kiemtraID = 0;
        }

if (kiemtraID){
        cout << "Khong tim thay ID" << endl;
    }
}
}
//xoa sv theo id
void xoasinhvien(list <SinhVien> &database ){
    int Id;
    cout << "Nhap Id sinh vien can xoa" << endl;
    cin >> Id;
    list <SinhVien>::iterator   it;
    list <SinhVien>::iterator   temp;
    
     bool kiemtraID = 1;

    for (it = database.begin(); it != database.end() ; it++)
    {
        if ((*it).getid() == Id )
        {       
                temp = it;
                kiemtraID = 0;
        }
    
}
if (kiemtraID){
        cout << "Khong tim thay ID" << endl;
    }else{
        database.erase(temp);
        cout << "Da xoa SinhVien khoi danh sach" << endl;
    }
}

//tim sv theo ten
void timsinhvientheoten (list<SinhVien> database){
    string ten;
    bool checkten = 1;
    cout << "Nhap ten can tim";
    cin >> ten;
    list <SinhVien>::iterator   it;
         for (it = database.begin(); it != database.end() ; ++it){
            if ((*it).get_ten() == ten){
                cout << "Thong tin Sinh vien" << endl;
                cout << "Ten: " << (*it).get_ten() << endl;
                cout << "Gioi tinh:  " << (*it).getGioiTinh() << endl;
                cout << "Tuoi: " << (*it).gettuoi() << endl;
                cout << "Diem toan: " << (*it).getdiem_toan() << endl;
                cout << "Diem ly: " << (*it).getdiem_toan() << endl;
                cout << "Diem hoa: " << (*it).getdiem_toan() << endl;
                checkten = 0;
            }
            if (checkten){
                 cout << "Khong co ten Sinh vien nay" << endl;
            }

         }
}
//sap xep theo diem tb
void sapxeptheogpa(list<SinhVien> &database){
    list <SinhVien>::iterator   it;
    list <SinhVien>::iterator   temp;
    for (it = database.begin(); it != database.end() ; ++it){
        for (temp = it; temp != database.end(); ++temp){
            if ( (*it).getdiem_tb()>(*temp).getdiem_tb()){
                swap(*it,*temp);
        }
    }
    }
}
// sap xep theo ten
void sapxeptheoten(list<SinhVien> &database){
    list <SinhVien>::iterator   it;
    list <SinhVien>::iterator   temp;
     for (it = database.begin(); it != database.end() ; ++it){
        for (temp = it; temp != database.end(); ++temp){
            if ( (*it).get_ten().compare((*temp).get_ten()) > 0 ){
                swap(*it,*temp);
        }
    }
    }

}
// hien thi danh sach
void hienthi(list<SinhVien> database){
    list <SinhVien>::iterator it;
    for (it = database.begin(); it != database.end(); it++){
        cout << "Thong tin Sinh vien: " << endl;
        cout << "Ten: " << (*it).get_ten() << endl;
        cout << "Gioi tinh:  " << (*it).getGioiTinh() << endl;
        cout << "Tuoi: " << (*it).gettuoi() << endl;
        cout << "Diem toan: " << (*it).getdiem_toan() << endl;
        cout << "Diem ly: " << (*it).getdiem_toan() << endl;
        cout << "Diem hoa: " << (*it).getdiem_toan() << endl;
    }
}
