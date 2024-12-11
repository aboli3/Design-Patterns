
#include <iostream>
#include <memory>
#include <string>

// Abstract State Class
class TrafficLightState {
public:
    virtual ~TrafficLightState() = default;

    // Define virtual methods for state transitions
    virtual void handleRequest() = 0;
    virtual std::string getStateName() const = 0;
};

// Concrete States
class RedState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Switching from Red to Green.\n";
    }

    std::string getStateName() const override {
        return "Red";
    }
};

class GreenState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Switching from Green to Yellow.\n";
    }

    std::string getStateName() const override {
        return "Green";
    }
};

class YellowState : public TrafficLightState {
public:
    void handleRequest() override {
        std::cout << "Switching from Yellow to Red.\n";
    }

    std::string getStateName() const override {
        return "Yellow";
    }
};

// Context Class
class TrafficLight {
private:
    std::shared_ptr<TrafficLightState> state;

public:
    TrafficLight(std::shared_ptr<TrafficLightState> initialState)
        : state(std::move(initialState)) {}

    void setState(std::shared_ptr<TrafficLightState> newState) {
        state = std::move(newState);
    }

    void handleRequest() {
        state->handleRequest();
    }

    void displayState() const {
        std::cout << "Current State: " << state->getStateName() << "\n";
    }
};

int main() {
    // Initialize the traffic light in Red state
    auto redState = std::make_shared<RedState>();
    auto greenState = std::make_shared<GreenState>();
    auto yellowState = std::make_shared<YellowState>();

    TrafficLight trafficLight(redState);

    // Simulate state transitions
    trafficLight.displayState();
    trafficLight.handleRequest();
    trafficLight.setState(greenState);

    trafficLight.displayState();
    trafficLight.handleRequest();
    trafficLight.setState(yellowState);

    trafficLight.displayState();
    trafficLight.handleRequest();
    trafficLight.setState(redState);

    trafficLight.displayState();

    return 0;
}
