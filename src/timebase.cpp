#include "timebase.h"
#include <QElapsedTimer>

static QElapsedTimer timer;

void initializeTimebase()
{
    timer.start();
}

unsigned long now()
{
    return timer.elapsed();
}
