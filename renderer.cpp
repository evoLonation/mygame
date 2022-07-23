#include"renderer.h"
#include<vector>
#include "actor.h"
#include "component.h"
#include "model.h"

void Renderer::Init(){
    OpenGLInit(window, context);
    programId = BuildProgram();
    viewProj = Matrix4::CreateScale(Vector3(2/1024.0, 2/768.0, 1));

    glUseProgram(programId);
    glUniformMatrix4fv(glGetUniformLocation(programId, "viewProj"), 1, GL_TRUE,
                       reinterpret_cast<const GLfloat *>(viewProj.data));

}

void Renderer::Finalize(){
    //finalize
    //destroy GL context
    SDL_GL_DeleteContext(context);

    // delete program
    glDeleteProgram(programId);
}



void Renderer::AddMesh(class MeshComponent* mesh){
    meshList.push_back(mesh);
}
void Renderer::DeleteMesh(int index){
    // unimplement
}



void Renderer::DoDraw(){
    glClearColor(0.5, 1.0, 1.0, 1.0);
//clear thr color buffer using clear color and clear the z buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto mesh : meshList){

        glBindVertexArray(mesh->getModel()->getVaoId());
        glBindTexture(GL_TEXTURE_2D, mesh->getTexture()->getTextureId());
        glUniformMatrix4fv(glGetUniformLocation(programId, "worldTransform"), 1, GL_TRUE,
                           reinterpret_cast<const float*>(&(mesh->getWorldTrans().data[0][0])));
//        glUniformMatrix4fv(glGetUniformLocation(programId, "viewProj"), 1, GL_TRUE,
//                           reinterpret_cast<const GLfloat *>(viewProj.data));

// glDrawElements(GL_TRIANGLES, actor->model->indexNumber, GL_UNSIGNED_INT, nullptr);
        static int count = 3;
//      if(count < mesh->getModel()->vertexNumber) count += 9;
        glDrawArrays(GL_TRIANGLES, 0, mesh->getModel()->getVertexNumber());
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



