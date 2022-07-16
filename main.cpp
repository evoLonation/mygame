#include<iostream>
#define GLEW_STATIC
#include <GLEW/glew.h>
#pragma comment(lib, "glew32s.lib")
// #include"GL/glew.h"
#include<SDL/SDL.h>

int main(int argv, char** args){
   SDL_Window* mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 5)", 100, 100,
							   1024, 768, SDL_WINDOW_OPENGL);
   SDL_GLContext mContext;
   glewExperimental = GL_TRUE;
   mContext = SDL_GL_CreateContext(mWindow);
   if(glewInit() != GLEW_OK){
      printf("filed!");
      return 0;
   }
   // glGetError();
   double t = 0.0;
   while (1)
   {

      glClearColor(0.5, 0.5 + t, 0.5 + t, 1.0);
      t += 0.001;
      glClear(GL_COLOR_BUFFER_BIT);
      SDL_GL_SwapWindow(mWindow);
   }
   
}