#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>

QSerialPort *serial;  // Make it global or class-level

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("LED CONTROLLER APP");
    // Initialize serial port
    serial = new QSerialPort(this);
    serial->setPortName("COM4");                // Set your COM port
    serial->setBaudRate(QSerialPort::Baud9600); // Match MCU baud
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Serial Error", "Failed to open COM4.");
    }
}

MainWindow::~MainWindow()
{
    if (serial->isOpen())
        serial->close();

    delete ui;
}

void MainWindow::on_redButton_clicked()
{
    if (serial->isOpen())
        serial->write("R");

}

void MainWindow::on_blueButton_clicked()
{
    if (serial->isOpen())
        serial->write("B");
}

void MainWindow::on_cycleButton_clicked()
{
    if (serial->isOpen())
        serial->write("C");
}
