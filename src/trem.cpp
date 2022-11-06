#include "trem.h"
#include <QtCore>
#include<iostream>

QMutex mutex;

//Construtor.
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    startPos.x = x;
    startPos.y = y;
    currentPos.x = x;
    currentPos.y = y;
    speed = 100;
}

void Trem::setSpeed(int speed){
    this->speed = speed;
}

void Trem::passCritical0() {
    mutex.lock();
    while(true) {
        switch (ID) {
        case 1:
            if (currentPos.x < (startPos.x + 270) && currentPos.y == startPos.y) {
                    currentPos.x += 10;
            }
            else if (currentPos.x == (startPos.x + 270)
                            && currentPos.y < (startPos.y + 120)) {
                currentPos.y += 10;
            }
            else if (currentPos.x > (startPos.x + 250)) {
                currentPos.x -= 10;
            }
            else {
                mutex.unlock();
                return;
            }
            break;

        case 2:
            if (currentPos.x > startPos.x && currentPos.y == (startPos.y + 120)) {
                currentPos.x -= 10;
            }
            else if (currentPos.x == startPos.x && currentPos.y > startPos.y ) {
                currentPos.y -= 10;
            }
            else if (currentPos.x < (startPos.x + 20)) {
                currentPos.x += 10;
            }
            else {
                mutex.unlock();
                return;
            }
            break;

        default:
            break;
        }

        emit updateGUI(ID, currentPos.x, currentPos.y);
        while(speed == 0)
            continue;
        msleep(200 - speed);
    }
}

// Função a ser executada após executar trem->START.
void Trem::run() {
    while(true) {
        switch (ID) {
        case 1:
            if (currentPos.x < (startPos.x + 250) && currentPos.y == startPos.y) {
                currentPos.x += 10;
            }
            else if (currentPos.x == (startPos.x + 250) && currentPos.y < (startPos.y + 120)) {
                passCritical0();
            }
            else if (currentPos.x > startPos.x && currentPos.y == (startPos.y + 120)) {
                currentPos.x -= 10;
            }
            else {
                currentPos.y -= 10;
            }
            break;

        case 2:
            if (currentPos.x < (startPos.x + 270) && currentPos.y == startPos.y) {
                currentPos.x += 10;
            }
            else if (currentPos.x == (startPos.x + 270) && currentPos.y < (startPos.y + 120)) {
                currentPos.y += 10;
            }
            else if (currentPos.x > (startPos.x + 20) && currentPos.y == (startPos.y + 120)) {
                currentPos.x -= 10;
            }
            else {
                passCritical0();
            }
            break;

        default:
            break;
        }

        emit updateGUI(ID, currentPos.x, currentPos.y);
        while(speed == 0)
            continue;
        msleep(200 - speed);
    }
}
