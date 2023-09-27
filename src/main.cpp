#include <memory>
#include "game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
    std::unique_ptr<Game> game(new Game(SCREEN_WIDTH, SCREEN_HEIGHT));
    return 0;
}