#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class authDialog;
}

class authDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit authDialog(QWidget *parent = 0);
    ~authDialog();
    QSqlDatabase log;
    bool auth;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::authDialog *ui;
};

#endif // AUTHDIALOG_H
