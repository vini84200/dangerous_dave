#include <stdio.h>
#include "Timer.h"

void getTimerText(float timer, char *out) {
    // Duração visível
    if (getHours(timer) != 0) {
        sprintf(out, "%02d:%02d:%02d.%03dms",
                getHours(timer),
                getMinutes(timer),
                getSeconds(timer),
                getMSeconds(timer));
    } else {
        sprintf(out, "%02d:%02d.%03dms",
                getMinutes(timer),
                getSeconds(timer),
                getMSeconds(timer));
    }
}

int getHours(float timer) {
    return (int) (timer / 3600);
}

int getMinutes(float timer) {
    return (int) (timer / MINUTE) % (HOUR / MINUTE);
}

int getSeconds(float timer) {
    return (int) (timer / SECOND) % (MINUTE / SECOND);
}

int getMSeconds(float timer) {
    return (int) (timer * 1000) % 1000;
}

void textSerializeTimer(float timer, char *out) {
    if (getHours(timer) > 99) {
        sprintf(out, "PT%02dH%02dM%02d.%03dS",
                99,
                getMinutes(timer),
                getSeconds(timer),
                getMSeconds(timer));
    }
    sprintf(out, "PT%02dH%02dM%02d.%03dS",
            getHours(timer),
            getMinutes(timer),
            getSeconds(timer),
            getMSeconds(timer));
}

void textDeserializeTimer(const char *text, float *timerOut) {

}


