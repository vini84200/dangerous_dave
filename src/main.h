#pragma once

#include <time.h>

#include "core.h"
#include "utils/erros.h"
#include "controller/AppStateMachine.h"


int main();

void setup_ncurses();

void executarASM(struct AppStateMachine *maquinaEstados, struct timespec *now, struct timespec *lastNow);
