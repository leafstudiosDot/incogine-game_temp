//
//  game.cpp
//  Incogine
//
//  Created by moritz on 10/17/22.
//

#include "game.hpp"

TTF_Font *font;

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
    const char fontFile[] = "./def_font.ttf";
    
    if(!(font = TTF_OpenFont(fontFile, 20))) {
        printf("Error loading font: %s", TTF_GetError());
    }
}

void Game::Update(int _windowWidth, int _windowHeight) {
    // Executes every frame at game
}

SDL_Rect _whatsoeva_position;
SDL_Color _whatsoeva_color;
Fonts *whatsoeva;

void Game::Render() {
    // Render Game
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // 3D Game
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
    
    // HUD Mode
    // Enable
    int vPort[4];
    glGetIntegerv(GL_VIEWPORT, vPort);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    // End Enable
    
    _whatsoeva_color.r = 255;
    _whatsoeva_color.g = 255;
    _whatsoeva_color.b = 255;
    _whatsoeva_color.a = 255;
    _whatsoeva_position.x = 50;
    _whatsoeva_position.y = 50;
    whatsoeva->RenderFont(font, "W", &_whatsoeva_position, _whatsoeva_color);
    
    // Disable
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    // End Disable
}

void Game::Destroy() {
    TTF_CloseFont(font);
}
