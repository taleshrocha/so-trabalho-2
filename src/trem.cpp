#include "trem.h"
#include <QtCore>
#include<iostream>

QMutex mutex[7];

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
    mutex[0].lock();
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
            else if (currentPos.x > (startPos.x + 240)) {
                currentPos.x -= 10;
            }
            else {
                mutex[0].unlock();
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
            else if (currentPos.x < (startPos.x + 30)) {
                currentPos.x += 10;
            }
            else {
                mutex[0].unlock();
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


void Trem::passCritical1() {
    mutex[1].lock();
    while(true) {
        switch (ID) {
        case 1:
            if (currentPos.x > startPos.x) {
                    currentPos.x -= 10;
            }
            else if (currentPos.y > startPos.y + 90) {
                    currentPos.y -= 10;
            }
            else {
                mutex[1].unlock();
                return;
            }
            break;

        case 3:
            if (currentPos.x < (startPos.x + 270)) {
                currentPos.x += 10;
            }
            else if (currentPos.y < startPos.y + 30) {
                currentPos.y += 10;
            }
            else {
                mutex[1].unlock();
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

void Trem::passCritical2() {
    mutex[2].lock();
    while(true) {
        switch (ID) {
        case 1:
            if (currentPos.x > startPos.x + 160) {
                    currentPos.x -= 10;
            }
            else if (currentPos.y > startPos.y + 90) {
                    currentPos.y -= 10;
            }
            else {
                mutex[2].unlock();
                return;
            }
            break;

        case 4:
            if (currentPos.x < (startPos.x + 270)) {
                currentPos.x += 10;
            }
            else if (currentPos.y < startPos.y + 30) {
                currentPos.y += 10;
            }
            else {
                mutex[2].unlock();
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
            if (currentPos.x < (startPos.x + 240)
                    && currentPos.y == startPos.y) {
                currentPos.x += 10;
            }
            else if (currentPos.y < startPos.y + 120) {
                passCritical0();
            }
            else if (currentPos.x > startPos.x) {
                if (currentPos.x == startPos.x + 160) {
                    passCritical1();
                }

                else if (currentPos.x == startPos.x + 190) {
                    passCritical2();
                }
                else {
                    currentPos.x -= 10;
                }
            }
            else {
                currentPos.y -= 10;
            }
            break;

        case 2:
            if (currentPos.x < startPos.x + 270
                    && currentPos.y == startPos.y) {
                currentPos.x += 10;
            }
            else if (currentPos.y < startPos.y + 120) {
                currentPos.y += 10;
            }
            else if (currentPos.x > startPos.x + 30) {
                currentPos.x -= 10;
            }
            else {
                passCritical0();
            }
            break;

        case 3:
            if (currentPos.x < (startPos.x + 270)
                    && currentPos.y == startPos.y) {
                if (currentPos.x == (startPos.x + 100)) {
                    passCritical1();
                }
                else {
                    currentPos.x += 10;
                }
            }
            else if (currentPos.x == (startPos.x + 270)
                     && currentPos.y < (startPos.y + 120)) {
                currentPos.y += 10;
            }
            else if (currentPos.x > startPos.x
                     && currentPos.y == (startPos.y + 120)) {
                currentPos.x -= 10;
            }
            else {
                currentPos.y -= 10;
            }
            break;

        case 4:
            if (currentPos.x < (startPos.x + 270)
                    && currentPos.y == startPos.y) {
                if (currentPos.x == (startPos.x + 100)) {
                    passCritical2();
                }
                else {
                    currentPos.x += 10;
                }
            }
            else if (currentPos.x == (startPos.x + 270)
                     && currentPos.y < (startPos.y + 120)) {
                currentPos.y += 10;
            }
            else if (currentPos.x > startPos.x
                     && currentPos.y == (startPos.y + 120)) {
                currentPos.x -= 10;
            }
            else {
                currentPos.y -= 10;
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
