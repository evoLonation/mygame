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
//    location->SetDirection(Vector3(0, 0, 1), 0);
    location->SetDirection(Vector3(0, 0, -1), 3.14/2);
    location->SetLocation(0, 0, 6);

    CameraComponent* cameraComponent = new CameraComponent();
    cameraComponent->SetProjection(3, 3, 4, 10);
    LocationComponent* cameraLocation = new LocationComponent();
    cameraLocation->SetLocation(0, 0, 0);

    Actor* actor = new Actor();
    actor->AddComponent(mesh);
    actor->AddComponent(location);

    Actor* camera = new Actor();
    camera->AddComponent(cameraComponent);
    camera->AddComponent(cameraLocation);


    renderer.AddMesh(actor);
    renderer.AddCamera(camera);


//    TranslationMatrix matrix4 = MatrixFactory::CreateTranslation(1,2,3);
//    TranslationMatrix matrix3 = MatrixFactory::CreateTranslation(1,2,3);
//    OrthogonalMatrix matrix = MatrixFactory::CreateRotationX(1);
//    BaseMatrix4 matrix42;
//    Matrix4 matrix41 = matrix3 * matrix;

    //   mesh->setScale(300);
//    mesh->setTranslation(0, 0, -6);

//    Camera* camera = new Camera();
//    camera->setPerspectiveProjection(MatrixFactory::CreatePerspectiveProjection(2, 2, 5, 10));
//    renderer.AddMesh(mesh);
//    renderer.AddCamera(camera);

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
         // actor2.RotateY(-2 * 3.14 / 60);

        }

        renderer.DoDraw();

        // glDrawElements(GL_TRIANGLES, model.indexNumber, GL_UNSIGNED_INT, nullptr);
    }
    renderer.Finalize();
    return 0;
}
