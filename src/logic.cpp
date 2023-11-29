#include <headers/logic.hpp>

Pong::Pong(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title,x,y,w,h,flags);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    screenSurface = SDL_GetWindowSurface(window);

    Pong::colision = Colision::P2;
    angleY = 0.2;

    player1X = 100;
    player1Y = h/2 - 60;
    player1W = 15;
    player1H = 60;
    scoreP1 = 0;
    P1Up = false;
    P1Down = false;

    player2X = w - 115; // 155 = distancia do lado direito para a raquete - largura da raquete
    player2Y = h/2 - 60;
    player2W = 15;
    player2H = 60;
    scoreP2 = 0;
    P2Up = false;
    P2Down = false;

    dividerX = w/2;
    dividerY = 0;
    dividerW = 5;
    dividerH = h;

    imgX = 0;
    imgY = 0;
    imgW = 5;
    imgH = 7;
    
    letterX = 0;
    letterY = 0;
    letterW = 35;
    letterH = 56;

    ballX = w/2;
    ballY = h/2;
    ballW = 10;
    ballH = 10;
    ballVelocity = 0.1;
};

void Pong::run()
{
    display();
    clear();
}

SDL_Texture* Pong::loadText(const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,filePath);

    if(texture == NULL)
    {
        std::cout << "sem texto: " << filePath << " Error: " << SDL_GetError() << '\n';

        return texture;
    }
}

void Pong::renderLetter(SDL_Texture* texture)
{
    img.x = imgX;
    img.y = imgY;
    img.w = imgW;
    img.h = imgH;

    letter.x = letterX;
    letter.y = letterY;
    letter.w = letterW;
    letter.h = letterH;

    SDL_RenderCopy(renderer, texture, &img, &letter);
}

void Pong::decimals(int aux,int num,int score, SDL_Texture* texture){
    imgX = aux * 5;
	imgY = 14;
	letterX = letterW * (num - 1);
	renderLetter(texture);
	imgX = (score - (aux*10))* 5;
	letterX = letterW * num;
	renderLetter(texture);
}

void Pong::renderText(SDL_Texture* texture)
{
    imgX = 10;
    imgY = 7;
    letterX = letterW * 8 + 12;
    renderLetter(texture);
    imgX = 5;
    imgY = 7;
    letterX = letterW * 9 + 12;
    renderLetter(texture);
    imgX = 0;
    imgY = 7;
    letterX = letterW * 10 + 12;
    renderLetter(texture);
    imgX = 30;
    imgY = 0;
    letterX = letterW * 11 + 12;
    renderLetter(texture);

    imgX = scoreP1  * 5;
    imgY = 14;
    letterX = letterW * 1;
    renderLetter(texture);
    if(scoreP1 > 9){
        decimals(1,1,scoreP1,texture);
    }
    if(scoreP1 > 19){
        decimals(2,1,scoreP1,texture);
    }
    if(scoreP1 > 29){
        decimals(3,1,scoreP1,texture);
    }
    if(scoreP1 > 39){
        decimals(4,1,scoreP1,texture);
    }
    if(scoreP1 > 49){
        decimals(5,1,scoreP1,texture);
    }
    if(scoreP1 > 59){
        decimals(6,1,scoreP1,texture);
    }
    if(scoreP1 > 69){
        decimals(7,1,scoreP1,texture);
    }
    if(scoreP1 > 79){
        decimals(8,1,scoreP1,texture);
    }
    if(scoreP1 > 89){
        decimals(9,1,scoreP1,texture);
    }
    
    imgX = scoreP2 * 5;
    imgY = 14;
    letterX = letterW * 18 + 20;
    renderLetter(texture);
    if(scoreP2 > 9){
        decimals(1,19,scoreP2,texture);
    }
    if(scoreP2 > 19){
        decimals(2,19,scoreP2,texture);
    }
    if(scoreP2 > 29){
        decimals(3,19,scoreP2,texture);
    }
    if(scoreP2 > 39){
        decimals(4,19,scoreP2,texture);
    }
    if(scoreP2 > 49){
        decimals(5,19,scoreP2,texture);
    }
    if(scoreP2 > 59){
        decimals(6,19,scoreP2,texture);
    }
    if(scoreP2 > 69){
        decimals(7,19,scoreP2,texture);
    }
    if(scoreP2 > 79){
        decimals(8,19,scoreP2,texture);
    }
    if(scoreP2 > 89){
        decimals(9,19,scoreP2,texture);
    }
}

