#include "QTimerInterface.h"
#include "TimedStatemachineInterface.h"

#include <QTimerEvent>
#include <QDebug>
#include <QtGlobal>

QTimerInterface::QTimerInterface(QObject* parent) :
        QObject(parent)
{
    //void
}

QTimerInterface::~QTimerInterface()
{
    cancel();
}

void QTimerInterface::setTimer(TimedStatemachineInterface* statemachine,
        sc_eventid event, sc_integer time_ms, sc_boolean isPeriodic)
{
    CallbackInfo callback_info;
    callback_info.m_event = event;
    callback_info.m_periodic = isPeriodic;
    callback_info.m_state_machine = statemachine;

    callback_reverse_map_type::iterator it = m_timers_lookup.find(callback_info);
    if ( it != m_timers_lookup.end() )
    {
        qDebug() << "setTimers : orig "
                 << " event: " << it->first.m_event;

        qDebug() << "setTimers : "
                 << " event: " << callback_info.m_event;

        Q_ASSERT(  false );

        unsetTimer(statemachine,event);
    }

    int qt_timer = startTimer(time_ms);
    m_timers[qt_timer] = callback_info;
    m_timers_lookup[callback_info] = qt_timer;

}

void QTimerInterface::timerEvent(QTimerEvent *event)
{
    if (event)
    {
        callback_map_type::iterator it = m_timers.find(event->timerId());
        if (it != m_timers.end())
        {
            // make the state machine call back
            it->second.m_state_machine->raiseTimeEvent(it->second.m_event);
            emit timeout();
        }
    }
}

void QTimerInterface::unsetTimer(TimedStatemachineInterface* statemachine,
        sc_eventid event)
{

    CallbackInfo unset_timer;
    unset_timer.m_periodic = false;
    unset_timer.m_state_machine = statemachine;
    unset_timer.m_event = event;

    callback_reverse_map_type::iterator it = m_timers_lookup.find(unset_timer);
    if (it != m_timers_lookup.end())
    {
        killTimer(it->second);
        m_timers.erase(it->second);
        m_timers_lookup.erase(it);
    }
    else
    {
        qDebug() << "unsetTimersFailed : "
                 << " event: " << unset_timer.m_event
                 << " sm: " << unset_timer.m_state_machine ;
        Q_ASSERT( false );
    }
}

void QTimerInterface::cancel()
{
    for (callback_reverse_map_type::iterator it = m_timers_lookup.begin();
            it != m_timers_lookup.end(); it++)
    {
        killTimer(it->second);
    }
    m_timers.clear();
    m_timers_lookup.clear();
}
