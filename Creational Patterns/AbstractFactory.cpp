
#include <iostream>
#include <cstring>
#include <string.h>

//Abstract factory Method
//abstrcat factor when we want multiple different object at same time eg Car plant
//as in it GasCar will be differnt and ElectricalCar will be differnt.

class Door
{
    public:
        Door(){}
        virtual void open() = 0;
};
class GasDoor : public Door
{
    public:
        GasDoor():Door(){}
        void open(){
            std::cout<<"Gas Door \n";
        }
};
class EleDoor : public Door
{
    public:
        EleDoor():Door(){}
        void open(){
            std::cout<<"Electrical Door \n";
        }
};
///////////////////////////////////////////////////////////////////
class Enginee
{
    public:
        Enginee(){}
        virtual void Run() = 0;
};
class GasEnginee : public Enginee
{
    public:
        GasEnginee():Enginee(){}
        void Run(){
            std::cout<<"Run gas enginee\n";
        }
};
class ElecEnginee :public Enginee
{
    public:
        ElecEnginee():Enginee(){}
        void Run(){
            std::cout<<"Run Elect enginee\n";
        }
};
///////////////////////////////////////////////////////////////////////
class CarFactory
{
    public:
        CarFactory(){}
        virtual Door* BuildDoor() = 0;
        virtual Enginee* BuildEnginee() = 0;
};
class GasCarFactory: public CarFactory
{
    public:
        GasCarFactory():CarFactory(){}
        Door* BuildDoor(){
            return new GasDoor;
        }
        Enginee* BuildEnginee(){
            return new GasEnginee;
        }
};
class EleCarFactory: public CarFactory
{
    public:
        EleCarFactory():CarFactory(){}
        Door* BuildDoor(){
            return new EleDoor;
        }
        Enginee* BuildEnginee(){
            return new ElecEnginee;
        }
};
int main()
{
    CarFactory* carplant;
    size_t in;
    std::cout<<"Enter gas or eng\n";
    std::cin>>in;
    switch(in)
    {
        case 1: carplant = new GasCarFactory;
                break;
        case 2: carplant = new EleCarFactory;
                break;
        default: carplant = nullptr;
                break;
    }
    if(carplant!=nullptr){
        Door* door = carplant->BuildDoor();
        Enginee* enginee = carplant->BuildEnginee();
        door->open();
        enginee->Run();
    }
    return 0;
}
