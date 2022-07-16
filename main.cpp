#include<iostream>
#include"renderer.h"

int main(int argv, char** args){
   Renderer renderer;
   renderer.Init();
   while (1)
   {
      renderer.DoDraw();
   }
   renderer.Finalize();
}