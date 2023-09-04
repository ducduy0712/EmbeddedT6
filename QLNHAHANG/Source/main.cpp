#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
    int second;
    int minute;
    int hour;
} typeTime;

typedef struct
{
    int day;
    int month;
    int year;
} typeDate;

typedef enum
{
    IN,
    OUT
} typeStatus;

typedef enum
{
    SERVING,
    NOTSERVICED
} typeService;
typedef struct
{
    typeTime time;
    typeDate date;
    typeStatus status;
} BookingHistory;

typedef enum
{
    JANITOR = 1,
    RECEPTIONIST = 2,
    LAUNDRY_STAFF = 3,
    LAUGGAGE_STAFF = 4,
    GRADENER = 5
} JobPosition;

typedef struct
{
    typeTime time;
    typeDate date;
    typeStatus Status;
} Schedule;

typedef enum
{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    ZERO = 0
} TypeRateStar;

typedef enum
{
    CASH = 1,
    INTERNETBANKING = 2,
    CREDIT = 3
} typePaymentMethod;

class Room
{
private:
    int ID;
    bool isBooked;  // false la chua co nguoi o, true la roi
    bool isCleaned; // false la chua co nguoi don, true la roi
public:
    int getID()
    {
        return ID;
    }
    Room(int number)
    {
        ID = number;
        isBooked = false;
        isCleaned = true;
    }
    bool IsAvailable()
    {
        return !isBooked && isCleaned;
    }
    void bookRoom()
    {
        isBooked = true;
    }
    void checkIn()
    {
        isBooked = true;
        isCleaned = false;
    }
    void checkOut()
    {
        isBooked = false;
        isCleaned = true;
    }
};
////////////////////////////////////////////CLASS CUSTOMER////
class Customer
{
private:
    int idRoomBooked;
    string name;
    string PhoneNumber;
    string address;
    vector<BookingHistory> bookinghistory;

public:
    vector<BookingHistory> &getbookinghistory()
    {
        return bookinghistory;
    }
    Customer(string name_ = " ", string phonenumber_ = " ", string address_ = " ", int id = 0)
    {
        name = name_;
        PhoneNumber = phonenumber_;
        address = address_;
        idRoomBooked = id;
    }
    int getidRoombooked()
    {
        return idRoomBooked;
    }
    string getname()
    {
        return name;
    }
    string getphonenumber()
    {
        return PhoneNumber;
    }
    string getaddress()
    {
        return address;
    }
    void setidroombooked(int id)
    {
        idRoomBooked = id;
    }
    void setname(string name_)
    {
        name = name_;
    }
    void setphone(string phone)
    {
        PhoneNumber = phone;
    }
    void setadress(string add)
    {
        address = add;
    }
    void AddBookingHistory(BookingHistory dataBooking)
    {
        bookinghistory.push_back(dataBooking);
    }
};
////////////////////////////////////////////CLASS CUSTOMER MANAGER////
class CustomerManager
{
private:
    vector<Customer> databaseCustomer;

public:
    void addCustomer(Customer &customer)
    {
        databaseCustomer.push_back(customer);
    }

    vector<Customer> &getdatabaseCustomer()
    {
        return databaseCustomer;
    }
    void editIDRoomCustomer(vector<Room> &databaseRoom, int id_current, int id_new);
    void editNameCustomer(vector<Room> databaseRoom, int id_current, string name_new);
    void editAddressCustomer(vector<Room> databaseRoom, int id_current, string add_new);
    void editPhoneCustomer(vector<Room> databaseRoom, int id_current, string phone_new);
    void eraseCustomer(vector<Room> &databaseRoom, int id_current, string name);
};

void CustomerManager::editIDRoomCustomer(vector<Room> &databaseRoom, int id_current, int id_new)
{
    for (int i = 0; i < databaseRoom.size(); i++)
    {
        if (databaseRoom[i].getID() == id_current)
            databaseRoom[i].checkOut();
        if (databaseRoom[i].getID() == id_new)
            databaseRoom[i].bookRoom();
    }

    for (int i = 0; i < databaseCustomer.size(); i++)
    {
        if (databaseCustomer[i].getidRoombooked() == id_current)
        {
            databaseCustomer[i].setidroombooked(id_new);
        }
    }
}

void CustomerManager ::editNameCustomer(vector<Room> databaseRoom, int id_current, string name_new)
{
    for (int i = 0; i < databaseCustomer.size(); i++)
    {
        if (databaseCustomer[i].getidRoombooked() == id_current)
        {
            databaseCustomer[i].setname(name_new);
        }
    }
}

void CustomerManager ::editAddressCustomer(vector<Room> databaseRoom, int id_current, string add_new)
{
    for (int i = 0; i < databaseCustomer.size(); i++)
    {
        if (databaseCustomer[i].getidRoombooked() == id_current)
        {
            databaseCustomer[i].setadress(add_new);
        }
    }
}
void CustomerManager ::editPhoneCustomer(vector<Room> databaseRoom, int id_current, string phone_new)
{
    for (int i = 0; i < databaseCustomer.size(); i++)
    {
        if (databaseCustomer[i].getidRoombooked() == id_current)
        {
            databaseCustomer[i].setphone(phone_new);
        }
    }
}
void CustomerManager ::eraseCustomer(vector<Room> &databaseRoom, int id_current, string name)
{
    for (int i = 0; i < databaseRoom.size(); i++)
    {
        if (databaseRoom[i].getID() == id_current)
            databaseRoom[i].checkOut();
    }

    for (int i = 0; i < databaseCustomer.size(); i++)
    {
        for (auto it = databaseCustomer.begin(); it != databaseCustomer.end(); it++)
        {
            if (databaseCustomer[i].getidRoombooked() == id_current && databaseCustomer[i].getname() == name)
            {
                databaseCustomer.erase(it);
            }
        }
    }
}
////////////////////////////////////////////CLASS EMPLOYEE////
class Employee
{
private:
    int ID;
    string Name;
    string Phonenumber;
    string address;
    Schedule schedule;
    JobPosition jobpositon;

public:
    Employee(string name = " ", string phonenumber = " ", string address_ = " ", int id = 0, Schedule schedule_ = {}, JobPosition jobpositon_ = {})
    {
        Name = name;
        Phonenumber = phonenumber;
        address = address_;
        ID = id;
        schedule = schedule_;
        jobpositon = jobpositon_;
    }
    int getid()
    {
        return ID;
    }

