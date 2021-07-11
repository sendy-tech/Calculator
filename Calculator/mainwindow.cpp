#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secretmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = 0;
    timer = new QTimer(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_change, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect (timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_sub->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
    ui->pushButton_equal->setCheckable(true);
    ui->pushButton_in->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;
    if(ui->result_show->text().contains('.')&& button->text() == '0'){
        new_label = ui->result_show->text()+button->text();
    }else
    {
    all_numbers = (ui->result_show->text()+button->text()).toDouble();
    new_label = QString::number(all_numbers, 'g', 15);
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_show->text().contains('.')))
    {
        ui->result_show->setText(ui->result_show->text()+".");
    }
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;

    if(button->text() == "+/-"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * -1;
        new_label = QString::number(all_numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }
    else if(button->text() == "%"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();
    if(ui->result_show_2->text().contains('('))
    {
        ui->result_show_2->setText("(" + ui->result_show->text() + button->text());
    }
    else{
        ui->result_show_2->setText(ui->result_show->text() + button->text());
    }
    num_first = ui->result_show->text().toDouble();
    ui->result_show->setText("");
    button->setChecked(true);
}

void MainWindow::on_pushButton_C_clicked()
{
    QString new_label;
    new_label =   ui->result_show->text();
    if(new_label.length() == 1)
    {
        new_label = "0";
    }
    else{
    new_label.chop(1);
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_equal_pressed(){
    timer->start(1);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
 int key = event->key();
 QString str = QString(QChar(key));
 if(s>5000)
 {
    oldText = "Timeout";
 }
 if ((oldText == "123")&& (secretFlag==true)){
     SecretMenu secret;
     secret.setWindowTitle("Секретное меню");
     secret.setModal(true);
     secret.exec();
     s = 0;
     secretFlag = false;
     oldText = "";
 }
 if (key>=Qt::Key_0 && key<=Qt::Key_9) {
  oldText = oldText+str;
 }
}

void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, num_second;
    QString new_label;
    timer->stop();
    if(s>=4000){
        secretFlag = true;
        s = 0;
        timer->start(1);
    }
    s = 0;
    num_second = ui->result_show->text().toDouble();
    ui->pushButton_equal->setChecked(true);
    if(ui->pushButton_add->isChecked()){
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->result_show_2->setText(ui->result_show_2->text() + QString::number(num_second, 'g', 15));
        ui->result_show->setText(new_label);
        ui->pushButton_add->setChecked(false);
    }else if (ui->pushButton_sub->isChecked()){
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->result_show_2->setText(ui->result_show_2->text() + QString::number(num_second));
        ui->result_show->setText(new_label);
        ui->pushButton_sub->setChecked(false);
    }
    else if (ui->pushButton_mult->isChecked()){
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber, 'g', 15);
        ui->result_show_2->setText(ui->result_show_2->text() + QString::number(num_second));
        ui->result_show->setText(new_label);
        ui->pushButton_mult->setChecked(false);
        }
    else if (ui->pushButton_division->isChecked()){
        if(num_second==0){
            ui->result_show->setText("0");
        }
        else
        {
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber, 'g', 15);
            ui->result_show_2->setText(ui->result_show_2->text() + QString::number(num_second));
            ui->result_show->setText(new_label);
        }
        ui->pushButton_division->setChecked(false);
        }
}

void MainWindow::on_pushButton_in_clicked()
{
    if(ui->pushButton_in->isChecked()){
    ui->result_show_2->setText( "(" + ui->result_show->text());
    }
    else{
        ui->result_show_2->setText(ui->result_show_2->text()+ ")");
        ui->pushButton_in->setChecked(false);
    }
}

void MainWindow::TimerSlot()
{
    s++;
}
