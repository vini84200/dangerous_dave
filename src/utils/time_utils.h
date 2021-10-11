#pragma once

#include <time.h>

// Calcula a diferença entre do
long calcDiffNanoseconds(struct timespec *now, struct timespec *lastNow);