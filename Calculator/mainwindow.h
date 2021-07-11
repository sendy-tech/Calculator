#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int s;
    double num_first;
    QString oldText;
    bool secretFlag = false;

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_C_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_equal_pressed();
    void math_operations();
    void on_pushButton_in_clicked();
    void keyPressEvent(QKeyEvent *event);
    void TimerSlot();

};

#endif // MAINWINDOW_H
