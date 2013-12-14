#include "dialogadd.h"
#include "ui_dialogadd.h"
#include <QMessageBox>

DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdd)
{
    ui->setupUi(this);
}

DialogAdd::~DialogAdd()
{
    delete ui;
}

void DialogAdd::on_pushButton_clicked()
{
    if(ui->lineEdit->text().size()>0 && ui->lineEdit_2->text().size()>0 && ui->lineEdit_3->text().size()>0 && ui->lineEdit_4->text().size()>0){
        name = ui->lineEdit->text();
        lastName = ui->lineEdit_2->text();
        datebirthDay = ui->lineEdit_3->text();
        information = ui->lineEdit_4->text();
        this->close();
    }
    else {
    QMessageBox::warning(this,"ყუდღება", "დაფიქსირდა შეცდომა, ველები არ არის შევსებული");
    }
}
