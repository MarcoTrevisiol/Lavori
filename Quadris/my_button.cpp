#include "my_button.h"

My_Button::My_Button(u x_,u y_,u z_,QWidget *parent) :
    QPushButton(parent)
{
    x = x_;
    y = y_;
    z = z_;
    connect(this,SIGNAL(released()),SLOT(Clic()));
}


void My_Button::Clic()
{
    emit Cliced(x,y,z);
}


void My_Button::Evid(bool b)
{
    if (b)
        setStyleSheet("background-color: yellow");
    else
        setStyleSheet("");
}
