#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

typedef enum
{
    SETTABLE = 1,
    ADD = 2,
    EDIT = 3,
    EREASE = 4,
    PRINT = 5,
    COMEBACK = 0
} Function;

typedef enum{
    ADDS = 1,
    EDITS =2,
    EREASES= 3,
    PRINTS = 4,
    PAYMENTS = 5,
    COMEBACKS = 0
}Funcitons;

class Food
{
protected:
    string name;
    int price;
    int ID;

public:
    int getID();
    string getname();
    int getprice();
    void setprice(int price);
    void setID(int id);
    void setname(string name);
    Food(string name_ = " ", int price_ = 0, int id = 0);
};
void Food::setID(int id){
    ID = id;
}
int Food::getID()
{
    return ID;
}
string Food ::getname()
{
    return name;
}

int Food ::getprice()
{
    return price;
}

void Food ::setprice(int price_)
{
    price = price_;
}
void Food::setname(string name_)
{
    name = name_;
}
Food::Food(string name_, int price_, int id)
{
    ID = id;
    name = name_;
    price = price_;
}

class Infortable : public Food
{
private:
    int quantity;

public:
    int getquantity();
    void setnquantity(int quantity_);
    Infortable(int quantity_ = 0);
};
Infortable ::Infortable(int quantity_)
{
    quantity = quantity_;
}
int Infortable ::getquantity()
{
    return quantity;
}

void Infortable ::setnquantity(int quantity_)
{
    quantity = quantity_;
}

class Table
{
private:
    int STT;
    bool status;
    // vector <Infortable>  databaseInfortable;
public:
    int getSTT();
    bool getstatus();
    void setstatus(bool status_);
    vector<Infortable> databaseInfortable;
    Table(int STT_, bool status_);
    // vector <Infortable> getdatabaseInfortable();
    // void setdatabaseInfortable(vector <Infortable>  databaseInfortable_);
};

int Table ::getSTT()
{
    return STT;
}

bool Table ::getstatus()
{
    return status;
}

void Table ::setstatus(bool status_)
{
    status = status_;
}

Table::Table(int STT_, bool status_)
{
    STT = STT_;
    status = status_;
}

void addFood(list<Food> &databaseFood)
{
    int key;
    do
    {
        cout << "Name: ";
        string name;
        cin >> name;
        cout << "Price: ";
        int price;
        cin >> price;
        static int id = 100;
        Food food(name, price, id);
        databaseFood.push_back(food);
        cout << " added dishes " << endl;
        cout << "    ID   "
             << "   NAME   "
             << "PRICE" << endl;
        cout << "   " << id << "       " << name << "    " << price << endl;
        cout << "------------------------------------" << endl;

        cout << "1. Coutinue to add dishes\n0. Exit" << endl;
        cout << "Select key: ";
        id++;
        cin >> key;
    } while (key != 0 );
}
void MenuFood(list<Food> databaseFood)
{
    list<Food>::iterator it;
    for (it = databaseFood.begin(); it != databaseFood.end(); it++)
    {
        cout << "MENU: " << endl;
        cout << "    ID   "
             << "   NAME   "
             << "PRICE" << endl;
        cout << "   " << (*it).getID() << "       " << (*it).getname() << "    " << (*it).getprice() << endl;
        cout << "------------------------------------" << endl;
    }
}
void EditFood(list<Food> &databaseFood)
{   bool check = 1;
    int key,k,h;
    list<Food>::iterator it;
    MenuFood(databaseFood);
    do
    {   again:
        int id;
        cout << " ID of dish: ";
        cin >> id;
        for (it = databaseFood.begin(); it != databaseFood.end(); it++)
        {
            if ((*it).getID() == id)
            {   check = 0;
                cout << "    ID   "
                     << "   NAME   "
                     << "PRICE" << endl;
                cout << "   " << (*it).getID() << "       " << (*it).getname() << "    " << (*it).getprice() << endl;
            
                cout << "1. Change price: \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
                if (key == 1) 
                {
                    cout << " New price: ";
                    int newprice;
                    cin >> newprice;
                    (*it).setprice(newprice);
                    cout << "Changed the price !!!" << endl;
                    cout << "1. Coutinue to Change price: \n0. Exit"<< endl;
                    cout << "Select key: ";
                    cin >> k;
                }
            }
        }if(check){
                cout << "Can't find ID" << endl;
            }
    }while (k != 0);
}
void EraseFood(list<Food> &databaseFood){
    int key,k;
    bool check = 1;
    list<Food>::iterator it;
    list <Food> :: iterator temp;
    MenuFood(databaseFood);
    do
    {
        int id;
        cout << " ID of dish: ";
        cin >> id;
        for (it = databaseFood.begin(); it != databaseFood.end(); it++)
        {
            if ((*it).getID() == id)
            {   
                temp = it;
                check = 0;
                cout << "    ID   "
                     << "   NAME   "
                     << "PRICE" << endl;
                cout << "   " << (*it).getID() << "       " << (*it).getname() << "    " << (*it).getprice() << endl;
                
            }
        }if (check) {
                cout << "Can't find ID" << endl;
            }else{
                    cout << "1. Erase dish: \n0. Exit" << endl;
                    cout << "Select key: ";
                    cin >> key;
                    databaseFood.erase(temp);
                    cout << "Erased the dish !!!" << endl;
                    cout << "1. Coutinue to erase dish: \n0. Exit"<< endl;
                    cout << "Select key: ";
                    cin >> k;
            }
    }while (k != 0);
}

