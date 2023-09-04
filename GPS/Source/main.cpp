#include <iostream>
#include <string>
#include <math.h>

using namespace std;

const int r = 6371;

class GPSPoint{
    private:
    int latitude;
    int longitude;
    public:
    int getlattitude(){
        return latitude;
    }
    int getlongitude(){
        return longitude;
    }
    bool isValid( int lat , int longi){
        if ( (lat  >= -90) && (lat <= 90) && (longi >=  -180) && (longi <=  180) ){
            return true;
        }
        else  {
            cerr << " WRONG  PLEASE ENTER AGAIN!!!!\n";
             return false;
             }
    }
    void input ( int latitude_ , int longitude_){
        latitude = latitude_;
        longitude = longitude_;
    }
    double toRadians_lat(){
        return latitude*(3.14/180);
    }
    double toRadians_long(){
        return longitude*(3.14/180);
    }
    double distanceTo( double lat , double longi){
        return 6371*2*asin(sqrt(pow(sin((lat - toRadians_lat())/2),2)) + cos(toRadians_lat())*cos(lat)*pow(sin((longi - toRadians_long())/2),2)) ;

    }
};
void input( GPSPoint point){
    int a;
    cout << "Enter latitude: " ; cin >> a;
    int b;
    cout << "Enter longitude: " ; cin >> b;
    if ( point.isValid(a , b) == true) {
        cout << "Enter Succsesful!!!" << endl;
        point.input(a , b);
        }

    else return input(point);

}
int main(){

    GPSPoint point1;
    GPSPoint point2;
    input(point1);
    input(point2);
    double a;
    a = point1.distanceTo(point2.getlattitude(), point2.getlongitude());
    cout  << "Distance of two point is: " << a << " Km" << endl;
    
    return 0;
}