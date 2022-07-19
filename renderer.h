#pragma once

// use to choose nvidia card
#include<windows.h>
#ifdef __giao2
#ifdef __giao
extern "C" {
#endif

__declspec(dllexport) DWORD NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __giao
}
#endif
#endif
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