#include<vector>
#include"renderer.h"
#include"model.h"
#include"component.h"
#include "texture.h"
#include "actor.h"

int main(int argv, char** args){
    Renderer renderer;
    renderer.Init();

    Model* model = new Model("african_head.obj");

    Texture* texture = new Texture("african_head_diffuse.tga");

    MeshComponent* mesh = new MeshComponent(model, texture);

    LocationComponent* location = new LocationComponent();
    location->SetDirection(Vector3(0, 0, -1), 3.14/4);
    location->SetLocation(0, 0, 6);

    CameraComponent* cameraComponent = new CameraComponent();
    cameraComponent->SetProjection(1, 1, 2, 100);
    LocationComponent* cameraLocation = new LocationComponent();
    cameraLocation->SetLocation(0, 0, 0);

    Actor* actor = new Actor();
    actor->AddComponent(mesh);
    actor->AddComponent(location);

    MeshComponent* mesh2 = new MeshComponent(model, texture);

    LocationComponent* location2 = new LocationComponent();
    location2->SetDirection(Vector3(0, 0, -1), 3.14/4);
    location2->SetLocation(0, 1, 8);

    Actor* actor2 = new Actor();
    actor2->AddComponent(mesh2);
    actor2->AddComponent(location2);

    Actor* camera = new Actor();
    camera->AddComponent(cameraComponent);
    camera->AddComponent(cameraLocation);


    renderer.AddMesh(actor);
    renderer.AddCamera(camera);
    renderer.AddMesh(actor2);


    bool isQuit = false;
    while (!isQuit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
             switch(event.type){
                case SDL_QUIT:
                    isQuit = true;
                break;
             }
        }
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if(state[SDL_SCANCODE_A]){
            cameraLocation->TranslateX(0.03);
        }
        if(state[SDL_SCANCODE_D]){
            cameraLocation->TranslateX(-0.03);
        }
        if(state[SDL_SCANCODE_W]){
            cameraLocation->TranslateZ(0.03);
        }
        if(state[SDL_SCANCODE_S]){
            cameraLocation->TranslateZ(-0.03);
        }
        if(state[SDL_SCANCODE_Z]){
            cameraLocation->TranslateY(0.03);
        }
        if(state[SDL_SCANCODE_X]){
            cameraLocation->TranslateY(-0.03);
        }
        if(state[SDL_SCANCODE_Q]){
//            cameraLocation->RotateY(0.03);
            cameraLocation->RotateByAxis(Vector3(0, 0, 2), Vector3(0, 1, 0), 0.03);
        }
        if(state[SDL_SCANCODE_E]){
//            cameraLocation->RotateY(-0.03);
            cameraLocation->RotateByAxis(Vector3(0, 0, 2), Vector3(0, -1, 0), 0.03);
        }


        renderer.DoDraw();

    }
    renderer.Finalize();
    return 0;
}
