#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// Observer interface
class IObserver {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~IObserver() = default;
};

// Subject interface
class ISubject {
public:
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(const std::string& message) = 0;
    virtual ~ISubject() = default;
};

// Concrete Subject (Observable)
class WeatherStation : public ISubject {
private:
    std::vector<IObserver*> observers;
    float temperature;
    float humidity;

public:
    void attach(IObserver* observer) override {
        observers.push_back(observer);
        std::cout << "Observer attached\n";
    }

    void detach(IObserver* observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
            std::cout << "Observer detached\n";
        }
    }

    void notify(const std::string& message) override {
        std::cout << "Notifying observers...\n";
        for (IObserver* observer : observers) {
            observer->update(message);
        }
    }

    // Business methods that will trigger notifications
    void setTemperature(float temp) {
        this->temperature = temp;
        std::string message = "Temperature updated to: " + std::to_string(temp);
        notify(message);
    }

    void setHumidity(float humid) {
        this->humidity = humid;
        std::string message = "Humidity updated to: " + std::to_string(humid);
        notify(message);
    }
};

// Concrete Observer 1
class PhoneDisplay : public IObserver {
private:
    std::string name;

public:
    PhoneDisplay(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Phone Display [" << name << "] received update: " << message << "\n";
    }
};

// Concrete Observer 2
class WindowDisplay : public IObserver {
private:
    std::string location;

public:
    WindowDisplay(const std::string& location) : location(location) {}

    void update(const std::string& message) override {
        std::cout << "Window Display at [" << location << "] received update: " << message << "\n";
    }
};

int main() {
    // Create subject
    WeatherStation weatherStation;

    // Create observers
    PhoneDisplay phone1("John's Phone");
    PhoneDisplay phone2("Mary's Phone");
    WindowDisplay window1("Living Room");

    // Register observers
    weatherStation.attach(&phone1);
    weatherStation.attach(&phone2);
    weatherStation.attach(&window1);

    // Change temperature - all observers will be notified
    std::cout << "\nChanging temperature:\n";
    weatherStation.setTemperature(25.5);

    // Detach one observer
    std::cout << "\nDetaching Mary's phone:\n";
    weatherStation.detach(&phone2);

    // Change humidity - remaining observers will be notified
    std::cout << "\nChanging humidity:\n";
    weatherStation.setHumidity(60.0);

    return 0;
}

