#include <iostream>

class Singleton
{
    private:
        static inline bool flag = false;
        static inline Singleton* sing = nullptr;
        Singleton(){}
    public:
        void method();
        static Singleton* getInstance();
        Singleton(const Singleton& ) = delete;
        Singleton& operator=(const Singleton&) = delete;
        ~Singleton(){
            flag = false;
        }
};

Singleton* Singleton::getInstance(){
    if(!flag){
        std::cout<<"instance created\n";
        sing = new Singleton;
        flag = true;
    }
    return sing;
}
void Singleton::method(){
    std::cout<<"methods called \n";
}

int main() {
   
    Singleton* src1 = Singleton::getInstance();
    src1->method();
    Singleton* src2 = src1;
    return 0;
}
