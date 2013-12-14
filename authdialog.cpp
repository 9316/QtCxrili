#include "authdialog.h"
#include "ui_authdialog.h"
#include <QDebug>
#include <QMessageBox>

authDialog::authDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authDialog)
{
    ui->setupUi(this);
    log = QSqlDatabase::addDatabase("QSQLITE");
    log.setDatabaseName("C:/Users/nikusha/Desktop/login");
    log.open();
    auth=false;

}

authDialog::~authDialog()
{
    delete ui;
}

void authDialog::on_pushButton_clicked()
{
    QString name;
    QString pass;
        name = ui->lineEdit->text();
         pass = ui->lineEdit_2->text();

        QSqlQuery qry;
        QString sql = "SELECT username, password FROM Users WHERE username='%1' AND password='%2'";

        if(qry.exec(sql.arg(name)
                    .arg(pass))){

            if(qry.next()){
              QMessageBox::information(this,"ინფორმაცია", "ავტორიზაცია წარმატებულია");

            }
            else{
                 auth=false;
            }
            }

        if(auth){
            this->close();
        }
       else if(ui->lineEdit->text().trimmed().isEmpty()){

            QMessageBox::information(this,"ინფორმაცია","ველები არ არის შევსებული");
        }


    }

