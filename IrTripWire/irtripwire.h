#ifndef IRTRIPWIRE_H
#define IRTRIPWIRE_H

#endif // IRTRIPWIRE_H
#include <QObject>
#include <QThread>

class IrTripWire : public QThread
{
    Q_OBJECT
private:

public:
    IrTripWire(unsigned long loopDelayMicroSecs, unsigned long triggerDelayMicroSecs, int triggerValueUnit);
    void sensorLoop();
    void run();
    void exit();
    bool setLoopDelay(unsigned long loopDelayMicroSecs);
    bool setTriggerDelay(unsigned long triggerDelayMicroSecs);
    bool setTriggerValueDelay(unsigned long triggerValueUnit);
    unsigned long *getLoopDelay();
    unsigned long *getTriggerDelay();
    int *getTriggerValueDelay();


signals:
void triggered(qint64 newValue);
};
