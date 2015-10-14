#include "QTimerInterface.h"
#include "TimedStatemachineInterface.h"
#include <QTimerEvent>

#include <QDebug>

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

    int qt_timer = startTimer(time_ms);
    CallbackInfo callback_info =
    { statemachine, event, isPeriodic };

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
            it->m_state_machine->raiseTimeEvent(it->m_event);
            // stop the timer if it's not periodic
            if (!(it->m_periodic))
            {
                killTimer(event->timerId());
                m_timers_lookup.remove(*it);
                m_timers.erase(it);
            }
            emit timeout();
        }
    }
}

void QTimerInterface::unsetTimer(TimedStatemachineInterface* statemachine,
        sc_eventid event)
{
    CallbackInfo unset_timer =
    { statemachine, event, false };

    callback_reverse_map_type::iterator it = m_timers_lookup.find(unset_timer);
    if (it != m_timers_lookup.end())
    {
        killTimer(*it);
        m_timers.remove(*it);
        m_timers_lookup.erase(it);
    }
}

void QTimerInterface::cancel()
{
    for (callback_map_type::iterator it = m_timers.begin();
            it != m_timers.end(); it++)
    {
        killTimer(it.key());
    }
    m_timers.clear();
    m_timers_lookup.clear();
}
