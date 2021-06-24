#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QThread>
#include "FMU.h"

class Simulator : public QThread
{
    Q_OBJECT

    void run() override;

signals:
    void resultReady(double temperature);


public slots:
    void openSwitch();
    void closeSwitch();
    void setAmbientTemperature(double temperature);

private:
    bool switchClosed = false;
    double ambientTemperature = 15;
    FMU *fmu = nullptr;
};

#endif // SIMULATOR_H
