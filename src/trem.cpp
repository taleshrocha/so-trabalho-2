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

void Trem::passRegion(int right, int down, int left, int up, int mutexNum) {
    if (mutexNum != -1)
        mutex[mutexNum].lock();

    while(true) {

        if (right != 0) {
            right = right - 10;
            currentPos.x += 10;
        }
        else if (down != 0) {
            down = down - 10;
            currentPos.y += 10;
        }
        else if (left != 0) {
            left = left - 10;
            currentPos.x -= 10;
        }
        else if (up != 0) {
            up = up - 10;
            currentPos.y -= 10;
        }
        else {
            break;
        }

        emit updateGUI(ID, currentPos.x, currentPos.y);
        while (speed == 0);
        msleep(200 - speed);
    }

    if (mutexNum != -1)
        mutex[mutexNum].unlock();
    return;
}


// Função a ser executada após executar trem->START.
void Trem::run() {
    while(true) {
        if (currentPos.x == startPos.x
                && currentPos. y == startPos.y) {
            if (ID == 3) {
                passRegion(90, 0, 0, 0, -1);
                passRegion(160, 20, 0, 0, 1);
            }
            else {
                passRegion(230, 0, 0, 0, -1);
            }
        }
        else if (currentPos.y == startPos.y) {
            if (ID == 1) {
                passRegion(20, 120, 20, 0, 0);
            }
            else {
                passRegion(20, 120, 20, 0, -1);
            }
        }
        else if (currentPos.x == startPos.x + 230) {
            if (ID == 1) {
                passRegion(0, 0, 90, 0, -1);
                passRegion(0, 0, 160, 20, 1);
            }
            else {
                passRegion(0, 0, 230, 0, -1);
            }
        }
        else if (currentPos.x == startPos.x) {
            if (ID == 2) {
                passRegion(0, 0, 20, 120, 0);
                passRegion(20, 0, 0, 0, 0);
            }
            else {
                passRegion(0, 0, 20, 120, -1);
                passRegion(20, 0, 0, 0, -1);
            }
        }
    }
}
