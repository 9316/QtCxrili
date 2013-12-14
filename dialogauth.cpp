#include "dialogauth.h"
#include "ui_dialogauth.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

Dialogauth::Dialogauth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogauth)
{
    ui->setupUi(this);
    log = QSqlDatabase::addDatabase("QSQLITE");
    log.setDatabaseName("C:/Users/nikusha/Desktop/login");
    log.open();
    auth=false;
}

Dialogauth::~Dialogauth()
{
    delete ui;
    log.close();
}


