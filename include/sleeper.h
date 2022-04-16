#ifndef SLEEPER_H
#define SLEEPER_H

#include <QDebug>
#include <QThread>

class Sleeper {
  public:
    static void usleep (unsigned long usecs) {QThread :: usleep (usecs);}
    static void msleep (unsigned long msecs) {QThread :: msleep (msecs);}
    static void sleep (unsigned long secs) {QThread :: sleep (secs);}
};

#endif
