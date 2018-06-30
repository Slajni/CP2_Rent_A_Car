#include <iostream>
#include <vector>
#include <stdio.h>
#include <limits.h>

using namespace std;




class Car
{
    static int baseCarId;
    int carId;
    int yearOfProduction = 0;
    string brand = "";
    int costOfRent = 1000;
    bool rented = 0;

public:

    Car(int yearOfProduction, const string &brand, int costOfRent) : yearOfProduction(yearOfProduction), brand(brand),
                                                                     costOfRent(costOfRent)
    {
        carId = baseCarId;
        baseCarId++;
    }

    void printInfo() const
    {
        printf("\n Car of the brand %s made in year %d has the id %d and the cost of rent is %d\n", brand.c_str(),yearOfProduction, carId, costOfRent);
    }

    void changeCarRentedState()
    {
        rented = !rented;
    }
    bool isRented() const
    {
        return rented;
    }
    Car * returnAdress()
    {
        return this;
    }
    int returnPrice() const
    {
        return costOfRent;
    }
    int returnId() const
    {
        return carId;
    }

};

int Car::baseCarId = 0;

class Client
{
    static int baseClientId;
    int clientId;
    string name;
    string surname;
    int balance;
public:
    Client(const string &name, const string &surname, int balance) : name(name), surname(surname), balance(balance)
    {
        clientId = baseClientId;
        baseClientId++;
    }

    void printClientInfo() const
    {
        printf("\nClient %s %s of id: %d has the balance of %d\n", name.c_str(), surname.c_str(), clientId, balance);
    }
    int returnId() const
    {
        return clientId;
    }
    Client * returnAdress()
    {
        return this;
    }
    int returnBalance() const
    {
        return balance;
    }
    void takeMoney(int amount)
    {
        balance -= amount;
    }
    void addMoney(int amount)
    {
        balance += amount;
    }
};

int Client::baseClientId = 0;

class Rent
{
public:
    int clientId;
    int carId;

    Rent(int clientId, int carId) : clientId(clientId), carId(carId)
    {}

};
class RentalCompany
{


    static vector <Client> clients;
    static vector <Car> cars;
    static vector <Rent> rents;

public:

    static void addCar(int yearOfProduction, const string & brand, int costOfRent)
    {
        cars.emplace_back(yearOfProduction, brand, costOfRent);
    }
    static void addClient(const string &name, const string &surname, int balance)
    {
        clients.emplace_back(name, surname, balance);
    }
    static void printAvaibleCars()
    {
        printf("Avaible Cars: \n");
        for(auto const &value: cars)
        {
            if(!value.isRented())
                value.printInfo();
        }
        printf("/////////////////////////\n");
    }
    static void printUnavaibleCars()
    {
        printf("Rented Cars: \n");
        for(auto const &value: cars)
        {
            if(value.isRented())
                value.printInfo();
        }
        printf("/////////////////////////\n");
    }
    static void printCars()
    {
        printf("List of cars:\n");
        for(auto const &value: cars)
            value.printInfo();
        printf("//////////////////////////\n");
    }
    static Client * returnClient(int id)
    {
        for(auto &value: clients)
            if(value.returnId()==id)
                return value.returnAdress();
    }
    static Car * returnCarPointer(int id)
    {
        for(auto &value: cars)
            return value.returnAdress();
    }
    static void printClients()
    {
        printf("\n LIST OF CLIENTS\n");
        for (auto const &value: clients)
        {
            value.printClientInfo();
        }
        printf("/////////////////////////\n");
    }
    static void rentACar(int clientId, int carId)
    {
        Car *carToBeRented = RentalCompany::returnCarPointer(carId);
        Client *personRentingCar = RentalCompany::returnClient(clientId);

        if(carToBeRented->returnPrice()<=personRentingCar->returnBalance() && !carToBeRented->isRented())
        {
            rents.emplace_back(clientId, carId);
            personRentingCar->takeMoney(carToBeRented->returnPrice());
            carToBeRented->changeCarRentedState();
        }
        else
        {
            printf("This client can't rent this car because it's too expensive\n");
        }
    }
    static void returnCar(int carId)
    {
        int i = 0;
        for(auto value: rents)
        {
            if(value.carId == carId)
            {
                Car *returnedCar = returnCarPointer(carId);
                returnedCar->changeCarRentedState();
                rents.erase(rents.begin() + i);
            }
            i++;
        }
    }
    static void deleteCar(int id)
    {
        int i = 0;
        for(auto const value: cars)
        {
            if(value.returnId() == id)
            {
                cars.erase(cars.begin() + i);
                return;
            }
            i++;
        }
        printf("\n There is no car of that id\n");
    }
    static void deleteClient(int id)
    {
        int i = 0;
        for(auto const value: clients)
        {
            if(value.returnId() == id)
            {
                clients.erase(clients.begin() + i);
                return;
            }
            i++;
        }
        printf("\nThere is no client of that id\n");
    }

