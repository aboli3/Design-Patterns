
// Factory Method is creational DP , object is created at run time
#include <iostream>
#include <cstring>
#include <string.h>

class Coffee
{
    public:
        Coffee(){}
        char* getType(){
            return _type;
        }
    protected:
        char _type[15];
};
class Expresso:public Coffee
{
    public:
        Expresso():Coffee(){
            strcpy(_type, "Expresso");
            std::cout<<"Expresso coffee !\n";
        }
};
class Capption:public Coffee
{
    public:
        Capption():Coffee(){
            strcpy(_type, "Capption");
            std::cout<<"Capption coffee !\n";
        }
};

class FactorMethodClas{
    public:
        Coffee* getCoffeeType(){
            size_t choice;
            std::cout<<"enter choice :\n";
            std::cin>>choice;
            
            switch(choice)
            {
                case 1:
                    return new Expresso;
                case 2:
                    return new Capption;
                default:
                    return nullptr;
            }
        }
    private:
        Coffee* coffee;
};
int main()
{
    FactorMethodClas fmc;
    Coffee* cup;
    cup = fmc.getCoffeeType();
    std::cout<<cup->getType();
    return 0;
}
