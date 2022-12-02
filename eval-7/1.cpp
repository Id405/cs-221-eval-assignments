#include <cmath>
#include <tuple>
#include <vector>
using namespace std;

class Car {
private:
  double x;
  double y;
  double milesPerGallon;
  double fuelTankCapacityGallons;
  double fuelGallons;

public:
  Car(double x, double y, float milesPerGallon, double fuelTankCapacityGallons,
      double fuelGallons)
      : x(x), y(y), milesPerGallon(milesPerGallon),
        fuelTankCapacityGallons(fuelTankCapacityGallons) {}
  bool moveTo(double destinationX, double destinationY) {
    double gallonCost =
        hypot(x - destinationX, y - destinationY) * milesPerGallon;
    if (gallonCost > fuelGallons) {
      return false;
    }

    fuelGallons -= gallonCost;
    x = destinationX;
    y = destinationY;
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

int main() {
    return 0;
}