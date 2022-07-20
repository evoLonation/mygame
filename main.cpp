#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"renderer.h"
#include"model.h"
#include"Math.h"
#include"actor.h"

int main(int argv, char** args){
   Renderer renderer;
   renderer.Init();

   Model model(std::string("african_head.obj"));
   Actor actor(&model);
   actor.setScale(300);
   actor.RotateZ(0.4);
   Actor actor2(&model);
   actor2.setScale(300);
   renderer.AddActor(actor);
   renderer.AddActor(actor2);

   // Matrix4 worldTransMatrix;
   // worldTransMatrix *= Matrix4::CreateScale(300);
   // worldTransMatrix *= Matrix4::CreateRotationZ(0.1);
   // worldTransMatrix *= Matrix4::CreateRotationX(0.5);
   // // worldTransMatrix *= Matrix4::CreateTranslation(Vector3())
   // Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024, 768);


   // glUniformMatrix4fv(0, 1, GL_TRUE, worldTransMatrix.GetAsFloatPtr());
   // glUniformMatrix4fv(1, 1, GL_TRUE, viewProj.GetAsFloatPtr());



   // GLuint vertexArrId;
   // glGenVertexArrays(1, &vertexArrId);
   // glBindVertexArray(vertexArrId);
   
   // GLuint vBufferId = CreateBuffer(GL_ARRAY_BUFFER, (void*)(model.locations), 
   //                      model.vertexNumber * 3 * sizeof(float), GL_STATIC_DRAW);
   // GLuint iBufferId = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, model.indexs, 
   //                      model.indexNumber * sizeof(unsigned int), GL_STATIC_DRAW);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);

   // GLint index = CreateVertexAttribute(vBufferId, 3, GL_FLOAT, 0, 0);

   // glEnableVertexAttribArray(index);

   // glBindVertexArray(0);


   // GLuint vertexShader = CreateShader(std::string("../shader/vert.glsl"), GL_VERTEX_SHADER);
   // GLuint fragShader = CreateShader(std::string("../shader/frag.glsl"), GL_FRAGMENT_SHADER);
   // std::vector<GLuint> shaders;
   // shaders.push_back(vertexShader);
   // shaders.push_back(fragShader);

   // GLuint shaderProgram = CreateProgram(shaders);
   // DeleteShader(vertexShader);
   // DeleteShader(fragShader);


   // //ready to draw
   // glBindVertexArray(vertexArrId);

   // glUseProgram(shaderProgram);


   while (1)
   {
      renderer.DoDraw();
      actor.RotateZ(2 * 3.14 / 60);
      actor2.RotateZ(-2 * 3.14 / 60);
      // renderer.DoDraw();
      // glClearColor(0.5, 1.0, 1.0, 1.0);
      // //clear thr color buffer using clear color 
      // glClear(GL_COLOR_BUFFER_BIT);
      
      // // start draw
      // // glBindVertexArray(0);
      // // glBindVertexArray(vertexArrId);
      // // glDrawArrays(GL_TRIANGLES, 0, 3);
      // // glBindVertexArray(vertexArrId2);
      // // glDrawArrays(GL_TRIANGLES, 0, 3);
      // // glBindVertexArray(vertexArrId);
      // // glDrawArrays(GL_TRIANGLES, 0, model.vertexNumber);
      // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);
      
      
      // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "worldTransfrom"), 1, GL_TRUE, worldTransMatrix.GetAsFloatPtr());
      // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewProj"), 1, GL_TRUE, viewProj.GetAsFloatPtr());
      // glDrawElements(GL_TRIANGLES, model.indexNumber, GL_UNSIGNED_INT, nullptr);
      // // SDL_Log("have error? %d", (int)(glGetError() != GL_NO_ERROR));
      

      // SDL_GL_SwapWindow(renderer.window);
   }
   // renderer.Finalize();
}
