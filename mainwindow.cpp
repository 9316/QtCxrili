#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <authdialog.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <dialogadd.h>
#include <QFont>
#include <QHeaderView>
#include <QMessageBox>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


       ui->setupUi(this);
       
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/nika/Desktop/nike");
    db.open();
    QFont font;
    font.setPointSize(10);

    QHeaderView* header = new QHeaderView(Qt::Horizontal);
   header->setFont(font);
    header->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
    ui->tableView->setHorizontalHeader(header);


    model = new QSqlTableModel(this, db);
    model->setTable("info");
    model->select();
    model->removeColumn(0);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, tr("სახელი"));
    model->setHeaderData(1, Qt::Horizontal, tr("გვარი"));
    model->setHeaderData(2, Qt::Horizontal, tr("დაბადების თაროღი"));
    model->setHeaderData(3, Qt::Horizontal, tr ("პროფესია"));
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
    this->showMaximized();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->label->hide();
    ui->label_2->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->pushButton->hide();
    showLabel=false;






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QSqlQuery qry(db);
    DialogAdd add;
QString sql = "INSERT INTO info(name,lastName,datebirthDay,information)"
            "VALUES ('%1', '%2', '%3', '%4')";

    add.setModal(true);
    add.exec();
    if(add.name.size()!=0 && add.lastName.size()!=0){
        qry.exec(sql.arg(add.name)
                 .arg(add.lastName).
                 arg(add.datebirthDay)
                 .arg(add.information));
        QSqlRecord rec = model->record();
        model->setRecord(model->rowCount(),rec);
        model->submitAll();
    }
    else {
        QMessageBox::information(this,"ინფორმაცია","ველები არ არის შევსებულუ");
    }



}
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    QString lastName = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    QString datebirthDay = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString();
    QString information = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString();
    QSqlQuery qry(db);
    qry.prepare("SELECT name FROM info WHERE name=:name");
    qry.bindValue(":name",name);
    qry.exec();
    qry.next();
}

void MainWindow::on_action_2_triggered()
{
    QSqlQuery qry(db);
    int rowid = ui->tableView->selectionModel()->selectedIndexes().at(0).row();
    QString sql ="DELETE FROM info WHERE name='%1' AND lastName='%2'";
    QString name = ui->tableView->model()->data(ui->tableView->model()->index(rowid,0)).toString();
    QString lastName = ui->tableView->model()->data(ui->tableView->model()->index(rowid,1)).toString();
    qry.exec(sql.arg(name).arg(lastName));
    model->submitAll();
}

void MainWindow::on_action_4_triggered()
{
    if(!showLabel){
        ui->label->show();
        ui->label_2->show();
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->pushButton->show();
        showLabel=true;
    }
    else {
        ui->label->hide();
        ui->label_2->hide();
        ui->lineEdit->hide();
        ui->lineEdit_2->hide();
        ui->pushButton->hide();
        showLabel=false;
    }
}

void MainWindow::on_pushButton_clicked()
{
     QString name= ui->lineEdit->text();
     QString lastName= ui->lineEdit_2->text();
    QSortFilterProxyModel *proxymodel = new QSortFilterProxyModel(this);
    proxymodel->setSourceModel(model);
    QSortFilterProxyModel *proxymodel2 = new QSortFilterProxyModel(this);
    proxymodel2->setSourceModel(proxymodel);

    if(!ui->lineEdit->text().trimmed().isEmpty()){
        proxymodel->setFilterRegExp(QRegExp(name, Qt::CaseSensitive, QRegExp::FixedString));
        proxymodel->setFilterKeyColumn(-1);
        ui->tableView->setModel(proxymodel);
        ui->tableView->show();
    }
    if(!ui->lineEdit_2->text().trimmed().isEmpty()){
        proxymodel2->setFilterRegExp(QRegExp(lastName, Qt::CaseSensitive, QRegExp::FixedString));
        proxymodel2->setFilterKeyColumn(-1);
        ui->tableView->setModel(proxymodel2);
        ui->tableView->show();
    }

    if(ui->lineEdit->text().trimmed().isEmpty() && ui->lineEdit_2->text().trimmed().isEmpty()){
        QMessageBox::information(this,"ყურადღება", "ველები არ არის შევსებული");
    }

}

void MainWindow::on_action_3_triggered()
{
     QMessageBox::StandardButton butt;
     butt = QMessageBox::question(this,"ყურადღება", "გსურთ პროგრამიდან გასვლა" ,QMessageBox::Yes | QMessageBox::No);
     if(butt==QMessageBox::Yes){ 
     
         this->close();
     }
     else QMessageBox::information(this,"ინფორმაცია", "თქვენ აგრძელებთ მუშაობას");

}
