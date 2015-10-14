#ifndef QTIMERINTERFACE_H_
#define QTIMERINTERFACE_H_

#include <QObject>
#include <QMap>

#include "TimerInterface.h"

class QTimerInterface: public QObject, public TimerInterface
{
        Q_OBJECT;

    public:
        QTimerInterface(QObject* parent);
        virtual ~QTimerInterface();
        virtual void setTimer(TimedStatemachineInterface* statemachine,
                sc_eventid event, sc_integer time, sc_boolean isPeriodic);
        virtual void unsetTimer(TimedStatemachineInterface* statemachine,
                sc_eventid event);
        virtual void cancel();
        void timerEvent(QTimerEvent *event);

    signals:
        void timeout();

    private:
        struct CallbackInfo
        {
                TimedStatemachineInterface* m_state_machine;
                sc_eventid m_event;
                sc_boolean m_periodic;

                bool operator==(const CallbackInfo& rhs) const
                {
                    return m_state_machine == rhs.m_state_machine
                            && m_event == rhs.m_event;
                }
                bool operator<(const CallbackInfo& rhs) const
                {
                    return m_event < rhs.m_event
                            && m_state_machine < rhs.m_state_machine;
                }
        };
        typedef QMap<int, CallbackInfo> callback_map_type;
        typedef QMap<CallbackInfo, int> callback_reverse_map_type;
        callback_map_type m_timers;
        callback_reverse_map_type m_timers_lookup;

};

#endif /* QTIMERINTERFACE_H_ */
