#include "DefaultStateChartDriver.h"

#include <Default.h>

#include <QDebug>
#include <QCoreApplication>
#include <QElapsedTimer>

DefaultStateChartDriver::DefaultStateChartDriver( QObject* parent, Default* sc) :
        m_sc(sc)
{
    //void

}

DefaultStateChartDriver::~DefaultStateChartDriver()
{
    //void
}


void DefaultStateChartDriver::onStateChartCycle()
{

    //void
    m_sc->runCycle();
    if (m_sc->getDefaultSCI()->isRaised_heartbeat())
    {
    	static QElapsedTimer timer;
    	if (timer.isValid())
    		qDebug() << "heartbeat :" << timer.elapsed() << "/ 1000";
        timer.restart();
    }
    if (m_sc->getDefaultSCI()->isRaised_footstomp())
    {
    	static QElapsedTimer timer;
    	if (timer.isValid())
    		qDebug() << "footstomp :"  << timer.elapsed() << "/300";
        timer.restart();
    }
    if (m_sc->getDefaultSCI()->isRaised_fingertap())
    {
    	static QElapsedTimer timer;
    	if (timer.isValid())
    		qDebug() << "fingertap :"  << timer.elapsed() << "/ 215";
        timer.restart();
    }

    if (m_sc->getDefaultSCI()->isRaised_done())
    {
        qDebug() << "done";
        QCoreApplication::quit();
    }
}
