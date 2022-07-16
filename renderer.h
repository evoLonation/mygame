#pragma once
#include <GLEW/glew.h>
#include<SDL/SDL.h>

class Renderer{
   public:
   void Init();
   void Finalize();
   // void addModel();
   void DoDraw();

   SDL_Window* window;
   private:
   SDL_GLContext context;

   // init sub-process
   void CreateGLContext();
   void GlewInit();

};