void setTablenumber(vector<Table> &databaseTable)
{   
    cout << "The number of Table : " ;
    int number;
    cin >> number;
    bool status = 0;
    int STT = 1;
    for (int i = 1; i <= number; i++)
    {
        Table table(STT, status);
        STT++;
        databaseTable.push_back(table);
    } cout << "Created tables" << endl;
}
void addFoodtotheTable(list<Food> databaseFood, vector<Table> &databaseTable)
{
    int key,k;
    bool check = 0;
    list<Food>::iterator it;
    do{
        int stt;
        cout << "Add food to table: ";
        cin >> stt;
        stt = stt -1 ;
        int id;
        cout << " ID of dish: ";
        cin >> id;
        for (it = databaseFood.begin(); it != databaseFood.end(); it++)
    {
        if ((*it).getID() == id)
        {   
            check = 0;
            cout << "Number of dish: " ;
            int number;
            cin >> number;
            Infortable Infor(number);
            Infor.setID((*it).getID());
            Infor.setname((*it).getname());
            Infor.setprice((*it).getprice());
            databaseTable[stt].databaseInfortable.push_back(Infor);
            databaseTable[stt].setstatus(1);     
            }
        }cout << "1. Coutinue to add food to the table: \n0. Exit"<< endl;
            cout << "Select key: ";
            cin >> key;
    }while (key != 0);
    }
    


void displayFoodontheTable(vector<Table> databaseTable){
    cout << "Number of the table: ";
    int stt;
    cin >> stt;
    stt = stt - 1;
    for (int i = 0; i < databaseTable[stt].databaseInfortable.size();i++){
        cout << "    ID   "
                     << "   NAME   "
                     << " PRICE " 
                     << "    QUANTITY" << endl;
        cout << "   " << databaseTable[stt].databaseInfortable[i].getID() << "       " << databaseTable[stt].databaseInfortable[i].getname() << "    " << databaseTable[stt].databaseInfortable[i].getprice() << "            " << databaseTable[stt].databaseInfortable[i].getquantity() << endl;

    }
}
void payment(vector<Table> &databaseTable)
{   cout << "Number of the table: ";
    int stt;
    cin >> stt;
    stt = stt -1 ;

    int payment = 0;
    for (int i = 0; i < databaseTable[stt].databaseInfortable.size(); i++)
    {
        payment += databaseTable[stt].databaseInfortable[i].getprice() * databaseTable[stt].databaseInfortable[i].getquantity();
    }
    cout << "payment amount: " << payment << endl;
    databaseTable[stt].databaseInfortable.clear();
    databaseTable[stt].setstatus(0);
    cout << "Thank you !!!" << endl;
}
void PrintTable(vector<Table> databaseTable){
    if (!databaseTable.empty()){
        cout << "   Table list     " ;
        cout << "                   Status        " << endl;
    for ( int i = 0 ; i < databaseTable.size() ; i++){
        cout << "     " << databaseTable[i].getSTT() << "     ";
        if (databaseTable[i].getstatus() == 0){
        cout << "                           O";
             }
            else {
        cout << "                           X" ;
            }
            cout << endl;
        } 
    }else {
            cout << "Table list is empty" << endl;
        }
    }

