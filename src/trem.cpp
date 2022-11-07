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

void Trem::passRegion(int right, int down, int left, int up) {
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

    return;
}


// Função a ser executada após executar trem->START.
void Trem::run() {
    while(true) {

        // Region 0.
        if (currentPos.x == startPos.x
                && currentPos. y == startPos.y) {
            if (ID == 2) {
                mutex[0].unlock(); // From Region 9.
            }
            if (ID == 4) {
                mutex[5].unlock(); // From Region 9.
            }
            if (ID == 5) {
                mutex[6].unlock(); // From Region 9.
            }
            passRegion(90, 0, 0, 0);
        }

        // Region 1.
        else if (currentPos.x == startPos.x + 90
             && currentPos.y == startPos.y) {
            if (ID == 3) {
                mutex[1].lock(); // Into Region 4.
            }
            if (ID == 4) {
                mutex[3].lock(); // Into Region 4.
            }
            passRegion(40, 0, 0, 0);
        }

        // Region 2.
        else if (currentPos.x == startPos.x + 130
             && currentPos.y == startPos.y) {
            if (ID == 4) {
                mutex[2].unlock(); // From Region 11.
            }
            if (ID == 5) {
                mutex[4].unlock(); // From Region 11.
            }
            passRegion(100, 0, 0, 0);
        }

        // Region 3.
        else if (currentPos.x == startPos.x + 230
             && currentPos.y == startPos.y) {
            if (ID == 1) {
                mutex[0].lock(); // Into Region 6.
            }
            if (ID == 3) {
                mutex[5].lock(); // Into Region 6.
            }
            if (ID == 4) {
                mutex[6].lock(); // Into Region 6.
            }
            passRegion(20, 20, 0, 0);
        }

        // Region 4.
        else if (currentPos.x == startPos.x + 250
             && currentPos.y == startPos.y + 20) {
            if (ID == 3) {
                mutex[1].unlock(); // From Region 1.
            }
            if (ID == 4) {
                mutex[3].unlock(); // From Region 1.
            }
            passRegion(0, 80, 0, 0);
        }

        // Region 5.
        else if (currentPos.x == startPos.x + 250
             && currentPos.y == startPos.y + 100) {
            if (ID == 1) {
                mutex[2].lock(); // Into Region 8.
            }
            if (ID == 2) {
                mutex[4].lock(); // Into Region 8.
            }
            passRegion(0, 20, 20, 0);
        }

        // Region 6.
        else if (currentPos.x == startPos.x + 230
             && currentPos.y == startPos.y + 120) {
            if (ID == 1) {
                mutex[0].unlock(); // From Region 3.
            }
            if (ID == 3) {
                mutex[5].unlock(); // From Region 3.
            }
            if (ID == 4) {
                mutex[6].unlock(); // From Region 3.
            }
            passRegion(0, 0, 90, 0);
        }

        // Region 7.
        else if (currentPos.x == startPos.x + 140
             && currentPos.y == startPos.y + 120) {
            if (ID == 1) {
                mutex[1].lock(); // Into Region 10.
            }
            if (ID == 2) {
                mutex[3].lock(); // Into Region 10.
            }
            passRegion(0, 0, 40, 0);
        }

        // Region 8.
        else if (currentPos.x == startPos.x + 100
             && currentPos.y == startPos.y + 120) {
            if (ID == 1) {
                mutex[2].unlock(); // From Region 5.
            }
            if (ID == 2) {
                mutex[4].unlock(); // From Region 5.
            }
            passRegion(0, 0, 100, 0);
        }

        // Region 9.
        else if (currentPos.x == startPos.x
             && currentPos.y == startPos.y + 120) {
            if (ID == 2) {
                mutex[0].lock(); // Into Region 0.
            }
            if (ID == 4) {
                mutex[5].lock(); // Into Region 0.
            }
            if (ID == 5) {
                mutex[6].lock(); // Into Region 0.
            }
            passRegion(0, 0, 20, 20);
        }

        // Region 10.
        else if (currentPos.x == startPos.x - 20
             && currentPos.y == startPos.y + 100) {
            if (ID == 1) {
                mutex[1].unlock(); // From Region 7.
            }
            if (ID == 2) {
                mutex[3].unlock(); // From Region 7.
            }
            passRegion(0, 0, 0, 80);
        }

        // Region 11.
        else if (currentPos.x == startPos.x - 20
             && currentPos.y == startPos.y + 20) {
            if (ID == 4) {
                mutex[2].lock(); // Into Region 2.
            }
            if (ID == 5) {
                mutex[4].lock(); // Into Region 2.
            }
            passRegion(0, 0, 0, 20);
            passRegion(20, 0, 0, 0);
        }
    }
}
