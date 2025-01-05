//Singleton Design Pattern has two charctristic:
//1] only one instance
//2]global object accessible anywhere
//other Design Pattern provied flexible and extensible where are other DP dont provide it .
//lazy initilazation
//eg: random generation data

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
=========================================
    Thread-Safe Singleton using mutex:

cppCopy#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    Singleton() {}
    
public:
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
=====================================================
    Double-Checked Locking Pattern:

cppCopy#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    Singleton() {}
    
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
=================================================
    #include <iostream>

class Singleton {
private:
    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

public:
    // Public static method to access the instance
    static Singleton& getInstance() {
        static Singleton instance; // Thread-safe and created only once
        return instance;
    }

    // Deleted copy constructor and assignment operators to prevent duplication
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    // Example method for demonstration
    void doSomething() {
        std::cout << "Doing something with the Singleton instance.\n";
    }
};

int main() {
    // Accessing the singleton instance
    Singleton& instance1 = Singleton::getInstance();
    instance1.doSomething();

    // Accessing again to demonstrate it’s the same instance
    Singleton& instance2 = Singleton::getInstance();
    instance2.doSomething();

    // Uncommenting any of the following lines will cause compilation errors:
    // Singleton anotherInstance;                  // Constructor is private
    // Singleton copyInstance = instance1;        // Copy constructor is deleted
    // Singleton movedInstance = std::move(instance1); // Move constructor is deleted

    return 0;
}
#########################IMP###################################
#include <iostream>

class Singleton {
private:
    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

public:
    // Public static method to access the instance
    static Singleton* getInstance() {
        static Singleton instance; // Local static variable ensures thread-safe lazy initialization
        return &instance; // Return the address of the local static instance
    }

    // Deleted copy constructor and assignment operators to prevent duplication
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    // Example method for demonstration
    void doSomething() {
        std::cout << "Doing something with the Singleton instance.\n";
    }

    // Destructor
    ~Singleton() {
        std::cout << "Singleton instance destroyed.\n";
    }
};

int main() {
    // Accessing the singleton instance
    Singleton* instance1 = Singleton::getInstance();
    instance1->doSomething();

    // Accessing again to demonstrate it’s the same instance
    Singleton* instance2 = Singleton::getInstance();
    instance2->doSomething();

    return 0;
}

/*Why is Meyer's Singleton thread-safe?

Static Local Variable Initialization:

C++11 standard guarantees that static local variable initialization is thread-safe
The compiler automatically generates thread-safe initialization code
Only one thread will initialize the instance, others will wait


Zero-Initialization:

Static local variables are zero-initialized before any dynamic initialization
This prevents problems with partially constructed objects


Construction Guarantee:

If multiple threads call getInstance() simultaneously:
Only one thread will construct the instance
Other threads will wait until construction is complete
No need for explicit locks or double-checking


Prevention of Multiple Instances:

Copy constructor is deleted (can't copy the instance)
Move constructor is deleted (can't move the instance)
Assignment operators are deleted (can't assign to instance)*/
================================
    #include <iostream>
#include <memory>
#include <mutex>

class Singleton {
private:
    static std::shared_ptr<Singleton> instance;
    static std::mutex mutex;

    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

public:
    // Public method to access the singleton instance
    static std::shared_ptr<Singleton> getInstance() {
        std::lock_guard<std::mutex> lock(mutex); // Thread-safe access
        if (instance == nullptr) {
            instance = std::shared_ptr<Singleton>(new Singleton());
        }
        return instance;
    }

    // Example method for demonstration
    void doSomething() {
        std::cout << "Doing something with the Singleton instance.\n";
    }
};

// Static member initialization
std::shared_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mutex;

// Main function to demonstrate usage
int main() {
    // Get the singleton instance and use it
    std::shared_ptr<Singleton> instance1 = Singleton::getInstance();
    instance1->doSomething();

    // Get the singleton instance again
    std::shared_ptr<Singleton> instance2 = Singleton::getInstance();
    instance2->doSomething();

    // Check if both instances are the same
    if (instance1 == instance2) {
        std::cout << "Both instances are the same.\n";
    }

    return 0;
}
==============================
    #include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class Singleton {
private:
   static Singleton* instance;
   static std::mutex mutex;
   
   // Member variable for demonstration
   int value;
   
   // Private constructor
   Singleton() : value(0) {
       std::cout << "Constructor called from thread: " 
                 << std::this_thread::get_id() << std::endl;
   }
   
public:
   static Singleton* getInstance() {
       std::lock_guard<std::mutex> lock(mutex);
       if (instance == nullptr) {
           instance = new Singleton();
       }
       return instance;
   }
   
   void setValue(int val) {
       value = val;
       std::cout << "Value set to " << value << " from thread: " 
                 << std::this_thread::get_id() << std::endl;
   }
   
   int getValue() const {
       return value;
   }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

// Thread function to test singleton
void threadFunction(int threadNum) {
   std::cout << "Thread " << threadNum << " with ID: " 
             << std::this_thread::get_id() << " started\n";
             
   // Get singleton instance
   Singleton* singleton = Singleton::getInstance();
   
   // Set value
   singleton->setValue(threadNum);
   
   // Simulate some work
   std::this_thread::sleep_for(std::chrono::milliseconds(100));
   
   // Read value
   std::cout << "Thread " << threadNum << " reads value: " 
             << singleton->getValue() << std::endl;
}

int main() {
   std::cout << "Testing thread-safe Singleton with mutex\n\n";
   
   // Create multiple threads
   std::thread t1(threadFunction, 1);
   std::thread t2(threadFunction, 2);
   std::thread t3(threadFunction, 3);
   
   // Wait for threads to complete
   t1.join();
   t2.join();
   t3.join();
   
   // Access singleton from main thread
   Singleton* mainSingleton = Singleton::getInstance();
   std::cout << "\nFinal value in main thread: " 
             << mainSingleton->getValue() << std::endl;
             
   return 0;
}

