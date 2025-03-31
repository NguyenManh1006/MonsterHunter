#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED

#include "CommonFunction.h"

class ImpTimer {
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();
    bool is_paused();
    bool is_started();

private:
    int start_tick_;
    int pause_tick_;

    bool is_paused_;
    bool is_started_;
};

#endif // IMPTIMER_H_INCLUDED
