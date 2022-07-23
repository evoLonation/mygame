#include<vector>
#include"renderer.h"
#include"model.h"
#include"component.h"
#include "texture.h"

int main(int argv, char** args){
   

   Renderer renderer;
   renderer.Init();
   Model* model = new Model("african_head.obj");
   Texture* texture = new Texture("african_head_diffuse.tga");
   MeshComponent* mesh = new MeshComponent(model, texture);
   renderer.AddMesh(mesh);
   mesh->setScale(300);

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
