#include "elevator.h"

Elevator::Elevator(){
    for (int i = 0; i < 9; i++){
        Floor floor(i);
        this->floors.push_back(floor);
    }

    this->queue.resize(9);
}

int Elevator::getCurPas(){
    return this->currentPas.size();
}

void Elevator::takePassangers(){
    if (this->currentPas.size() == 4) return;
    if (this->queue[this->currentFloor].size() == 0) return;

    int taken = 0;
    direction were;
    if (this->status == UP) were = LAST;
    else if (this->status == DOWN) were = FIRST;

    for (int i = 0; i < this->queue[this->currentFloor].size(); i++){
        if (this->queue[this->currentFloor][i].where == were){
            this->currentPas.push_back(this->queue[this->currentFloor][i]);
            this->queue[this->currentFloor].remove(i);
            i--;
            if (were == LAST) this->floors[currentFloor].setCountUp(this->floors[currentFloor].getCountUp()-1);
            else this->floors[currentFloor].setCountDown(this->floors[currentFloor].getCountDown()-1);
            taken++;
            if (this->currentPas.size() == 4) break;
        }
    }
    emit passangerTaken(this->currentFloor);
}

int Elevator::mDestFloor(){
    if (this->getCurPas() == 0) return -1;
    if (this->status == UP){
        int max_dest_floor = 0;
        for (int i = 0; i < this->currentPas.size(); i++){
            if (max_dest_floor < this->currentPas[i].getDestFloor())
                    max_dest_floor = this->currentPas[i].getDestFloor();
        }
        return max_dest_floor;
    }
    else if (this->status == DOWN){
        int min_dest_floor = 8;
        for (int i = 0; i < this->currentPas.size(); i++){
            if (min_dest_floor > this->currentPas[i].getDestFloor())
                    min_dest_floor = this->currentPas[i].getDestFloor();
        }
        return min_dest_floor;
    }
    return -1;
}

void Elevator::releasePassangers(){
    if (this->getCurPas() == 0){
        return;
    }
    for (int i = 0; i < this->currentPas.size(); i++){
        if (this->currentPas[i].getDestFloor() == this->currentFloor){
            this->currentPas.remove(i);
            i--;
        }
    }
    emit passangerReleased(this->currentFloor, this->status);
}

bool Elevator::isWaiting(){
    for (int i = 0; i < this->queue.size(); i++){
        if (!this->queue[i].empty()) return true;
    }
    return false;
}

int Elevator::chooseDestFloor(){
    int dist = -1, dist2 = -2, destFloor = -1, destFloor2= -2;

    for (int i = 0; i <= this->currentFloor; i++){
        if (!this->queue[i].empty()){
            dist = (this->currentFloor - i);
            destFloor = i;
            break;
        }
    }

    for (int i = 8; i >= this->currentFloor; i--){
        if (!this->queue[i].empty()){
            dist2 = i - this->currentFloor;
            destFloor2 = i;
            break;
        }
    }

    if (dist >= 0 && dist2 >= 0) {
        if (dist < dist2) {
            this->status = DOWN;
            return destFloor;
        } else if (dist > dist2) {
            this->status = UP;
            return destFloor2;
        } else if (dist == dist2) {
            if (this->status == UP) {
                return destFloor2;
            } else {
                return destFloor;
            }
        }
    } else if (dist >= 0 && dist2 < 0) {
        this->status = DOWN;
        return destFloor;
    } else if (dist < 0 && dist2 >= 0) {
        this->status = UP;
        return destFloor2;
    } else if (dist == 0 && dist2 == 0) {
        if (this->status == UP) {
            return destFloor2;
        } else {
            return destFloor;
        }
    }
    return -1;
}


void Elevator::loop(){
    int destFloor;
    while (isWaiting()){

            destFloor = this->chooseDestFloor();
            do{
                if (currentFloor == 8 && this->status == UP) this->status = DOWN;
                if (currentFloor == 0 && this->status == DOWN) this->status = UP;
                this->takePassangers();
                if (this->getCurPas() != 0) destFloor = mDestFloor();
                QThread::msleep(500);
                if (this->status == UP && this->currentFloor != 8) this->currentFloor++;
                else if (this->status == DOWN && this->currentFloor != 0) this->currentFloor--;
                emit (floorChanged(this->currentFloor, this->status));
                QThread::msleep(500);
                this->releasePassangers();
            } while (this->currentFloor != destFloor);
        }
    this->status = IDLE;
    emit passangerReleased(this->currentFloor, this->status);
    emit finished();
}
