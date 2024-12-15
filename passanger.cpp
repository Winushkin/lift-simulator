#include "passanger.h"

Passanger::Passanger(){}

Passanger::Passanger(int c, direction w){
    this->currentFloor = c;
    this->where = w;
    this->destinationFloor = this->randFloor();
}

int Passanger::randFloor(){
    int min_floor = 0;
    int max_floor = 8;
    std::random_device dice;
    std::mt19937 gen(dice());
    if (this->where == LAST){
        std::uniform_int_distribution<> dis(this->currentFloor + 1, max_floor);
        return dis(gen);
    } else{
        std::uniform_int_distribution<> dis(min_floor, this->currentFloor - 1);
        return dis(gen);
    }
}

int Passanger::getDestFloor(){
    return this->destinationFloor;
}
