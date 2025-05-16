#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  // <- Это обязательно!

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_connectButton_clicked();  // Слот для кнопки подключения
    void readSerialData();            // Слот для чтения данных
    void handleSerialError(QSerialPort::SerialPortError error);  // Обработчик ошибок

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    void updatePortsList();  // Функция обновления списка портов
};
#endif // MAINWINDOW_H