    string getname()
    {
        return Name;
    }
    string getPhonenumber()
    {
        return Phonenumber;
    }
    string getaddress()
    {
        return address;
    }
    Schedule getSchedule()
    {
        return schedule;
    }
    JobPosition getjobposition()
    {
        return jobpositon;
    }
    void setname(string name)
    {
        Name = name;
    }
    void setphonenumber(string phone)
    {
        Phonenumber = phone;
    }
    void setaddress(string add)
    {
        address = add;
    }
    void setschedule(Schedule schedule_)
    {
        schedule = schedule_;
    }
    void setJobposition(JobPosition jobposition_)
    {
        jobpositon = jobposition_;
    }
};
////////////////////////////////////////////CLASS USER////
class User
{
private:
    string USERNAME;
    string PASSWORD;

public:
    User(string username = "duytritue", string password = "11081999")
    {
        USERNAME = username;
        PASSWORD = password;
    }
    bool checkAuthenticate(string username, string password)
    {
        bool checkSignup = (username == USERNAME && password == PASSWORD);
        return checkSignup;
    }
    string getusername()
    {
        return USERNAME;
    }
    string getpassword()
    {
        return PASSWORD;
    }
    void setusername(string name)
    {
        USERNAME = name;
    }
    void setpassword(string pass)
    {
        PASSWORD = pass;
    }
};
////////////////////////////////////////////CLASS SERVICE AND UTILITIES////
class Service
{
private:
    int ID;
    string NameService;
    typeService status;

public:
    int getID()
    {
        return ID;
    }
    string getNameService()
    {
        return NameService;
    }
    typeService getstatus()
    {
        return status;
    }
    void setNameService(string name)
    {
        NameService = name;
    }
    void setStatus(typeService status_)
    {
        status = status_;
    }
    Service(string name = " ", typeService status_ = NOTSERVICED, int id = 0)
    {
        NameService = name;
        status = status_;
        ID = id;
    }
};
////////////////////////////////////////////CLASS SERVICE MANAGER////
class ServiceManager
{
private:
    vector<Service> databaseService;

public:
    vector<Service> &getdatabaseServive()
    {
        return databaseService;
    }
    void addService(Service service)
    {
        databaseService.push_back(service);
    }
    void editStatusService(int id, typeService status_);
    void eraseService(int id);
};

void ServiceManager ::editStatusService(int id, typeService status_)
{
    for (int i = 0; i < databaseService.size(); i++)
    {
        if (databaseService[i].getID() == id)
        {
            databaseService[i].setStatus(status_);
        }
    }
}
void ServiceManager ::eraseService(int id)
{
    for (int i = 0; i < databaseService.size(); i++)
    {
        for (auto it = databaseService.begin(); it != databaseService.end(); it++)
        {
            if (databaseService[i].getID() == id)
                databaseService.erase(it);
        }
    }
}

////////////////////////////////////////////CLASS SECURITY MANAGER////
class SecurityManager
{
private:
    vector<User> databaseUser;
    vector<Service> databaseService;
    User user;
    bool checkAuthenticate;

public:
    vector<Service> &getdatabaseServive()
    {
        return databaseService;
    }
    vector<User> &getdatabaseUser()
    {
        return databaseUser;
    }
    bool getcheckAuthenticate(string username, string password)
    {
        if (user.checkAuthenticate(username, password) || password == "admin")
        {
            return true;
        }
        else
            return checkAuthenticate;
    }
    void addUser(string name, string pass)
    {
        User user(name, pass);
        databaseUser.push_back(user);
    }
    void eraseUser(string username);
    void editpasswordUser(string username, string password_new);
    void setPasswordManager(string pass_new)
    {
        user.setpassword(pass_new);
    }
};

void SecurityManager ::eraseUser(string username)
{
    for (int i = 0; i < databaseUser.size(); i++)
    {
        for (auto it = databaseUser.begin(); it != databaseUser.end(); it++)
        {
            if (databaseUser[i].getusername() == username)
                databaseUser.erase(it);
        }
    }
}
void SecurityManager ::editpasswordUser(string username, string password_new)
{
    for (int i = 0; i < databaseUser.size(); i++)
    {
        if (databaseUser[i].getusername() == username)
        {
            databaseUser[i].setpassword(password_new);
        }
    }
}

////////////////////////////////////////////CLASS EMPLOYEE MANAGER////
class EmployeeManager
{
private:
    vector<Employee> databaseEmployee;
    User user;
    bool checkAuthenticate;

public:
    vector<Employee> &getdatabaseEmployee()
    {
        return databaseEmployee;
    }
    void addEmployee(Employee employee_)
    {
        databaseEmployee.push_back(employee_);
    }
    bool getcheckAuthenticate(string username, string password)
    {
        if (user.checkAuthenticate(username, password) || password == "admin")
        {
            checkAuthenticate = true;
        }
        return checkAuthenticate;
    }
    void EditnameEmployee(int id, string name_new);
    void EditPhonenumberEmployee(int id, string phone);
    void EditAddressEmployee(int id, string add);
    void EditShedule(int id, Schedule schedule_);
    void EditJobpositon(int id, JobPosition position);
    void EraseEmployee(int id);
};
void EmployeeManager ::EditnameEmployee(int id, string name_new)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        if (databaseEmployee[i].getid() == id)
        {
            databaseEmployee[i].setname(name_new);
        }
    }
}

void EmployeeManager ::EditPhonenumberEmployee(int id, string phone)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        if (databaseEmployee[i].getid() == id)
        {
            databaseEmployee[i].setphonenumber(phone);
        }
    }
}

