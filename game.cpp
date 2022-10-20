//
//  game.cpp
//  Incogine
//
//  Created by moritz on 10/17/22.
//

#include "game.hpp"

Game::Game() {
    // Initialize Game
    Console console;
    console.Println("Game initialized successfully");
}

Game::~Game() {
    // Purge Game
    Console console;
    console.Println("Game purged successfully");
}

float playerx = 50, playery = 50, speed = 5;
const Uint8 *_Pkeyboard = SDL_GetKeyboardState(0);


void Game::RawEvent(SDL_Event event, int _windowWidth, int _windowHeight) {
    // Events (Keyboard, Mouse, etc.)
    Console console;
    
    // Type-Style KeyDown (Hold Key)
    if (_Pkeyboard[SDL_SCANCODE_D]) {
        // Pressed
        playerx += speed;
    } else {
        // Released
    }
    
    if (_Pkeyboard[SDL_SCANCODE_A]) {
       // Pressed
        console.Println("Type Style Left Key Pressed");
        playerx -= speed;
    } else {
        // Released
    }

    if (_Pkeyboard[SDL_SCANCODE_W]) {
        // Pressed
        playery -= speed;
    } else {
        // Released
    }
    
    if (_Pkeyboard[SDL_SCANCODE_S]) {
        // Pressed
        playery += speed;
    } else {
        // Released
    }
}

void Game::Event(SDL_Event event) {
    Console console;
    
    // Quit
    if(event.type == SDL_QUIT) {
        Core::corerunning = false;
    }
    
    // KeyUp and KeyDown
    // Pressed
    if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym){
        case SDLK_LEFT:
            console.Println("Left Key Pressed");
            break;
        case SDLK_r:
            playery = 50;
            playerx = 50;
            break;
        }
    }
    // Released
    if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_LEFT:
                console.Println("Left Key Lifted");
                break;
        }
    }
}

void Game::Start() {
    // Executes as game launches
    Console console;
}

void Game::Update(int _windowWidth, int _windowHeight) {
    // Executes every frame at game
}

//SDL_Rect _whatsoeva_position;
//SDL_Color _whatsoeva_color;
//Fonts *whatsoeva;

void Game::Render() {
    // Render Game
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    /*_whatsoeva_color.r = 255;
    _whatsoeva_color.g = 255;
    _whatsoeva_color.b = 255;
    _whatsoeva_color.a = 255;
    _whatsoeva_position.x = 0;
    _whatsoeva_position.y = 0;
    whatsoeva->RenderFont("What", &_whatsoeva_position, _whatsoeva_color);*/
    
    glPushMatrix();
    glTranslated(playerx, playery, 0);
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2f(0, 0);
        glVertex2f(50, 0);
        glVertex2f(50, 50);
        glVertex2f(0, 50);
    glEnd();
    glPopMatrix();
}
