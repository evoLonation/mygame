#include"renderer.h"
#include<vector>
#include "actor.h"
#include "component.h"
#include "model.h"

void Renderer::Init() {
    OpenGLInit(window, context);
    programId = BuildProgram();
    viewProj = MatrixFactory::CreateScale(2 / 1024.0, 2 / 768.0, 1);

    glUseProgram(programId);
//    glUniformMatrix4fv(glGetUniformLocation(programId, "viewProj"), 1, GL_TRUE,
//                       reinterpret_cast<const GLfloat *>(viewProj.data));

}

void Renderer::Finalize() {
    //finalize
    //destroy GL context
    SDL_GL_DeleteContext(context);

    // delete program
    glDeleteProgram(programId);
}


void Renderer::AddMesh(Actor *meshActor) {
    meshList.push_back(meshActor);
}

void Renderer::DeleteMesh(int index) {
    // unimplement
}


void Renderer::DoDraw() {
    glClearColor(0.5, 1.0, 1.0, 1.0);
//clear thr color buffer using clear color and clear the z buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto mesh: meshList) {
        LocationComponent *locationComponent = mesh->GetComponent<LocationComponent>();
        MeshComponent *meshComponent = mesh->GetComponent<MeshComponent>();
        glBindVertexArray(meshComponent->GetModel()->getVaoId());
        glBindTexture(GL_TEXTURE_2D, meshComponent->getTexture()->getTextureId());
        glUniformMatrix4fv(glGetUniformLocation(programId, "worldTransform"), 1, GL_TRUE,
                           reinterpret_cast<const float *>(locationComponent->GetWorldTrans().data));
        CameraComponent *cameraComponent = camera->GetComponent<CameraComponent>();
        LocationComponent *cameraLocationComponent = camera->GetComponent<LocationComponent>();

        glUniformMatrix4fv(glGetUniformLocation(programId, "toCamera"), 1, GL_TRUE,
                           reinterpret_cast<const GLfloat *>((cameraLocationComponent->GetWorldTransInverse() *
                                                              cameraComponent->GetProjection()).data));


//        glUniformMatrix4fv(glGetUniformLocation(programId, "toCamera"), 1, GL_TRUE,
//                           reinterpret_cast<const GLfloat *>(cameraComponent->GetProjection().data));

//        glDrawElements(GL_TRIANGLES, meshComponent->GetModel()->getVertexNumber(), GL_UNSIGNED_INT, nullptr);
//        static int count = 3;
//      if(count < mesh->GetModel()->vertexNumber) count += 9;
        glDrawArrays(GL_TRIANGLES, 0, meshComponent->GetModel()->getVertexNumber());
    }
    SDL_GL_SwapWindow(window);

}

void Renderer::AddCamera(Actor *camera) {
    this->camera = camera;
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



