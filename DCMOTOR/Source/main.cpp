#include <iostream>
#include <string>

using namespace std;

typedef enum{
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = 0
}Typeclockwise;

typedef enum{
    START = 1,
    STOP = 0
}TypeStart;

class DCMotor{
    private:
    int voltage;
    int speed;
    int maxCurrent;
    int maxTemp;
    Typeclockwise direction;
    bool Isrunning = false;
    public:
    int getspeed(){
        return speed;
    }
    void setspeed( int speed_){
        speed = speed_;
    }
    Typeclockwise getdirection(){
        return direction;
    }
    void setdirection(Typeclockwise direction_){
        direction = direction_;
    }
    bool MotorRunning(){
        if ( Isrunning == false){
        cerr << "DC Motor is running\n";
         return Isrunning = true;
        }
    }
    bool MotorStop(){
        if (Isrunning == true){
        cerr << "DC Motor is stop\n";
        return Isrunning = false;
        }
    }
    int getCurrentmax(){
        return maxCurrent;
    }
    int getTempmax(){
        return maxTemp;
    }
    void setCurrentmax( int current){
        maxCurrent = current;
    }
    void setTempmax( int temp){
        maxTemp = temp;
    }
};

class FeedbackSystem{
    private:
    bool overloadDetected;
    bool overheatDetected;
    public:
    bool checkLoad( int maxcurrent){
        if (maxcurrent > 2){
            cerr << "DC Motor is overload\n";
             return overloadDetected = true;
        }else return overloadDetected = false;
    }
    bool checkHeat( int maxtemp){
        if( maxtemp > 100){
            cerr << "DC Motor is overheat\n";
           return overheatDetected = true;
        }else return overheatDetected = false;
    }
};

class DCMotorController{
    private:
    FeedbackSystem feedback;
    DCMotor motor;
    TypeStart start;
    public:
    void Motorstart(){
        if (feedback.checkHeat(motor.getTempmax()) == true && feedback.checkLoad(motor.getCurrentmax() == true)){
            cerr << "Motor is overload or overheat\n" ;
            motor.MotorStop();
        }else motor.MotorRunning();
    }
    void Motorstop(){
        motor.MotorStop();
    }
    void setspeed( int speed){
        motor.setspeed(speed);
        cerr << "Set speed sucessful\n";
    }
    void setdirection( Typeclockwise direction){
        motor.setdirection(direction);
        cerr << "Set direction sucessful\n";
    }
    DCMotor & getMotor(){
        return motor;
    }
};

int main(){
    DCMotorController controller;
    controller.getMotor().setspeed(10);
    controller.getMotor().setdirection(CLOCKWISE);
    controller.getMotor().setCurrentmax(1);
    controller.getMotor().setTempmax(80);
    cout << controller.getMotor().getTempmax() << endl;
    controller.Motorstart();


}