void Pong::renderPlayer(int WIDTH, int HEIGHT)
{
    player1.x = player1X;
    player1.y = player1Y;
    player1.w = player1W;
    player1.h = player1H;

    player2.x = player2X;
    player2.y = player2Y;
    player2.w = player2W;
    player2.h = player2H;

    divider.x = dividerX;
    divider.y = dividerY;
    divider.w = dividerW;
    divider.h = dividerH;

    ball.x = ballX;
    ball.y = ballY;
    ball.w = ballW;
    ball.h = ballH;

    SDL_SetRenderDrawColor(renderer,0,0,50,255);
    clear();
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &player1);
    SDL_RenderFillRect(renderer, &player2);
    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &divider);
}

void Pong::isPressed(SDL_Keycode key)
{
    switch (key)
        {
        case SDLK_w:
            P1Up = true;
            break;
        case SDLK_s:
            P1Down = true;
            break;
        case SDLK_UP:
            P2Up = true;
            break;
        case SDLK_DOWN:
            P2Down = true;
            break;
        }
}

void Pong::isReleased(SDL_Keycode key)
{
    switch (key)
        {
        case SDLK_w:
            P1Up = false;
            break;
        case SDLK_s:
            P1Down = false;
            break;
        case SDLK_UP:
            P2Up = false;
            break;
        case SDLK_DOWN:
            P2Down = false;
            break;
        }
}

void Pong::handleEvents(int WIDTH, int HEIGHT)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_KEYDOWN:
        isPressed(event.key.keysym.sym);
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            ballVelocity = 0.25;
            break;
        }
        break;
    case SDL_KEYUP:
        isReleased(event.key.keysym.sym);
        break;
    }

    if(P1Up == true)
    {
        player1Y -= 0.5;
        if(player1Y <= 0)
        {
            player1Y = 0;
        }
    }
    if(P1Down == true)
    {
        player1Y += 0.5;
        if (player1Y >= HEIGHT- player1H) //  Height == 480
        {
            player1Y = HEIGHT - player1H; //  Height == 480
        }
    }
    if(P2Up == true)
    {
        player2Y -= 0.5;
        if(player2Y <= 0)
        {
            player2Y = 0;
        }
    }
    if(P2Down == true)
    {
        player2Y += 0.5;
        if (player2Y >= HEIGHT- player2H) //  Height == 480
        {
            player2Y = HEIGHT - player2H; //  Height == 480
        }
    }
}

float Pong::randAngle()
{
    return (float)(rand())/ (float)(0xffff);
}

void Pong::ballDirection(int WIDTH, int HEIGHT)
{
    switch (Pong::colision)
    {
    case Colision::P2:
        ballX -=ballVelocity;
        ballY += angleY;
        if(ballX < player1X and ballX > player1X - player1W and player1Y <= ballY and (player1Y + player1H - 10) >= ballY)
        {
            angleY = randAngle();
            Pong::colision = Colision::P1;
        }
        break;
    case Colision::P1:
        ballX +=ballVelocity;
        ballY += angleY;
        if(ballX > player2X and ballX < player2X + player2W and player2Y <= ballY and (player2Y + player2H - 10) >= ballY)
        {
            angleY = randAngle();
            Pong::colision = Colision::P2;
        }
        break;
    }
    if(ballX >= WIDTH)
    {
        scoreP1 += 1;
        ballX = WIDTH/2;
        ballY = HEIGHT/2;
    }
    if(ballX <= 0)
    {
        scoreP2 += 1;
        ballX = WIDTH/2;
        ballY = HEIGHT/2;
    }
    if (ballY <= 0 or ballY >= HEIGHT - ballH)
    {
        float aux = -1;
        angleY = angleY * aux;
    }
}

void Pong::display()
{
    SDL_RenderPresent(renderer);
}

void Pong::clear()
{
    SDL_RenderClear(renderer);
}

void Pong::cleanUp()
{
    SDL_DestroyWindow(window);
}