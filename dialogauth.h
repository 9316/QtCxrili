#ifndef DIALOGAUTH_H
#define DIALOGAUTH_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql/QSql>

namespace Ui {
class Dialogauth;
}

class Dialogauth : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialogauth(QWidget *parent = 0);
    ~Dialogauth();
    QSqlDatabase log;
    bool auth;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialogauth *ui;
};

#endif // DIALOGAUTH_H
