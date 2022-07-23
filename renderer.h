#pragma once

#include"opengl/basic.h"
#include "math.h"



class Actor;

class Renderer{
public:
    void Init();
    void Finalize();
    void AddMesh(class MeshComponent* mesh);
    void DeleteMesh(int index);
    void DoDraw();

private:
    SDL_Window* window;
    SDL_GLContext context;
    GLuint programId;



    std::vector<class MeshComponent*> meshList;
    Matrix4 viewProj;

};