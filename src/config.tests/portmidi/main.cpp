extern "C" {
#include <portmidi.h>
}

int main()
{
    return Pm_CountDevices();
}
