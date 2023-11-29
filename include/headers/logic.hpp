#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>

enum class GameState{PLAY,EXIT};
enum class Colision{P1,P2}; // P = PLAYER

class Pong{
    public:
        Pong(const char* title, int x, int y, int w, int h, Uint32 flags);
        GameState gameState;
        Colision colision;
        SDL_Rect player1;
        SDL_Rect player2;
        SDL_Rect img;
        SDL_Rect letter;
        SDL_Rect divider;
        SDL_Rect ball;
        SDL_Texture* loadText(const char* filePath);
        float angleY;
        float randAngle();
        void isPressed(SDL_Keycode key);
        void isReleased(SDL_Keycode key);
        void renderLetter(SDL_Texture* texture);
        void renderText(SDL_Texture* texture);
        void decimals(int aux,int num,int score, SDL_Texture* texture);
        void ballDirection(int WIDTH,int HEIGHT);
        void renderPlayer(int WIDTH, int HEIGHT);
        void handleEvents(int WIDTH, int HEIGHT);
        void run();

    private:
        void clear();
        void display();
        void cleanUp();

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* screenSurface;

        int player1X;
        float player1Y;
        int player1W;
        int player1H;
        int scoreP1;
        bool P1Up;
        bool P1Down;

        int player2X;
        float player2Y;
        int player2W;
        int player2H;
        int scoreP2;
        bool P2Up;
        bool P2Down;

        int imgX;
        int imgY;
        int imgW;
        int imgH;

        int letterX;
        int letterY;
        int letterW;
        int letterH;

        int dividerX;
        int dividerY;
        int dividerW;
        int dividerH;

        float ballX;
        float ballY;
        float ballW;
        float ballH;
        float ballVelocity;
};