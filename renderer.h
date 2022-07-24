#pragma once

#include"opengl/basic.h"
#include "math.h"


class Actor;

class Renderer{
public:
    void Init();
    void Finalize();
    void AddMesh(Actor* meshActor);
    void AddCamera(Actor* camera);
    void DeleteMesh(int index);
    void DoDraw();


private:
    SDL_Window* window;
    SDL_GLContext context;
    GLuint programId;



    std::vector<Actor*> meshList;
    Actor* camera;
    BaseMatrix4 viewProj;

};