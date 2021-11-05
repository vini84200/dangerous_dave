#include "time_utils.h"
#include "time.h"

long calcDiffNanoseconds(struct timespec *now, struct timespec *lastNow) {
    long dns = (*now).tv_nsec - (*lastNow).tv_nsec;

    // Verifica se um segundo passou
    if (dns < 0) {
        dns += 1000000000;
    }

    return dns;
}