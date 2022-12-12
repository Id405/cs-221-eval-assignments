#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// Previous homework
class Car {
private:
  double x;
  double y;
  double milesPerGallon;
  double fuelTankCapacityGallons;
  double fuelGallons;

protected:
  void setX(double toX) { x = toX; }
  void setY(double toY) { y = toY; }
  void setFuelGallons(double gallons) { fuelGallons = gallons; }
  void burnGallons(double gallons) { fuelGallons -= gallons; }

public:
  Car(double x, double y, float milesPerGallon, double fuelTankCapacityGallons,
      double fuelGallons)
      : x(x), y(y), milesPerGallon(milesPerGallon),
        fuelTankCapacityGallons(fuelTankCapacityGallons) {}
  double getMilesPerGallon() { return milesPerGallon; }
  double getFuelTankCapacityGallons() { return fuelTankCapacityGallons; }
  double getFuelGallons() { return fuelGallons; }
  double getX() { return x; }
  double getY() { return y; }
  bool moveTo(double destinationX, double destinationY) {
    double gallonCost = hypot(getX() - destinationX, getY() - destinationY) *
                        getMilesPerGallon();
    if (gallonCost > getFuelGallons()) {
      return false;
    }

    burnGallons(gallonCost);
    setX(destinationX);
    setY(destinationY);
    return true;
  }
  double refillTank() {
    double refilledGallons = fuelTankCapacityGallons - fuelGallons;
    return refilledGallons;
  }
};

vector<Car> moveToPoint(vector<Car> cars, double destinationX,
                        double destinationY) {
  vector<Car> result;
  for (Car car : cars) {
    if (car.moveTo(destinationX, destinationY)) {
      result.push_back(car);
    }
  }

  return result; // Return array with size and a lot of other helpful things
                 // like god (the C++ standard library) intended us to do. This
                 // helpful construct is called a vector. I know its not an
                 // array. I know its not an array. I know its not an array. I
}

class GasStation {
private:
  double x;
  double y;
  double pricePerGallon;

public:
  GasStation(double x, double y, double pricePerGallon)
      : x(x), y(y), pricePerGallon(pricePerGallon) {}
  double getX() { return x; }
  double getY() { return y; }
  double getPricePerGallon() { return pricePerGallon; }
};

tuple<vector<Car>, vector<double>>
moveToPointGasStations(vector<Car> cars, vector<GasStation> gasStations,
                       double destinationX, double destinationY) {
  vector<Car> resultCar;
  vector<double> resultCost;

  for (Car car : cars) {
    double cost = 0;

    for (int i = gasStations.size(); i > 0; i--) {
      if (car.moveTo(destinationX, destinationY)) {
        resultCar.push_back(car);
        resultCost.push_back(cost);
        continue;
      }

      GasStation gasStation = gasStations.at(i);
      if (car.moveTo(gasStation.getX(), gasStation.getY())) {
        cost += car.refillTank() * gasStation.getPricePerGallon();
      } else {
        continue;
      }
    }
  }

  return {resultCar, resultCost};
}

// Homework 8
class Bus : public Car {
private:
  int maxPassengers;
  vector<int> passengers;
  double milesPerGallonPenaltyPerPassenger;

public:
  double getMilesPerGallon() {
    return Car::getMilesPerGallon() -
           passengers.size() * milesPerGallonPenaltyPerPassenger;
  }

  bool moveTo(double destinationX, double destinationY) {
    double gallonCost = hypot(getX() - destinationX, getY() - destinationY) *
                        getMilesPerGallon();
    if (gallonCost > getFuelGallons()) {
      return false;
    }

    burnGallons(gallonCost);
    setX(destinationX);
    setY(destinationY);
    return true;
  }

  vector<int> generateRoute() {
    vector<int>::iterator it = unique(passengers.begin(), passengers.end());
    vector<int> results = passengers;
    results.erase(it);

    return results;
  }
};

class Provider {
private:
  string name;
  string role;
};

class Patient {
private:
  string name;
  string condition;
};

class MedicalCenter {
private:
  vector<Provider> providers;
  vector<Patient> patients;

public:
  vector<Patient> getPatients() { return patients; }

  vector<Provider> getProviders() { return providers; }
};

class Ambulance : Car, MedicalCenter {
private:
  int patientCapacity;
  int providerCapacity;
  double gasMileagePenalty;

public:
  double getMilesPerGallon() {
    return Car::getMilesPerGallon() -
           getPatients().size() * getProviders().size() * gasMileagePenalty;
  }

  bool moveTo(double destinationX, double destinationY) {
    double gallonCost = hypot(getX() - destinationX, getY() - destinationY) *
                        getMilesPerGallon();
    if (gallonCost > getFuelGallons()) {
      return false;
    }

    burnGallons(gallonCost);
    setX(destinationX);
    setY(destinationY);
    return true;
  }
};

vector<Car> moveToPoint(vector<unique_ptr<Car>> cars, double destinationX,
                        double destinationY) {
  vector<Car> result;
  for (auto &car : cars) {
    if ((*car).moveTo(destinationX, destinationY)) {
      result.push_back(*car);
    }
  }

  return result; // Return array with size and a lot of other helpful things
                 // like god (the C++ standard library) intended us to do. This
                 // helpful construct is called a vector. I know its not an
                 // array. I know its not an array. I know its not an array. I
}

int main() { return 0; }