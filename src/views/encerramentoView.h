#pragma once

#include "../core.h"
#include "../models/Encerramento.h"
#include "../models/ranking.h"

void viewEncerramento(struct Encerramento *self);

bool handleInputEncerramento(struct Encerramento *self, int ch);

void enter_encerramento(struct Encerramento *self);