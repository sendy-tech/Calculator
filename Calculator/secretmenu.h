#ifndef SECRETMENU_H
#define SECRETMENU_H

#include <QDialog>

namespace Ui {
class SecretMenu;
}

class SecretMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SecretMenu(QWidget *parent = nullptr);
    ~SecretMenu();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::SecretMenu *ui;
};

#endif // SECRETMENU_H
