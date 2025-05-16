#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);
    ui->statusLabel->setText("Улова нет");
    ui->statusLabel->setStyleSheet("color: red; font-weight: bold;");

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::on_connectButton_clicked);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    connect(serial, &QSerialPort::errorOccurred, this, &MainWindow::handleSerialError);

    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);


    updatePortsList();
}



void MainWindow::updatePortsList()
{
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(port.portName());
    }
}

void MainWindow::on_connectButton_clicked()
{

    qDebug() << "Кнопка подключения нажата";

    if (serial->isOpen()) {

        serial->close();
        ui->connectButton->setText("Подключиться к Arduino");
        return;
    }

    QString portName = ui->comboBox->currentText();
    qDebug() << "Попытка открыть порт:" << portName;

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);

    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Порт успешно открыт";
        ui->connectButton->setText("Отключиться");
    } else {
        qDebug() << "Ошибка открытия порта:" << serial->errorString();
    }
}

void MainWindow::readSerialData()
{
    QByteArray data = serial->readAll();
    qDebug() << "Raw data:" << data;

    if (data.contains("1")) {
        ui->statusLabel->setText("АКТИВЕН");
        ui->statusLabel->setStyleSheet("color: green; font-weight: bold;");
    }
    else if (data.contains("0")) {
        ui->statusLabel->setText("НЕ АКТИВЕН");
        ui->statusLabel->setStyleSheet("color: red; font-weight: bold;");
    }
}



void MainWindow::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        qDebug() << "Ошибка:" << serial->errorString();
        if (serial->isOpen()) {
            serial->close();
        }
        ui->connectButton->setText("Подключиться к Arduino");
    }
}

MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete ui;
}
