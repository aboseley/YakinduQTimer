#ifndef _StateChartDriver_h
#define _StateChartDriver_h
#include "DefaultStateChartDriver.h"

#include <QObject>

class Default;

class DefaultStateChartDriver: public QObject
{
        Q_OBJECT

    public:
        DefaultStateChartDriver( QObject * parent, Default* sc);
        virtual ~DefaultStateChartDriver();

    public slots:
        void onStateChartCycle();

    private:
        Default* m_sc;
};

#endif /* QDEFAULT_H_ */
