#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setScene(&scene);
    ui->centralWidget->setSceneRect(0,0,100,100);
    scene.addRect(0,0,100,100);

    srand(time(0));
    AddActor(nul);
    AddActor(nul);
    AddActor(nul);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddActor(typeAct t)
{
    BasicActor *ba = F.AddActor(t);
    QBrush br(Qt::red);
    scene.addEllipse(ba->getx(),ba->gety(),10,10,QPen(),br);
}
