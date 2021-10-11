//
// Created by vini84200 on 10/10/2021.
//
#include "time_utils.h"
#include "time.h"

long calcDiffNanoseconds(struct timespec *now, struct timespec *lastNow) {
    long dns = (*now).tv_nsec - (*lastNow).tv_nsec;
    double ds = difftime((*now).tv_sec, (*lastNow).tv_sec);


    if (dns < 0) {
        ds -= 1;
        dns += 1000000000;
    }

    return dns;
}