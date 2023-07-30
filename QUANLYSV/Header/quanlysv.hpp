#ifndef QUANLYSV_HPP
#define QUANLYSV_HPP

#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <cstring>
using namespace std;


typedef enum{
    NU,
    NAM
}TypeGioiTinh;

typedef enum{
    GIOI,
    KHA,
    TRUNG_BINH,
    YEU
}TypeHocLuc;

//class

class SinhVien{
    private:
    int ID, tuoi;
    string GIOI_TINH;
    TypeHocLuc HOC_LUC();
    double diem_toan, diem_ly, diem_hoa;
    double diem_tb();
    string TEN;
    public:
    int getid();
    double getdiem_toan();
    double getdiem_ly();
    double getdiem_hoa();
    double getdiem_tb();
    string get_ten();
    int gettuoi();
    TypeHocLuc getHocLuc();
    string getGioiTinh();
    void set_ten(string ten);
    void set_tuoi(int tuoi);
    void set_diemtoan(int diemtoan);
    void set_diemly(int diemly);
    void set_diemhoa(int diemhoa);
    void set_gioitinh(string gioitinh);
    SinhVien::SinhVien(string ten, string gioi_tinh, int Tuoi, double diemtoan, double diemly, 
double diemhoa);
};

// cac ham 

void themSV(list<SinhVien> &database);

void Capnhattheoid(list<SinhVien> &database);

void xoasinhvien(list <SinhVien> &database );

void timsinhvientheoten (list<SinhVien> database);

void sapxeptheogpa(list<SinhVien> &database);

void sapxeptheoten(list<SinhVien> &database);

void hienthi(list<SinhVien> database);


#endif