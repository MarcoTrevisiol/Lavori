#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainhead.h"
#include "field.h"
#include "basicactor.h"
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddActor(typeAct t);
    
private:
    Ui::MainWindow *ui;

    Field F;
    QGraphicsScene scene;
};

#endif // MAINWINDOW_H
