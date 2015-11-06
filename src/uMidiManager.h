#ifndef UMIDIMANAGER_H
#define UMIDIMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMap>

class UMidiManager : public QObject
{

    Q_OBJECT

signals:

    void  noteOnEvent(ulong, int);
    void  noteOffEvent(ulong, int);

public:

    static UMidiManager *getInstance();

protected:

    static UMidiManager *Instance;

    UMidiManager();
    virtual ~UMidiManager();

private slots:

    void checkForEvents();

private:

    bool _initialized;
    QMap<int, void *> _streams;
    QTimer _timer;

};

#endif // UMIDIMANAGER_H
