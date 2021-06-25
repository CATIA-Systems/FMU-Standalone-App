#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Simulator.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Simulator *worker = new Simulator;

    connect(ui->switchPushButton, &QPushButton::pressed, worker, &Simulator::closeSwitch);
    connect(ui->switchPushButton, &QPushButton::released, worker, &Simulator::openSwitch);
    connect(ui->TAmbDoubleSpinBox, &QDoubleSpinBox::valueChanged, worker, &Simulator::setAmbientTemperature);

    connect(worker, &Simulator::resultReady, this, &MainWindow::showTemperature);
    connect(worker, &Simulator::errorMessage, this, &MainWindow::handleError);

    worker->start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::showTemperature(double temperature)
{
    ui->temperatureLcdNumber->display(temperature);
}

void MainWindow::handleError(const QString &message)
{
    QMessageBox::critical(this, "An error occurred", message);
    QApplication::exit(1);
}
