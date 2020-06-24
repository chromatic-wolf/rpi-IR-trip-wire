#include "irtripwire.h"
#include "WiringPi-master/wiringPi/wiringPi.h"
//#include <wiringPi.h>
//#include <unistd.h>
#include <iostream>
#include <qobject.h>
#include <qdebug.h>
#include <QElapsedTimer>

bool stopLoop = false;
void sensorLoop();
unsigned long *loopDelay;
unsigned long *triggerDelay;
int *triggerValue;

IrTripWire::IrTripWire(unsigned long loopDelayMicroSecs, unsigned long triggerDelayMicroSecs, int triggerValueUnit)
{
    //The delay when checking if the capacitor charge time is above specified value
    loopDelay = new unsigned long(loopDelayMicroSecs);
    triggerDelay = new unsigned long(triggerDelayMicroSecs);
    triggerValue = new int(triggerValueUnit);

}

void IrTripWire::run()
{
    sensorLoop();
}
void IrTripWire::exit()
{
    stopLoop = true;

}

bool IrTripWire::setLoopDelay(unsigned long loopDelayMicroSecs)
{
    *loopDelay = loopDelayMicroSecs;
    return true;
}

bool IrTripWire::setTriggerDelay(unsigned long triggerDelayMicroSecs)
{
    *triggerDelay = triggerDelayMicroSecs;
    return true;
}

bool IrTripWire::setTriggerValueDelay(unsigned long triggerValueUnit)
{
    *triggerValue = triggerValueUnit;
    return true;
}

unsigned long *IrTripWire::getLoopDelay()
{
return loopDelay;
}

unsigned long * IrTripWire::getTriggerDelay()
{
return triggerDelay;
}

int * IrTripWire::getTriggerValueDelay()
{
return triggerValue;
}




void IrTripWire::sensorLoop()
{
    QElapsedTimer  *timer = new QElapsedTimer();


    qInfo() << "Sensor loop started";
    while(stopLoop == false)
    {
        timer->restart();
        timer->start();
        //int count = 0;
        pinMode (0, OUTPUT) ;
        digitalWrite (0,  LOW) ;

        usleep(*loopDelay);
        pinMode (0, INPUT) ;


        while(digitalRead(0) == LOW && stopLoop == false)
        {
            //count += 1;

        }


        //std::cout << count << std::endl;


        if(timer->elapsed() > 1000)
        {
            std::cout << "sending signal" << std::endl;
            emit triggered(timer->elapsed());
            usleep(*triggerDelay);
//            digitalWrite(7, HIGH);
//            usleep(1000000);
//            digitalWrite(7, LOW);

        }
    }
    std::cout << "Sensor stopping" << std::endl;

}
