#include"renderer.h"
#include "opengl/basic.h"
#include<vector>
#include "actor.h"
#include "Math.h"

void Renderer::Init(){
   OpenGLInit(window, context);
   programId = BuildProgram();
   viewProj = Matrix4::CreateSimpleViewProj(1024, 768);

   glUseProgram(programId);
   glUniformMatrix4fv(glGetUniformLocation(programId, "viewProj"), 1, GL_TRUE, viewProj.GetAsFloatPtr());

}

void Renderer::Finalize(){
   //finalize
   //destroy GL context
   SDL_GL_DeleteContext(context);

   // delete program
   glDeleteProgram(programId);
}



void Renderer::AddActor(Actor &actor){
   actorList.push_back(&actor);
}
void Renderer::DeleteActor(int index){
   // unimplement
}



void Renderer::DoDraw(){
   glClearColor(0.5, 1.0, 1.0, 1.0);
   //clear thr color buffer using clear color 
   glClear(GL_COLOR_BUFFER_BIT);
   for(auto actor : actorList){
      glBindVertexArray(actor->getVAOId());
      glUniformMatrix4fv(glGetUniformLocation(programId, "worldTransfrom"), 1, GL_TRUE, actor->getWorldTrans()->GetAsFloatPtr());
      glDrawElements(GL_TRIANGLES, actor->model->indexNumber, GL_UNSIGNED_INT, nullptr);
   }
   SDL_GL_SwapWindow(window);

}

// use to choose nvidia card
#include<windows.h>
#ifdef __giao
extern "C" {
#endif

__declspec(dllexport) DWORD NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __giao
}
#endif