int pinRole()
{
    int key = 0;
    do
    {
        cout << "Select postion !!!\n***************\n"
             << "1: Manager\n2: Staff\n0: Exit\n***************\n"
             << "Select key: ";

        cin >> key;
    } while (key != 1 && key != 2);
    return key;
}
void Manager(list<Food> &databaseFood, vector<Table> &databaseTable)
{
    while (1)
    {
        cout << "Choice!!! \n***************\n"
             << "1. Set Table:\n2. Add Food to menu: \n3. Edit Food from menu: \n4. Erase Food form menu:\n5. Print menu: \n0. Exit:\n***************\n"
             << "Select key: ";
        int key;
        cin >> key;
        switch (key)
        {
        case ADD:
            addFood(databaseFood);
            break;
        case EDIT:
            EditFood(databaseFood);
            break;
        case EREASE:
            EraseFood(databaseFood);
            break;
        case SETTABLE:
            setTablenumber(databaseTable);
            break;
        case PRINT:
            MenuFood(databaseFood);
            break;
        case COMEBACK:
            return;
        default:
            cout << "Warning. Again\n";
            break;
        }
    };
}
void EditFoodfromTable( vector<Table> &databaseTable){
    int key,k;
    do{
        int stt;
        cout << "Number of the Table:  ";
        cin >> stt;
        stt = stt - 1 ;
        int id;
        cout << "ID of dish: ";
        cin >> id;
        for  (int i = 0; i < databaseTable[stt].databaseInfortable.size();i++)
    {
        if (databaseTable[stt].databaseInfortable[i].getID() == id)
        {   
                cout << "1. Change the quantity: \n0. Exit" << endl;
                cout << "Select key: ";
                cin >> key;
                if (key  == 1 )
                {
                cout << " New quantity: ";
                int quantity;
                cin >> quantity;
                databaseTable[stt].databaseInfortable[i].setnquantity(quantity);
                cout << "Changed quantity: " << endl;
                cout << "1.Continue Change the quantity: \n0. Exit" << endl;
                cout << "Select key: ";
                cin >>k;
                }
            }
        }
    }while (k != 0);
}
void EraseFoodfromTable(vector<Table> &databaseTable){
    int key,k;
    do{
        int stt;
        cout << "Number of the Table:  ";
        cin >> stt;
        stt = stt -1 ;
        int id;
        cout << "ID of dish want to erase: ";
        cin >> id;
        for  (int i = 0; i < databaseTable[stt].databaseInfortable.size();i++)
    {
        if (databaseTable[stt].databaseInfortable[i].getID() == id)
        {   
                databaseTable[stt].databaseInfortable[i].setname(" ");
                databaseTable[stt].databaseInfortable[i].setID(0);
                databaseTable[stt].databaseInfortable[i].setprice(0);
                databaseTable[stt].databaseInfortable[i].setnquantity(0);
                cout << "Erased quantity: " << endl;
                cout << "1.Continue Earase dish: \n0. Exit" << endl;
                cout << "Select key: ";
                cin >>k;
                }
            }
        
    }while (k != 0);


}
void Staff(list<Food> &databaseFood, vector<Table> &databaseTable){
    while (1){
         cout << "Choice!!! \n***************\n"
             << "1. Add Food to the Table:\n2. Edit Food from the Table: \n3. Erase Food from the Table: \n4. List food on the table:\n5. Payment: \n0. Exit:\n***************\n"
             << "Select key: ";
        int key;
        cin >> key;
        switch (key){
            case ADDS:
            PrintTable(databaseTable);
            MenuFood(databaseFood);
            addFoodtotheTable (databaseFood,  databaseTable);
            break;
            case EDITS:
            displayFoodontheTable(databaseTable);
            EditFoodfromTable(databaseTable);
            break;
            case EREASES:
            displayFoodontheTable(databaseTable);
            EraseFoodfromTable(databaseTable); 
            break;
            case PRINTS:
            displayFoodontheTable(databaseTable);
            break;
            case PAYMENTS:
            payment(databaseTable);
            PrintTable(databaseTable);
            break;
            case COMEBACKS:
            return;
            default:
            cout << "Warning. Again\n";
            break;

        }
    }
}
int main()
{
    list<Food> database_Food;
    vector<Table> database_Table;
    int check;
    do
    {
         check = pinRole();
        if (check == 1)
            Manager(database_Food, database_Table);
         else if(check == 2 ) Staff (database_Food, database_Table);
         else cout << " WARNING !!! Select again:  " << endl;
    } while (1);
    
}