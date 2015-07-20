#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include "merger.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_selectfiles_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_trans_clicked();

private:
    Ui::Dialog *ui;
    mem m;
};

#endif // DIALOG_H
