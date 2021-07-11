#include "secretmenu.h"
#include "ui_secretmenu.h"

SecretMenu::SecretMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecretMenu)
{
    ui->setupUi(this);
}

SecretMenu::~SecretMenu()
{
    delete ui;
}

void SecretMenu::on_pushButton_back_clicked()
{
    hide();
}
