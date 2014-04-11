#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "casuale.h"
#include "tess_greedy.h"
#include "tess_deep.h"
#include "greedy_m.h"
#include "widpar.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

    QStringListModel types_p;
    IVPlayer* newPlayer(int i, bool r_o);

    std::list<t_savp> cur_p;
    std::list<t_savp>::iterator itc;

public slots:
    void SetOP(int i);
    void SetXP(int i);

    void Carica();
    void Next();
    void Prev();
    void FdpSav();
};

#endif // DIALOG_H
