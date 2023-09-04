#include <iostream>
#include <string>

using namespace std;

class Wheel{
private:
int speed;
public:
int getspeed(){
    return speed;
}
void setspeed( int a){
    speed  = a;
}
};

class Car{
private:
Wheel wheel;
int mass;
int passenger;
public:
Wheel & getwheel(){
    return wheel;
}
int getmass(){
    return mass;
}
void setmass( int masss_){
    mass  = masss_;
}
int getpassenger(){
    return passenger;
}
void setpassenger( int passenger_){
    passenger = passenger_;
}
int totalmass(){
    return mass + passenger;
}
};

class ABS{
private:
Car car;
int speedABS = 10;
public:
void brake(){
    if (car.getwheel().getspeed() <= speedABS){
        cerr << "Brake is locked, ABS need to be used\n" ;
        cerr << "Total mass of the car is: " << car.totalmass() << endl;
    }else cerr << "Brake is working\n";
}
Car & getcar(){
    return car;
}
void setCar( Car & car_){
    car = car_;
}
void settCar ( Car & car_){
     car_ = car;
}
};

int main(){
    Car car;
    ABS abs;
    car.getwheel().setspeed(5);
    car.setmass(1000);
    car.setpassenger(0);
    abs.setCar(car);
    abs.brake();
    abs.getcar().setpassenger(140);
    abs.brake();
    abs.settCar(car);
    cout << car.totalmass();
    
}