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

bool is3D = true;

float playerx = 0.0f, playery = 0.0f, speed = 0.05f;
float hudx = 0.0f, hudy = 0.0f;
float camx = 0.0f, camy = 0.0f, camsensitivity = 0.05f;
float angle = 0.0f;

const Uint8 *_Pkeyboard = SDL_GetKeyboardState(0);


void Game::RawEvent(SDL_Event event, int _windowWidth, int _windowHeight) {
    // Events (Keyboard, Mouse, etc.)
    Console console;
    if (!is3D) {
        // 2D Controls
        // Type-Style KeyDown (Hold Key)
        if (_Pkeyboard[SDL_SCANCODE_D]) {
            // Pressed
            playerx += speed;
        } else {
            // Released
        }
        
        if (_Pkeyboard[SDL_SCANCODE_A]) {
            // Pressed
            //console.Println("Type Style Left Key Pressed");
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
    } else {
    // Disable if using 2D
        if (_Pkeyboard[SDL_SCANCODE_UP]) {
            hudy -= 5;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_DOWN]) {
            hudy += 5;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_LEFT]) {
            /*angle -= camsensitivity;
            camx = sin(angle);
            camy = -cos(angle);*/
            hudx -= 3;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_RIGHT]) {
            /*angle += camsensitivity;
            camx = sin(angle);
            camy = -cos(angle);*/
            hudx += 3;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_W]) {
            playerx += camx * speed;
            playery -= camy * speed;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_S]) {
            playerx -= camx * speed;
            playery += camy * speed;
        } else {
            
        }
        
        if (_Pkeyboard[SDL_SCANCODE_D]) {
            // Pressed
            playerx -= (camy * speed);
            playery -= (camx * speed);
        } else {
            // Released
        }
        
        if (_Pkeyboard[SDL_SCANCODE_A]) {
            // Pressed
            playerx += (camy * speed);
            playery += (camx * speed);
        } else {
            // Released
        }
    }
}

void Game::Event(SDL_Event event, int _windowWidth, int _windowHeight) {
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
            //console.Println("Left Key Pressed");
            break;
        case SDLK_r:
            playery = 0;
            playerx = 0;
            camy = 0;
            camx = 0;
            angle = 0;
            console.Println("Engine reset successfully");
            break;
        }
    }
    // Released
    if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
            case SDLK_LEFT:
                //console.Println("Left Key Lifted");
                break;
        }
    }
    
    // Mouse
    if (event.type == SDL_MOUSEMOTION) {
        int mouseposx = event.motion.xrel, mouseposy = event.motion.yrel;
        if (is3D) {
            if (mouseposx < 1) {
                angle -= mouseposx * (camsensitivity - 0.04f);
                camx = sin(angle);
                camy = -cos(angle);
            } else {
                angle += (mouseposx * (camsensitivity - 0.04f))*(-1);
                camx = sin(angle);
                camy = -cos(angle);
            }
        }
    }
}

void Game::Start(int _windowWidth, int _windowHeight) {
    // Executes as game launches
    Console console;
    #if __APPLE__
    const char fontFile[] = "../Resources/fonts/def_font.ttf";
    #elif EMSCRIPTEN
    const char fontFile[] = "/assets/fonts/def_font.ttf";
    #endif
    
    if(!(font = TTF_OpenFont(fontFile, 100))) {
        printf("Error loading font: %s", TTF_GetError());
    }
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    
    camx = sin(angle);
    camy = -cos(angle);
    
    if (is3D) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
}

void Game::Update(int _windowWidth, int _windowHeight) {
    // Executes every frame at game
    p_windowWidth = _windowWidth;
    p_windowHeight = _windowHeight;
}

SDL_Color _whatsoeva_color;
Fonts *whatsoeva;

Fonts *renderdebug_position2;

void Game::Render(int _windowWidth, int _windowHeight) {
    // Render Game
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (is3D) {
        // Use in 3D Camera Movement (First Person)
        gluLookAt(playerx, 0.0f, (playery*(-1)), playerx+camx, 0.0f, (playery*(-1))+camy, 0, 1, 0);
    } else {
        // Use in 2D Camera Movement (Top Down)
        gluLookAt((playerx*(-1)), (playery*(-1)), 0.0f, (playerx*(-1)), (playery*(-1)), -100, 0, 1, 0);
    }
    
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
    //cout << "X: " << playerx << " Y: " << playery << endl;
    //cout << "CamX: " << camx << " CamY: " << camy << endl;
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

SDL_Color _whatsoeva_hud_color;
Fonts *whatsoeva_hud;

void Game::RenderCanvas(int _windowWidth, int _windowHeight) {
    // Render HUD
    glPushMatrix();
    glTranslatef(hudx, hudy, 0);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
        glVertex2f(10.0, 10.0);
        glVertex2f(0.0, 10.0);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(hudx, hudy, 0);
    _whatsoeva_hud_color.r = 255;
    _whatsoeva_hud_color.g = 255;
    _whatsoeva_hud_color.b = 255;
    _whatsoeva_hud_color.a = 100;
    whatsoeva_hud->RenderFontHUD(font, "Hud Font", 40.0f, 90.0f, 0.0f, _whatsoeva_hud_color, 230.0f, -70.0f, hudx);
    glPopMatrix();
}

void Game::Destroy() {
    // Destroy Game
    TTF_CloseFont(font);
}
