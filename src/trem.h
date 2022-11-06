#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>

struct coordenate {
    int x;
    int y;
};

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread {
    Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    void run();         //função a ser executada pela thread
    void setSpeed(int);
    void passRegion(int, int, int, int, int);

signals:
    void updateGUI(int,int,int);

private:
    coordenate currentPos;
    coordenate startPos;
    int ID;
    int speed;
};

#endif // TREM_H
