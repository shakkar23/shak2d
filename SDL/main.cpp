// pong.cpp : Defines the entry point for the application.
//

#include "main.hpp"

void pressKey(SDL_Scancode scan, moveDirection &player) {
    if (scan == SDL_Scancode::SDL_SCANCODE_W)
        player.Up = true;
    else if (scan == SDL_Scancode::SDL_SCANCODE_S)
        player.Down = true;
    else if (scan == SDL_Scancode::SDL_SCANCODE_A)
        player.Left = true;
	else if (scan == SDL_Scancode::SDL_SCANCODE_D) 
		player.Right = true;
    else if(scan == SDL_Scancode::SDL_SCANCODE_SPACE)
		player.Jump = true;
}

void unpressKey(SDL_Scancode scan, moveDirection& player) {
    if (scan == SDL_Scancode::SDL_SCANCODE_W)
    {
            player.Up = false;
    }
    else if (scan == SDL_Scancode::SDL_SCANCODE_S)
    {
            player.Down = false;
    }
    else if (scan == SDL_Scancode::SDL_SCANCODE_A)
    {
            player.Left = false;
    }
    else if (scan == SDL_Scancode::SDL_SCANCODE_D)
    {
            player.Right = false;
    }
    else if (scan == SDL_Scancode::SDL_SCANCODE_SPACE)
    {
        player.Jump = false;
    }
    else if (scan == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
    exit(0);
    }
}


int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
        // printf("HEY.. SDL_Init HAS FAILED. SDL_ERROR: %s", SDL_GetError());
	
    RenderWindow window("Shak2D", 720, 720);
    GameManager.Init(window);
    bool gameRunning = true;
    SDL_Event event;

    // rendering constantly, and not actually displaying causes memory to stack higher and higher until the frames can be shown
    bool shouldDisplay = true; 

    double alpha = 0.0;
    Uint64 last_time = SDL_GetPerformanceCounter();
    //Uint64 ticks = 0;
    moveDirection player;
    moveDirection prevplayer;
    //Uint8 lastEvent = 0;
	
    while (gameRunning) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_NONE:
                    break;
                case SDL_WINDOWEVENT_SHOWN:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    shouldDisplay = false;
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    shouldDisplay = false;
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_TAKE_FOCUS:
                    //shouldDisplay = true;
                    break;
                case SDL_WINDOWEVENT_HIT_TEST:
                    //shouldDisplay = true;
                    break;
                default:
                    break;
                }
                //if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                //    shouldDisplay = false;
                //}
                //else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                //    ;
                //}
                //else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                //    shouldDisplay = false;
                //}
                //else if (event.window.event == SDL_WINDOWEVENT_TAKE_FOCUS)
                //    shouldDisplay = true;
                //else shouldDisplay = true;
            }
            else if ((event.key.type == SDL_KEYDOWN) || (event.key.type == SDL_KEYUP)) {
                if (event.key.state == SDL_PRESSED) {
                    if (event.key.repeat)
                        continue;
                    pressKey(event.key.keysym.scancode, player);
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        gameRunning = false; break;
                    }
                }
                else {
                    unpressKey(event.key.keysym.scancode, player);
                }
            }
            else if (event.type == SDL_QUIT)
                gameRunning = false;

        }

        if (shouldDisplay) { // skip frames that cant be shown due to window not currently accepting frames to display

            constexpr bool highPerformanceMode = true;
            if (highPerformanceMode) {
                const auto now = SDL_GetPerformanceCounter();
                alpha += (double)((double)(now - last_time) / SDL_GetPerformanceFrequency() * UPDATES_A_SECOND);
                last_time = now;

                while (alpha > 1.0) {
                    GameManager.gameLogic(prevplayer, player);
                    prevplayer = player;

                    alpha -= 1;
                }
                if (gameRunning) {
                    GameManager.render(window);
                }
                else {
                    gameRunning = false;
                }

            }
            else {
                constexpr int FRAME_RATE = (int)((1.0 / 60.0) * UPDATES_A_SECOND); // time spent in a frame in ms
                int32_t ticks = SDL_GetTicks() % (FRAME_RATE);
                if ((ticks) == 0) {
                    GameManager.gameLogic(prevplayer, player);
                    prevplayer = player;
                    GameManager.render(window);
                }
                else {
                    SDL_Delay((Uint32)std::abs((int)(ticks - FRAME_RATE)) + 1);
                    GameManager.gameLogic(prevplayer, player);
                    prevplayer = player;
                    GameManager.render(window);
                }
            }

        }
        else {
            const auto now = SDL_GetPerformanceCounter();
            alpha = 0;
            last_time = now;
        }
        //window.display();
    }

    window.cleanUp();
    SDL_Quit();
	//std::cin.get();
	return 0;
}
