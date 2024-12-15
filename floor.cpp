#include "floor.h"

Floor::Floor(){

}

Floor::Floor(int i){
    this->number = i;
}

int Floor::getCountUp(){
    return this->countUp;
}

int Floor::getCountDown(){
    return this->countDown;
}

void Floor::setCountUp(int c){
    this->countUp = c;
}

void Floor::setCountDown(int c){
    this->countDown = c;
}
