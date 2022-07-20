#pragma once

#include"opengl/basic.h"
#include "Math.h"



class Actor;

class Renderer{
   public:
   void Init();
   void Finalize();
   void AddActor(Actor &actor);
   void DeleteActor(int index);
   void DoDraw();

   private:
   SDL_Window* window;
   SDL_GLContext context;

   // set shader
   GLuint programId;
   // void ShaderProgramInit();

   std::vector<Actor*> actorList;
   Matrix4 viewProj;

};