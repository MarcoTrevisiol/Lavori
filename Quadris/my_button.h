#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <QPushButton>
#include "partita.h"

class My_Button : public QPushButton
{
    Q_OBJECT
public:
    explicit My_Button(u,u,u,QWidget *parent = 0);
    void Evid(bool);

signals:
    void Cliced(uint,uint,uint);

private:
    u x,y,z;
public slots:
    void Clic();

};

#endif // MY_BUTTON_H
