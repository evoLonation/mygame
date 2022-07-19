#pragma once
#include <GLEW/glew.h>
#include<SDL/SDL.h>

/**
 * this function do following job:
 * set GL attribute
 * create a sdl window
 * create a gl context
 */
void CreateGLContext(SDL_Window*& window, SDL_GLContext& context);

void GlewInit();