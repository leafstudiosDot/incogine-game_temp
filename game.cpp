//
//  game.cpp
//  Incogine
//
//  Created by moritz on 10/17/22.
//

#include "game.hpp"

TTF_Font *font;
int p_windowWidth;
int p_windowHeight;

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

float playerx = 0.0f, playery = 0.0f, speed = 0.05f;
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
        playery += speed;
    } else {
        // Released
    }
    
    if (_Pkeyboard[SDL_SCANCODE_S]) {
        // Pressed
        playery -= speed;
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
            playery = 0;
            playerx = 0;
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
    const char fontFile[] = "../Resources/fonts/def_font.ttf";
    
    if(!(font = TTF_OpenFont(fontFile, 100))) {
        printf("Error loading font: %s", TTF_GetError());
    }
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void Game::Update(int _windowWidth, int _windowHeight) {
    // Executes every frame at game
    p_windowWidth = _windowWidth;
    p_windowHeight = _windowHeight;
}

SDL_Color _whatsoeva_color;
Fonts *whatsoeva;

Fonts *renderdebug_position2;

void Game::Render() {
    // Render Game
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(playerx, 0.0f, (playery*(-1)), playerx, 0.0f, -100, 0, 1, 0);
    
    glPushMatrix();
    glTranslated(-11.0f, 0.0f, -10.0f);
    _whatsoeva_color.r = 255;
    _whatsoeva_color.g = 255;
    _whatsoeva_color.b = 255;
    _whatsoeva_color.a = 100;
    whatsoeva->RenderFont(font, "Welcome", 5.0f, 0, 0, _whatsoeva_color, 3.0f, 1.0f);
    glPopMatrix();
    
    // Debug Point
    //const char* deb = (char)playerx + ", " + (char)playery;
    //renderdebug_position2->RenderFont(font, "", 0, 0, 0, {255, 255, 255, 255}, 0.25f, 0.2f);
    cout << "X: " << playerx << " Y: " << playery << endl;
    glPushMatrix();
    glTranslated(0, 3.0f, 0);
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 255);
        glVertex2f(0, 0);
        glVertex2f(0.05f, 0);
        glVertex2f(0.05f, 0.05f);
        glVertex2f(0, 0.05f);
    glEnd();
    glPopMatrix();
}

void Game::Destroy() {
    TTF_CloseFont(font);
}