void EmployeeManager ::EditAddressEmployee(int id, string add)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        if (databaseEmployee[i].getid() == id)
        {
            databaseEmployee[i].setaddress(add);
        }
    }
}

void EmployeeManager ::EditShedule(int id, Schedule schedule_)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        if (databaseEmployee[i].getid() == id)
        {
            databaseEmployee[i].setschedule(schedule_);
        }
    }
}

void EmployeeManager ::EditJobpositon(int id, JobPosition position)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        if (databaseEmployee[i].getid() == id)
        {
            databaseEmployee[i].setJobposition(position);
        }
    }
}
void EmployeeManager ::EraseEmployee(int id)
{
    for (int i = 0; i < databaseEmployee.size(); i++)
    {
        for (auto it = databaseEmployee.begin(); it != databaseEmployee.end(); it++)
        {
            if (databaseEmployee[i].getid() == id)
            {
                databaseEmployee.erase(it);
            }
        }
    }
}
////////////////////////////////////////////CLASS PAYMENT////
class Payment
{
private:
    int idRoom;
    vector<BookingHistory> dataCheckout;
    typePaymentMethod method;
    TypeRateStar Rate;
    string comment;
    int price;
    int payment;
    string namecustomer;
    string phonecustomer;
    string addresscustomer;

public:
    Payment(string comment_ = " ", typePaymentMethod method_ = CASH, TypeRateStar rate = ZERO, int payment_ = 0, int id = 0, string namecustomer_ = " ", string phone = " ", string add = " ", int price_ = 10)
    {
        comment = comment_;
        method = method_;
        Rate = rate;
        idRoom = id;
        payment = payment_;
        namecustomer = namecustomer_;
        phonecustomer = phone;
        addresscustomer = add;
        price = price_;
    }
    string getnamecustomer()
    {
        return namecustomer;
    }
    string getphonecustomer()
    {
        return phonecustomer;
    }
    string getaddresscustomer()
    {
        return addresscustomer;
    }
    int getpayment()
    {
        return payment;
    }
    void setpayment(int payment_)
    {
        payment = payment_;
    }

    typePaymentMethod getmethod()
    {
        return method;
    }
    void setmethod(typePaymentMethod method_)
    {
        method = method_;
    }

public:
    vector<BookingHistory> getdataCheckout()
    {
        return dataCheckout;
    }
    int getprice()
    {
        return price;
    }
    string getcomment()
    {
        return comment;
    }
    TypeRateStar getRate()
    {
        return Rate;
    }
    void setprice(int price_)
    {
        price = price_;
    }
    void setcomment(string comment_)
    {
        comment = comment_;
    }
    void setRate(TypeRateStar rate)
    {
        Rate = rate;
    }
    int getIDroom()
    {
        return idRoom;
    }
    int setIDroom(int id)
    {
        idRoom = id;
    }
    void addDataCheckout(BookingHistory data)
    {
        dataCheckout.push_back(data);
    }
};
///////////////////////////////////////////CLASS  PAYMENT MANAGER////
class Paymentmanager
{
private:
    vector<Payment> datapayment;

public:
    vector<Payment> &getdatapayment()
    {
        return datapayment;
    }

    void addDatapayment(Payment payment)
    {
        datapayment.push_back(payment);
    }
};

////////////////////////////////////////////function ////
void DisplaySchedule(EmployeeManager employeemanager, int id)
{
    for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
    {
        if (employeemanager.getdatabaseEmployee()[i].getid() == id)
        {
            cout << "Schedule of ID : " << employeemanager.getdatabaseEmployee()[i].getid() << endl;
            cout << "Date  " << endl;
            cout << "Day: " << employeemanager.getdatabaseEmployee()[i].getSchedule().date.day << endl;
            cout << "Month: " << employeemanager.getdatabaseEmployee()[i].getSchedule().date.month << endl;
            cout << "Year: " << employeemanager.getdatabaseEmployee()[i].getSchedule().date.year << endl;

            cout << "Time  " << endl;
            cout << "Second: " << employeemanager.getdatabaseEmployee()[i].getSchedule().time.second << endl;
            cout << "Minute: " << employeemanager.getdatabaseEmployee()[i].getSchedule().time.minute << endl;
            cout << "Hour: " << employeemanager.getdatabaseEmployee()[i].getSchedule().time.hour << endl;
        }
    }
}
void printListroom(vector<Room> &databaseRoom)
{
    cout << "List room: " << endl;
    cout << "  ID  ";
    for (int i = 0; i < databaseRoom.size(); i++)
    {
        cout << "      " << databaseRoom[i].getID();
    }
    cout << endl;
    cout << "Status";
    for (int i = 0; i < databaseRoom.size(); i++)
    {
        if (databaseRoom[i].IsAvailable() == true)
            cout << "      o";
        else
            cout << "      x";
    }
    cout << endl;
}