    static bool checkIfClientExists(int id)
    {
        for(auto &value: clients)
        {
            if(value.returnId() == id)
                return true;
        }
        return false;
    }
    static bool checkIfCarExists(int id)
    {
        for(auto &value: cars)
        {
            if(value.returnId() == id)
                return true;
        }
        return false;
    }
    static void topUp(int clientId, int amount)
    {
        for (auto &value: clients)
        {
            if (value.returnId() == clientId)
            {
                value.addMoney(amount);
            }
        }
    }
};


vector <Client> RentalCompany::clients;
vector <Car> RentalCompany::cars;
vector <Rent> RentalCompany::rents;


void menu()
{

    printf("\n\nTHIS IS MENU WITH AVAIBLE CHOICES, WHAT DO YOU WANT TO DO?\n\n\n "
           "1. See the list of clients\n"
           "2. See the list of cars\n"
           "3. See the list of cars that can be rented\n"
           "4. Add a car\n"
           "5. Add a client\n"
           "6. Delete a car\n"
           "7. Delete a client\n"
           "8. Rent a Car for a client\n"
           "9. Return a car of given id\n"
           "10. Top up some clients account\n"
           "11. List rented cars\n"
           "12. Close program\n\n\n");
}

int main()
{

    while(true)
    {
        menu();
        int choice = 0;
        do
        {
            printf("Make a choice: ");
            cin >> choice;
            if(choice < 1 || choice > 12)
                cout << "There is no such option" << endl;
        } while (choice < 1 || choice > 12);

        switch (choice)
        {
            case 1:
            {
                RentalCompany::printClients();
                break;
            }
            case 2:
            {
                RentalCompany::printCars();
                break;
            }
            case 3:
            {
                RentalCompany::printAvaibleCars();
                break;
            }
            case 4:
            {
                string brandOfCar;
                int cost;
                int yearOfProdcution;
                cin.clear();
                cin.sync();
                cin.ignore(INT_MAX,'\n');
                printf("Put the name of car: ");
                getline(cin, brandOfCar);
                printf("Put the cost of rent: ");
                cin >> cost;
                printf("Put the year of production: ");
                cin >> yearOfProdcution;
                RentalCompany::addCar(yearOfProdcution, brandOfCar, cost);
                break;
            }
            case 5:
            {
                string name;
                string surname;
                int balance;
                printf("Put the name of client: ");
                cin >> name;
                printf("Put the surname of client: ");
                cin >> surname;
                printf("Put the balance of client: ");
                cin >> balance;
                RentalCompany::addClient(name, surname, balance);
                break;
            }
            case 6:
            {
                int id;
                printf("Choose id of car to be deleted: ");
                cin >> id;
                RentalCompany::deleteCar(id);
                break;
            }
            case 7:
            {
                int id;
                printf("Choose id of client to be deleted: ");
                cin >> id;
                RentalCompany::deleteClient(id);
                break;
            }
            case 8:
            {
                int clientId;
                int carId;
                printf("Choose client id: ");
                cin >> clientId;
                printf("Choose car id: ");
                cin >> carId;
                if(RentalCompany::checkIfCarExists(carId) && RentalCompany::checkIfClientExists(clientId))
                    RentalCompany::rentACar(clientId, carId);
                else
                    printf("\n There is no possible to do this because there is no such client or car in base\n");
                break;
            }
            case 9:
            {
                int carId;
                printf("Choose car id: ");
                cin >> carId;
                if (RentalCompany::checkIfCarExists(carId))
                    RentalCompany::returnCar(carId);
                else
                    printf("\nThere is no such car in base\n");
                break;
            }
            case 10:
            {
                int clientId;
                printf("Choose client id : ");
                cin >> clientId;
                if(RentalCompany::checkIfClientExists(clientId));
                {
                    int amount;
                    printf("Choose amount of money to top up clients account: ");
                    cin >> amount;
                    RentalCompany::topUp(clientId, amount);
                }
            }
            case 11:
            {
                RentalCompany::printUnavaibleCars();
            }
            case 12:
                return 0;

        }

    }

}