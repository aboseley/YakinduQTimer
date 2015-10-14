

#include <QCoreApplication>

#include "QTimerInterface.h"
#include "Default.h"
#include "DefaultStateChartDriver.h"

int main( int argc, char * argv[] )
{
    QCoreApplication app(argc, argv);

    Default sc;
    DefaultStateChartDriver* driver = new DefaultStateChartDriver ( &app, &sc );
    QTimerInterface* sc_timers = new QTimerInterface( &app  );

    QObject::connect( sc_timers,  &QTimerInterface::timeout,
                                  driver, &DefaultStateChartDriver::onStateChartCycle );

    sc.setTimer( sc_timers );
    sc.init();
    sc.enter();

    return app.exec();
}

