#pragma once
#include <cstdio>
#include "screen.h"

class Game {
public:
    Game();
    ~Game();

    void helloWorld();
    static void loopPrincipal();
    bool isRunning();

private:
    bool _running;
    Screen screen;
};
