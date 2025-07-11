#include<iostream>
#include<string>

using namespace std;
//Real life car

class car{
    public:
    virtual void startEngine() = 0; // pure virtual function
    virtual void shiftgear(int gear) = 0; // pure virtual function     
    virtual void accelerate() = 0; // pure virtual function
              virtual void brake() = 0; // pure virtual function
    virtual void stopEngine() = 0; // pure virtual function
    virtual ~car() {} // virtual destructor
};
class SportsCar : public car {
    public:

    string brand;
    string model;
    bool isEngineOn;
    int currentGear;
    int currentSpeed;

    SportsCar(string b, string m){
       this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentGear = 0;
        currentSpeed = 0;
    }

    void startEngine() override {
        isEngineOn = true;
        cout << "Engine started for " << brand << " " << model << endl;
    }

    void shiftgear(int gear) override {
        if (isEngineOn) {
            currentGear = gear;
            cout << "Gear shifted to " << currentGear << " for " << brand << " " << model << endl;
        } else {
            cout << "Cannot shift gear, engine is off." << endl;
        }
    }

    void accelerate() override {
        if (isEngineOn) {
            currentSpeed += 10; // Increase speed by 10
            cout << "Accelerating " << brand << " " << model << " to " << currentSpeed << " km/h" << endl;
        } else {
            cout << "Cannot accelerate, engine is off." << endl;
        }
    }

    void brake() override {
        if (currentSpeed > 0) {
            currentSpeed -= 10; // Decrease speed by 10
            cout << "Braking " << brand << " " << model << ", current speed: " << currentSpeed << " km/h" << endl;
        } else {
            cout << "Already at a stop." << endl;
        }
    }

    void stopEngine() override {
        isEngineOn = false;
        currentGear = 0;
        currentSpeed = 0;
        cout << "Engine stopped for " << brand << " " << model << endl;
    }
};

int main(){
   car* myCar = new SportsCar("Ferrari", "488 GTB");
    myCar->startEngine();
    myCar->shiftgear(1);
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine();
    delete myCar; // Clean up memory
    return 0;
}