void Editroom(vector<Room> &databaseRoom, CustomerManager &customermanager)
{
    printListroom(databaseRoom);

    int key = 0;
    do
    {
        cout << "Enter current ID room: ";
        int ID_current;
        cin >> ID_current;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == ID_current)
            {
                cout << " Enter new ID room: ";
                int ID_new;
                cin >> ID_new;
                customermanager.editIDRoomCustomer(databaseRoom, ID_current, ID_new);
                cout << "Change room Successful !!!" << endl;
                cout << "1. Coutinue to Change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void EditName(vector<Room> databaseRoom, CustomerManager &customermanager)
{
    int key = 0;
    do
    {
        cout << "Enter current ID room: ";
        int ID_current;
        cin >> ID_current;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == ID_current)
            {
                cout << " Enter new name: ";
                string name_new;
                cin >> name_new;
                customermanager.editNameCustomer(databaseRoom, ID_current, name_new);
                cout << "Change name Successful !!!" << endl;
                cout << "1. Coutinue to Change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}
void EditAddress(vector<Room> databaseRoom, CustomerManager &customermanager)
{
    int key = 0;
    do
    {
        cout << "Enter current ID room: ";
        int ID_current;
        cin >> ID_current;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == ID_current)
            {
                cout << " Enter new address: ";
                string address_new;
                cin >> address_new;
                customermanager.editNameCustomer(databaseRoom, ID_current, address_new);
                cout << "Change address Successful !!!" << endl;
                cout << "1. Coutinue to Change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void Editphone(vector<Room> databaseRoom, CustomerManager &customermanager)
{
    int key = 0;
    do
    {
        cout << "Enter current ID room: ";
        int ID_current;
        cin >> ID_current;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == ID_current)
            {
                cout << " Enter new Phonenumber: ";
                string phone_new;
                cin >> phone_new;
                customermanager.editNameCustomer(databaseRoom, ID_current, phone_new);
                cout << "Change Phonenumber Successful !!!" << endl;
                cout << "1. Coutinue to Change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void Erasecustomer(vector<Room> databaseRoom, CustomerManager &customermanager)
{
    int key = 0;
    do
    {
        cout << "Enter current ID room: ";
        int ID_current;
        cin >> ID_current;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == ID_current)
            {
                cout << "Enter name Customer want to erase : ";
                string name;
                cin >> name;
                customermanager.eraseCustomer(databaseRoom, ID_current, name);
                cout << "Erase Customer Successful !!!" << endl;
                cout << "1. Coutinue to Erase : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void Displaycustomer(CustomerManager customermanager)
{
    if (!customermanager.getdatabaseCustomer().empty())
    {
        cout << "List customer " << endl;
        for (int i = 0; i < customermanager.getdatabaseCustomer().size(); i++)
        {
            cout << " ID ROOM ";
            cout << "     NAME";
            cout << "     PHONENUMBER      ";
            cout << "     ADDRESS";
            cout << endl;
            cout << "    " << customermanager.getdatabaseCustomer()[i].getidRoombooked();
            cout << "          " << customermanager.getdatabaseCustomer()[i].getname();
            cout << "         " << customermanager.getdatabaseCustomer()[i].getphonenumber();
            cout << "                   " << customermanager.getdatabaseCustomer()[i].getaddress();
            cout << endl;
        }
    }
    else
    {
        cout << "List customer are empty!!!" << endl;
    }
}
void setRoom(vector<Room> &databaseRoom, int number)
{
    for (int i = 0; i < number; i++)
    {
        Room room(i);
        databaseRoom.push_back(i);
    }
}

void reservationManager(vector<Room> &databaseRoom, CustomerManager &customerManager)
{
    int key = 0;
    do
    {

        printListroom(databaseRoom);
        cout << " Enter the ID of Room:  ";
        int id;
        cin >> id;
        for (int i = 0; i < databaseRoom.size(); i++)
        {
            if (databaseRoom[i].getID() == id)
            {
                databaseRoom[i].bookRoom();
                databaseRoom[i].checkIn();

                string name;
                string phonenumber;
                string address;

                cout << "Name:  ";
                cin >> name;

                cout << "Phone Number: ";
                cin >> phonenumber;

                cout << "Address: ";
                cin >> address;

                int second = 0;
                int minute = 0;
                int hour = 0;

                cout << "Second: ";
                cin >> second;
                cin.ignore();
                cout << "Minute: ";
                cin >> minute;
                cin.ignore();
                cout << "Hour: ";
                cin >> hour;
                cin.ignore();

                int day = 0;
                int month = 0;
                int year = 0;

                cout << "Day: ";
                cin >> day;
                cin.ignore();
                cout << "Month: ";
                cin >> month;
                cin.ignore();
                cout << "Year: ";
                cin >> year;
                cin.ignore();

                Customer customer(name, phonenumber, address, id);

                BookingHistory bookingData;
                bookingData.time = {second, minute, hour};
                bookingData.date = {day, month, year};
                bookingData.status = {IN};

                customer.AddBookingHistory(bookingData);
                customerManager.addCustomer(customer);
                cout << "Booking Successful !!!" << endl;
                cout << "1. Coutinue to booking : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void DisplayEmployee(EmployeeManager employeemanager)
{
    if (!employeemanager.getdatabaseEmployee().empty())
    {
        cout << "List employee " << endl;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
        {
            cout << " ID   ";
            cout << "     NAME";
            cout << "     PHONENUMBER      ";
            cout << "     ADDRESS";
            cout << "      JOBPOSITON";
            cout << endl;
            cout << " " << employeemanager.getdatabaseEmployee()[i].getid();
            cout << "       " << employeemanager.getdatabaseEmployee()[i].getname();
            cout << "         " << employeemanager.getdatabaseEmployee()[i].getPhonenumber();
            cout << "                      " << employeemanager.getdatabaseEmployee()[i].getaddress();
            cout << "             " << employeemanager.getdatabaseEmployee()[i].getjobposition();
            cout << endl;
        }
    }
    else
    {
        cout << "List employee are empty!!!" << endl;
    }
    cout << "1. JANITOR\n2. RECEPTIONIST\n3. LAUNDRY_STAFF\n4. LAUGGAGE_STAFF\n5. GRADENER \n";
}
void addEmployee(EmployeeManager &employeemanager)
{
    int k = 0;
    do
    {
        string name;
        string phonenumber;
        string address;

        cout << "Name:  ";
        cin >> name;

        cout << "Phone Number: ";
        cin >> phonenumber;

        cout << "Address: ";
        cin >> address;

        JobPosition jobposition;
        cout << "Choose postion of employee!!!" << endl;
        cout << "1. JANITOR\n2. RECEPTIONIST\n3. LAUNDRY_STAFF\n4. LAUGGAGE_STAFF\n5. GRADENER \n";
        cout << "Select key: ";
        int key = 0;
        cin >> key;
        switch (key)
        {
        case 1:
            jobposition = JANITOR;
            break;
        case 2:
            jobposition = RECEPTIONIST;
            break;
        case 3:
            jobposition = LAUNDRY_STAFF;
            break;
        case 4:
            jobposition = LAUGGAGE_STAFF;
            break;
        case 5:
            jobposition = GRADENER;
        default:
            cout << " WARNING, AGAIN!!!" << endl;
            break;
        }

        int day = 0;
        int month = 0;
        int year = 0;

        cout << "Day: ";
        cin >> day;
        cin.ignore();
        cout << "Month: ";
        cin >> month;
        cin.ignore();
        cout << "Year: ";
        cin >> year;
        cin.ignore();
        Schedule schedule;
        schedule.date = {day, month, year};

        int second = 0;
        int minute = 0;
        int hour = 0;

        cout << "Second: ";
        cin >> second;
        cin.ignore();
        cout << "Minute: ";
        cin >> minute;
        cin.ignore();
        cout << "Hour: ";
        cin >> hour;
        cin.ignore();

        schedule.time = {second, minute, hour};
        schedule.Status = {IN};
        static int id = 100;

        Employee employee(name, phonenumber, address, id, schedule, jobposition);
        id++;
        employeemanager.addEmployee(employee);
        cout << "Adding Employee Successful !!!" << endl;
        cout << "1. Coutinue to add : \n0. Exit" << endl;
        cout << "Select key: ";
        cin >> k;

    } while (k != 0);
}
void Editname(EmployeeManager &employeemanager)
{
    DisplayEmployee(employeemanager);
    int key = 0;
    do
    {
        cout << "Enter ID of employee to change name: ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                cout << "Enter new name: ";
                string name_new;
                cin >> name_new;
                employeemanager.EditnameEmployee(id, name_new);
                cout << "Edit name Eployee Successful !!!" << endl;
                cout << "1. Coutinue to add : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}

void EditPhone(EmployeeManager &employeemanager)
{
    DisplayEmployee(employeemanager);
    int key = 0;
    do
    {
        cout << "Enter ID of employee to change Phonenumber: ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                cout << "Enter new PhoneNumber: ";
                string phone_new;
                cin >> phone_new;
                employeemanager.EditPhonenumberEmployee(id, phone_new);
                cout << "Edit PhoneNumber Eployee Successful !!!" << endl;
                cout << "1. Coutinue to edit : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}

void EditADD(EmployeeManager &employeemanager)
{
    DisplayEmployee(employeemanager);
    int key = 0;
    do
    {
        cout << "Enter ID of employee to change Address: ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                cout << "Enter new Address: ";
                string add_new;
                cin >> add_new;
                employeemanager.EditAddressEmployee(id, add_new);
                cout << "Edit Address Eployee Successful !!!" << endl;
                cout << "1. Coutinue to edit : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}

void EditSchedule(EmployeeManager &employeemanager)
{
    int key = 0;
    do
    {
        cout << "Enter ID of employee to change Schedule: ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                DisplaySchedule(employeemanager, id);
                cout << "Enter new Schedule!!!" << endl;
                int day_new = 0;
                int month_new = 0;
                int year_new = 0;

                cout << "Day: ";
                cin >> day_new;
                cin.ignore();
                cout << "Month: ";
                cin >> month_new;
                cin.ignore();
                cout << "Year: ";
                cin >> year_new;
                cin.ignore();
                Schedule schedule_new;
                schedule_new.date = {day_new, month_new, year_new};

                int second_new = 0;
                int minute_new = 0;
                int hour_new = 0;

                cout << "Second: ";
                cin >> second_new;
                cin.ignore();
                cout << "Minute: ";
                cin >> minute_new;
                cin.ignore();
                cout << "Hour: ";
                cin >> hour_new;
                cin.ignore();

                schedule_new.time = {second_new, minute_new, hour_new};
                schedule_new.Status = {IN};
                employeemanager.EditShedule(id, schedule_new);
                cout << "Edit Schedule Eployee Successful !!!" << endl;
                cout << "1. Coutinue to edit : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}
void EditJobposition(EmployeeManager &employeemanager)
{
    DisplayEmployee(employeemanager);
    int key = 0;
    do
    {
        cout << "Enter ID of employee to change Jobposition: ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                JobPosition jobposition_new;
                cout << "Choose new postion of employee!!!" << endl;
                cout << "1. JANITOR\n2. RECEPTIONIST\n3. LAUNDRY_STAFF\n4. LAUGGAGE_STAFF\n5. GRADENER \n";
                cout << "Select key: ";
                int k = 0;
                cin >> k;
                switch (k)
                {
                case 1:
                    jobposition_new = JANITOR;
                    break;
                case 2:
                    jobposition_new = RECEPTIONIST;
                    break;
                case 3:
                    jobposition_new = LAUNDRY_STAFF;
                    break;
                case 4:
                    jobposition_new = LAUGGAGE_STAFF;
                    break;
                case 5:
                    jobposition_new = GRADENER;
                default:
                    cout << " WARNING, AGAIN!!!" << endl;
                    break;
                }
                employeemanager.EditJobpositon(id, jobposition_new);
                cout << "Edit Jobposition Eployee Successful !!!" << endl;
                cout << "1. Coutinue to edit : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}
void EraseEmployee(EmployeeManager &employeemanager)
{
    DisplayEmployee(employeemanager);
    int key = 0;
    do
    {
        cout << "Enter ID of employee to Erase : ";
        int id = 0;
        cin >> id;
        for (int i = 0; i < employeemanager.getdatabaseEmployee().size(); i++)
            if (employeemanager.getdatabaseEmployee()[i].getid() == id)
            {
                employeemanager.EraseEmployee(id);
                cout << "Erase Eployee Successful !!!" << endl;
                cout << "1. Coutinue to edit : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}

void employeemanager_(EmployeeManager &employeemanager, SecurityManager &securitymanager)
{
    while (1)
    {
        int k;
        cout << "1. Manger\n2. Staff\n0. Exit" << endl;
        cout << "Select key: ";
        cin >> k;
        if (k == 1)
        {
            string user;
            string password;
            cout << "USERNAME: ";
            cin >> user;
            cout << "PASSWORD: ";
            cin >> password;
            bool check = securitymanager.getcheckAuthenticate(user, password);
            if (check == 0)
            {
                cout << "Wrong USERNAME or PASSWORD!!!" << endl;
                return;
            }
            else
            {
                cout << endl;
                cout << "1. ADD EMPLOYEE \n2. EDIT NAME EMPLOYEE\n3. EDIT PHONENUMBER EMPLOYEE\n4. EDIT ADDRESS EMPLOYEE\n5. EDIT SCHEDULE EMPLOYEE\n6. EDIT POSITION EMPLOYEE\n7. ERASE EMPLOYEE\n8. DISPLAY LIST EMPLOYEE\n0. EXIT" << endl;
                cout << "Select key: ";
                int key = 0;
                cin >> key;
                switch (key)
                {
                case 1:
                    addEmployee(employeemanager);
                    break;
                case 2:
                    Editname(employeemanager);
                    break;
                case 3:
                    EditPhone(employeemanager);
                    break;
                case 4:
                    EditADD(employeemanager);
                case 5:
                    EditSchedule(employeemanager);
                    break;
                case 6:
                    EditJobposition(employeemanager);
                    break;
                case 7:
                    EraseEmployee(employeemanager);
                    break;
                case 8:
                    DisplayEmployee(employeemanager);
                    break;
                case 0:
                    return;
                default:
                    cout << "WARNING!!!" << endl;
                    break;
                }
            }
        }
        else if (k == 2)
        {
            string username;
            string pass;
            int checkUser = 0;
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> pass;
            for (int i = 0; i < securitymanager.getdatabaseUser().size(); i++)
            {
                if (securitymanager.getdatabaseUser()[i].getusername() == username)
                {
                    checkUser++;
                    if (securitymanager.getdatabaseUser()[i].getpassword() == pass)
                        break;
                    else
                    {
                        cout << "Password is wrong!!!" << endl;
                        return;
                    }
                }
                if (checkUser == 0)
                {
                    cout << "Username is wrong" << endl;
                    return;
                }
            }
            cout << "1. EDIT PHONENUMBER EMPLOYEE\n2. EDIT ADDRESS EMPLOYEE\n0. EXIT" << endl;
            cout << "Select key: ";
            int key = 0;
            cin >> key;
            switch (key)
            {
            case 1:
                EditPhone(employeemanager);
                break;
            case 2:
                EditADD(employeemanager);
                break;
            case 0:
                return;
            default:
                cout << "WARNING!!!" << endl;
                break;
            }
        }
        else
            break;
    }
}

void customermanager_(vector<Room> databaseRoom, CustomerManager &customermanager)
{
    while (1)
    {
        cout << endl;
        cout << "1. EDIT ROOM CUSTOMER\n2. EDIT NAME CUSTOMER \n3. EDIT PHONENUMBER CUSTOMER\n4. EDIT ADDRESS CUSTOMER\n5. ERASE CUSTOMER \n6. DISPLAY LIST CUSTOMER\n0. EXIT" << endl;
        cout << "Select key: ";
        int key = 0;
        cin >> key;
        switch (key)
        {
        case 1:
            Editroom(databaseRoom, customermanager);
            break;
        case 2:
            EditName(databaseRoom, customermanager);
            break;
        case 3:
            Editphone(databaseRoom, customermanager);
            break;
        case 4:
            EditAddress(databaseRoom, customermanager);
        case 5:
            Erasecustomer(databaseRoom, customermanager);
            break;
        case 6:
            Displaycustomer(customermanager);
            break;
        case 0:
            return;
        default:
            cout << "WARNING!!!" << endl;
            break;
        }
    }
}

int pinRole()
{
    int key = 0;
    do
    {
        cout << "Select postion !!!\n***************\n"
             << "1: Reservation Manager\n2: Customer Mangaer\n3: Employee Manager\n4: Service Manager\n5: Payment Manager\n6: Security Manager\n0: Exit\n***************\n"
             << "Select key: ";

        cin >> key;
    } while (key != 1 && key != 2 && key != 3 && key != 4 && key != 6 && key != 5);
    return key;
}

void EditPasswordMangager(SecurityManager &securitymanager)
{
    string username;
    string password;
    int key = 0;
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSOWRD: ";
    cin >> password;
    bool check = securitymanager.getcheckAuthenticate(username, password);
    string password_new;
    string password_new_again;
    do
    {
        if (check == true)
        {
            while (1)
            {

                cout << "Enter new password: ";
                cin >> password_new;
                cout << "Verify new password: ";
                cin >> password_new_again;
                if (password_new == password_new_again)
                    break;
                else
                    cout << "\nRepeat password is wrong, enter again!!!";
            }
            securitymanager.setPasswordManager(password_new);
            cout << "Change Password Successful !!!" << endl;
            cout << "1. Coutinue to change : \n0. Exit" << endl;
            cout << "Select key: ";
            cin >> key;
        }
        else
        {
            cout << "WRONG ID OR PASSWORD !!!" << endl;
            return;
        }
    } while (key != 0);
}
void displayUser(SecurityManager securitymanager)
{
    cout << "List of user" << endl;
    for (int i = 0; i < securitymanager.getdatabaseUser().size(); i++)
    {
        cout << "STT: "
             << "  " << i << endl;
        cout << "USERNAME: "
             << "  " << securitymanager.getdatabaseUser()[i].getusername() << endl;
        cout << "PASSWORD: "
             << "  " << securitymanager.getdatabaseUser()[i].getpassword() << endl;
    }
}
void AddUser(SecurityManager &securitymanager)
{
    int key = 0;
    do
    {
        string username;
        string password;
        cout << "Enter user: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        User user(username, password);
        securitymanager.addUser(username, password);
        cout << "Add User Successful !!!" << endl;
        cout << "1. Coutinue to edit : \n0. Exit" << endl;
        cout << "Select key: ";
        cin >> key;
    } while (key != 0);
}
void EraseUser(SecurityManager &securitymanager)
{
    displayUser(securitymanager);
    int key = 0;
    do
    {
        cout << "Enter Username of User to Erase : ";
        string username;
        cin >> username;
        for (int i = 0; i < securitymanager.getdatabaseUser().size(); i++)
            if (securitymanager.getdatabaseUser()[i].getusername() == username)
            {
                securitymanager.eraseUser(username);
                cout << "Erase User Successful !!!" << endl;
                cout << "1. Coutinue to erase : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}

void AddSerive(ServiceManager &servicemanager)
{
    int key = 0;
    static int id = 100;
    do
    {
        string name;
        cout << "Enter name of the service: ";
        cin >> name;
        Service service(name, NOTSERVICED, id);
        servicemanager.addService(service);
        cout << "Add Service Successful !!!" << endl;
        cout << "1. Coutinue to add : \n0. Exit" << endl;
        cout << "Select key: ";
        cin >> key;
        id++;
    } while (key != 0);
}
void displayService(ServiceManager servicemanager)
{
    cout << "List Service!!!" << endl;
    for (int i = 0; i < servicemanager.getdatabaseServive().size(); i++)
    {
        cout << "ID: " << servicemanager.getdatabaseServive()[i].getID() << endl;
        cout << "Service: " << servicemanager.getdatabaseServive()[i].getNameService() << endl;
        cout << "Status: ";
        if (servicemanager.getdatabaseServive()[i].getstatus() == 0)
            cout << "SERVING" << endl;
        else
            cout << "NOTSERVIED" << endl;
    }
}
void EditStatusService(ServiceManager &servicemanager)
{
    displayService(servicemanager);
    int key = 0;
    do
    {
        int id;
        cout << "Enter ID of the service: ";
        cin >> id;
        for (int i = 0; i < servicemanager.getdatabaseServive().size(); i++)
        {
            if (servicemanager.getdatabaseServive()[i].getID() == id)
            {
                typeService status;
                int k;
                cout << "Select the status for the service!!!\n";
                cout << "1. SERVING\n0. NOTSERVICED\n";
                cout << "Select key: ";
                cin >> k;
                if (k = 1)
                    status = SERVING;
                else
                    status = NOTSERVICED;
                servicemanager.editStatusService(id, status);
                cout << "Change Status Successful !!!" << endl;
                cout << "1. Coutinue to change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
        }
    } while (key != 0);
}

void EraseService(ServiceManager &servicemanager)
{
    displayService(servicemanager);
    int key = 0;
    do
    {
        cout << "Enter ID Service want to Erase : ";
        int id;
        cin >> id;
        for (int i = 0; i < servicemanager.getdatabaseServive().size(); i++)
            if (servicemanager.getdatabaseServive()[i].getID() == id)
            {
                servicemanager.eraseService(id);
                cout << "Erase Service Successful !!!" << endl;
                cout << "1. Coutinue to erase : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}
void EditUserPassword(SecurityManager &securitymanager)
{
    displayUser(securitymanager);
    int key = 0;
    do
    {
        cout << "Enter Username of User to change password : ";
        string username;
        cin >> username;
        for (int i = 0; i < securitymanager.getdatabaseUser().size(); i++)
            if (securitymanager.getdatabaseUser()[i].getusername() == username)
            {
                string newpass;
                cout << "New password: ";
                cin >> newpass;
                securitymanager.editpasswordUser(username, newpass);
                cout << "Change password Successful !!!" << endl;
                cout << "1. Coutinue to change : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
            }
    } while (key != 0);
}
void SecurityManger_(SecurityManager &securitymanager)
{
    cout << " Enter Manager Account" << endl;
    string user;
    string pass;
    cout << "Enter Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    bool check = securitymanager.getcheckAuthenticate(user, pass);
    if (check == false)
    {
        cout << "USERNAME OR PASSWORD WRONG!!!" << endl;
        return;
    }
    else
    {
        while (1)
        {
            cout << endl;
            cout << "1. ADD USER\n2. EDIT USER PASSWORD \n3. ERASE USER \n4. EDIT MANAGER PASSWORD\n5. DISPLAY LIST USER\n0. EXIT" << endl;
            cout << "Select key: ";
            int key = 0;
            cin >> key;
            switch (key)
            {
            case 1:
                AddUser(securitymanager);
                break;
            case 2:
                EditUserPassword(securitymanager);
                break;
            case 3:
                EraseUser(securitymanager);
                break;
            case 4:
                EditPasswordMangager(securitymanager);
            case 5:
                displayUser(securitymanager);
                break;
                break;
            case 0:
                return;
            default:
                cout << "WARNING SELECT AGAIN !!!" << endl;
                break;
            }
        }
    }
}
void ServiceManager_(ServiceManager &servicemanager, SecurityManager &securitymanager)
{
    cout << " Enter Manager Account" << endl;
    string user;
    string pass;
    cout << "Enter Username: ";
    cin >> user;
    cout << "Enter Password: ";
    cin >> pass;
    bool check = securitymanager.getcheckAuthenticate(user, pass);
    if (check == false)
    {
        cout << "USERNAME OR PASSWORD WRONG!!!" << endl;
        return;
    }
    else
    {
        while (1)
        {
            cout << endl;
            cout << "1. ADD SERVICE\n2. EDIT STATUS SERVICE\n3. ERASE SERVICE\n4. DISPLAY LIST SERVICE\n0. EXIT" << endl;
            cout << "Select key: ";
            int key = 0;
            cin >> key;
            switch (key)
            {
            case 1:
                AddSerive(servicemanager);
                break;
            case 2:
                EditStatusService(servicemanager);
                break;
            case 3:
                EraseService(servicemanager);
                break;
            case 4:
                displayService(servicemanager);
                break;
            case 0:
                return;
            default:
                cout << "WARNING SELECT AGAIN !!!" << endl;
                break;
            }
        }
    }
}

void displaycheckout(Paymentmanager paymentmanager)
{
    cout << "List customer check out: " << endl;
    for (int i = 0; i < paymentmanager.getdatapayment().size(); i++)
    {
        cout << "STT: " << i << endl;
        cout << "ID room: " << paymentmanager.getdatapayment()[i].getIDroom() << endl;
        cout << "Name customer: " << paymentmanager.getdatapayment()[i].getnamecustomer() << endl;
        cout << "Phone customer: " << paymentmanager.getdatapayment()[i].getphonecustomer() << endl;
        cout << "Address customer: " << paymentmanager.getdatapayment()[i].getaddresscustomer() << endl;
        cout << "Payment: " << paymentmanager.getdatapayment()[i].getpayment() << " $" << endl;
        cout << "Date and time checkout" << endl;
        cout << "Date: " << paymentmanager.getdatapayment()[i].getdataCheckout()[i].date.day << "/" << paymentmanager.getdatapayment()[i].getdataCheckout()[i].date.month << "/" << paymentmanager.getdatapayment()[i].getdataCheckout()[i].date.year << endl;
        cout << "Time: " << paymentmanager.getdatapayment()[i].getdataCheckout()[i].time.hour << "h" << paymentmanager.getdatapayment()[i].getdataCheckout()[i].time.minute << "m" << paymentmanager.getdatapayment()[i].getdataCheckout()[i].time.second << "s" << endl;
        cout << "********************************" << endl;
    }
}

void Paymentmanager_(vector<Room> &databaseRoom, Paymentmanager &paymentmanager, CustomerManager customermanager)
{
    int x = 0;
    int k = 0;
    while (1)
    {
        cout << "1. PAYMENT CHECKOUT ROOM\n2. DISPLAY LIST CUSTOMER CHECKOUT\n0. EXIT\n";
        cout << "Select key: ";
        cin >> k;
        if (k == 1)
        {
            do
            {
                Displaycustomer(customermanager);
                cout << "Enter ID room want to payment: ";
                int id;
                cin >> id;
                string name;
                string address;
                string phonenumber;
                int pay = 0;
                int price = 10;

                int second = 0;
                int minute = 0;
                int hour = 0;
                cout << "Enter time checkout" << endl;
                cout << "Second: ";
                cin >> second;
                cin.ignore();
                cout << "Minute: ";
                cin >> minute;
                cin.ignore();
                cout << "Hour: ";
                cin >> hour;
                cin.ignore();

                int day = 0;
                int month = 0;
                int year = 0;

                cout << "Day: ";
                cin >> day;
                cin.ignore();
                cout << "Month: ";
                cin >> month;
                cin.ignore();
                cout << "Year: ";
                cin >> year;
                cin.ignore();

                BookingHistory datacheckout;
                datacheckout.time.minute = minute;
                datacheckout.time.second = second;
                datacheckout.time.hour = hour;

                datacheckout.date.year = year;
                datacheckout.date.month = month;
                datacheckout.date.day = day;
                datacheckout.status = {OUT};

                for (int i = 0; i < databaseRoom.size(); i++)
                {
                    if (databaseRoom[i].getID() == id)
                    {
                        databaseRoom[i].checkOut();
                    }
                }
                for (int a = 0; a < customermanager.getdatabaseCustomer().size(); a++)
                {
                    if (customermanager.getdatabaseCustomer()[a].getidRoombooked() == id)
                    {
                        pay = price * (day - customermanager.getdatabaseCustomer()[a].getbookinghistory()[a].date.day);
                        name = customermanager.getdatabaseCustomer()[a].getname();
                        phonenumber = customermanager.getdatabaseCustomer()[a].getphonenumber();
                        address = customermanager.getdatabaseCustomer()[a].getaddress();
                        cout << "Payment of room: " << id << " is " << pay << " $" << endl;
                    }
                }

                int key;

                cout << "Enter method to payment" << endl;
                cout << "1. CASH\n2. INTERNET BANKING\n3. CREDIT\n";
                cout << "Select key: ";
                cin >> key;
                typePaymentMethod method;
                if (key == 1)
                    method = CASH;
                else if (key == 2)
                    method = INTERNETBANKING;
                else
                    method == CREDIT;
                cout << "Payment success , please give us your rate and comment!!!" << endl;

                int k;

                cout << "Enter rate star" << endl;
                cout << "1. ONESTAR\n2. TWOSTAR\n3. THREESTAR\n4. FOURSTAR\n5. FIVESTAR\n0. ZERO\n";
                cout << "Select key: ";
                cin >> k;
                TypeRateStar rate;
                if (k == 1)
                    rate = ONE;
                else if (k == 2)
                    rate = TWO;
                else if (k == 3)
                    rate = THREE;
                else if (k == 4)
                    rate = FOUR;
                else if (k == 4)
                    rate = FIVE;
                else
                    rate = ZERO;

                string comment;
                cout << "Please enter your comment: ";
                cin >> comment;
                Payment payment(comment, method, rate, pay, id, name, phonenumber, address, price);
                payment.addDataCheckout(datacheckout);
                paymentmanager.addDatapayment(payment);
                cout << "Rate Successful !!!" << endl;
                cout << "1. Coutinue to payment : \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> x;
            } while (x != 0);
        }
        else if (k == 2)
            displaycheckout(paymentmanager);
        else
            break;
    }
}

int main()
{
    vector<Room> databaseRoom;
    CustomerManager customermanager;
    EmployeeManager employeemanager;
    SecurityManager securitymanager;
    ServiceManager servicemanager;
    Paymentmanager paymentmanager;

    setRoom(databaseRoom, 9);
    int check = 0;

    do
    {
        check = pinRole();
        if (check == 1)
            reservationManager(databaseRoom, customermanager);
        else if (check == 2)
            customermanager_(databaseRoom, customermanager);
        else if (check == 3)
            employeemanager_(employeemanager, securitymanager);
        else if (check == 4)
            ServiceManager_(servicemanager, securitymanager);
        else if (check == 6)
            SecurityManger_(securitymanager);
        else if (check == 5)
            Paymentmanager_(databaseRoom, paymentmanager, customermanager);
        else
            cout << "WARNING !!! Select again: " << endl;
    } while (1);

    return 0;
}
