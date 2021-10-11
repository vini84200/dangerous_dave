//
// Created by vini84200 on 26/09/2021.
//
#pragma once

#include "../core.h"

struct Vec2Int {
    int x;
    int y;
};

struct Vec2Int add(struct Vec2Int a, struct Vec2Int b);

struct Vec2Int sub(struct Vec2Int a, struct Vec2Int b);

bool equalVec(struct Vec2Int a, struct Vec2Int b);