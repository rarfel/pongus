#include <headers/logic.hpp>

int main(int argc, char* argv[])
{
    int WIDTH = 720;
    int HEIGHT = 480;

    Pong pong("PONGUS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Texture* text = pong.loadText("fonts/font.png");

    while(pong.gameState != GameState::EXIT)
    {
        pong.handleEvents(WIDTH, HEIGHT);
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            pong.gameState = GameState::EXIT;
            break;
        }
        pong.ballDirection(WIDTH,HEIGHT);
        pong.renderPlayer(WIDTH,HEIGHT);
        pong.renderText(text);
        pong.run();
    }

    return 0;
}