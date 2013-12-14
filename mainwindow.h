#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase db;
    QSqlTableModel *model;
    bool showLabel;
    
private slots:
    void on_action_triggered();





    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_pushButton_clicked();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
