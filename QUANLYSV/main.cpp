#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <algorithm>



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

class SinhVien{
    private:
    int ID, tuoi;
    TypeGioiTinh GIOI_TINH;
    TypeHocLuc HOC_LUC();
    double diem_toan, diem_ly, diem_hoa;
    double diem_tb;
    string TEN;
    public:
    int getid();
    void set_ten(string ten);
    double getdiem_toan();
    double getdiem_ly();
    double getdiem_hoa();
    double getdiem_tb();
    string get_ten();
    TypeHocLuc getHocLuc();
    void Hienthi();
    SinhVien(string ten, TypeGioiTinh gioi_tinh, int tuoi, double diemtoan, double diemly, double diemhoa);
};
void SinhVien::set_ten(string ten){
    TEN = ten;
}
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


   

string SinhVien::get_ten(){
    return TEN;
}

TypeHocLuc SinhVien::HOC_LUC(){
    if (diem_tb < 5)
    {
        return YEU;
    }else if(diem_tb < 6.5){
        return TRUNG_BINH;
    }else if(diem_tb < 8){
        return KHA;
    }else{
        return GIOI;
    };
}
TypeHocLuc SinhVien::getHocLuc(){
    return HOC_LUC();
}
SinhVien::SinhVien(string ten, TypeGioiTinh gioi_tinh, int tuoi, double diemtoan, double diemly, 
double diemhoa){
    static int id = 1000;
    ID = id;
    id++;
    TEN = ten;
    diem_tb = (diemtoan + diemly + diemhoa)/3;
    diem_toan = diemtoan;
    diem_hoa = diemhoa;
    diem_ly = diemly;
    

};

double SinhVien::getdiem_tb(){
    return diem_tb;
}

void themSV(list<SinhVien> &database){
    int  tuoi;
    double diem_toan, diem_ly, diem_hoa;
    TypeGioiTinh GIOI_TINH;
    string TEN;

    cout<<"TEN SV:"; cin>>TEN;
    cout<<"TUOI :"; cin >> tuoi;
    cout<<"Diem toan:"; cin >> diem_toan;
    cout << "Diem ly: "; cin >> diem_ly;
    cout << "Diem hoa:"; cin >> diem_hoa;

    SinhVien sv (TEN, GIOI_TINH, tuoi, diem_toan, diem_ly, diem_hoa);
    database.push_back(sv);

}
void Capnhatthongtin(list<SinhVien> &database, int Id, string name){
    list <SinhVien>::iterator it;
    
     bool kiemtraID = 1;

    for (it = database.begin(); it != database.end(); it++)
    {
        if ((*it).getid() == Id )
        {
                (*it).set_ten(name);
                //cout<< (*it).get_ten() << endl;
                kiemtraID = 0;
        }
    
}
if (kiemtraID){
        cout << "Khong tim thay ID" << endl;
    }
}

void hienthi(list<SinhVien> database){
    list <SinhVien>::iterator it;
    for (it = database.begin(); it != database.end(); it++){
        cout << (*it).get_ten() << endl;
        cout << (*it).getid() << endl;
    }
}
void xoasinhvien(list <SinhVien> &database , int Id){
    list <SinhVien>::iterator   it;
    list <SinhVien>::iterator  temp;
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
    }
}




int main(){
    
    list <SinhVien> data_base;
    SinhVien sv("duy",NAM,19,3.5,4.5,5.7);
    data_base.push_back(sv);
    SinhVien sv2("tai",NAM,19,3.5,4.5,5.7);
    data_base.push_back(sv2);
    hienthi(data_base);   
    //sv.set_ten("mamama");
    Capnhatthongtin(data_base, 1001, "quynh");
    //cout << sv.get_ten() << endl;
    //cout << sv2.get_ten() << endl;
    hienthi(data_base);
    xoasinhvien(data_base, 1000);
    hienthi(data_base);   
    
    
    
    

    

    //themSV(data_base);
}
