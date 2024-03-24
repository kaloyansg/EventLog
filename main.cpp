#include <iostream>
#include <fstream>
#include "Event.h"
#include "EventLog.h"

int main()
{
    EventLog log;
    log.addEvent(Event("Mama", 12, 2, 2025, 23, 33));
    log.addEvent(Event("Bababa", 15, 4, 2333, 3, 11));
    log.addEvent(Event("Papapapa", 11, 11, 2111, 11, 11));

    std::ofstream writer("eventLogBin.dat", std::ios::binary);
    log.saveAsBin(writer);
    writer.close();

    std::ifstream reader("eventLogBin.dat", std::ios::binary);

    if (!reader)
    {
        std::cerr << "File could not be loaded";
    }
    else
    {
        EventLog logCopy;
        logCopy.getFromBin(reader);
        logCopy.print();
    }

    reader.close();
}