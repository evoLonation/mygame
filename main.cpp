#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"renderer.h"
#include"myGL.h"

int main(int argv, char** args){
   Renderer renderer;
   renderer.Init();

   // float vertices[] = {
   //    -0.5, 0.5, 0,
   //    0.5,  0.5, 0,
   //    0.5, -0.5, 0,
   //    -0.5, -0.5, 0,
   // };
   // uint16_t indexs[] = {
   //    0, 1, 2,
   //    2, 3, 0,
   // };
   
   
   // GLuint vBufferId;
   // glGenBuffers(1, &vBufferId);
   // //GL_ARRAY_BUFFER shows we want to use this id as vertex buffer
   // glBindBuffer(GL_ARRAY_BUFFER, vBufferId);
   // //GL_STATIC_DRAW shows we just want to load the date once and repeatly use it
   // glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

   // GLuint iBufferId;
   // glGenBuffers(1, &iBufferId);
   // //GL_ELEMENT_ARRAY_BUFFER shows we want to use this id as index buffer
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);
   // //GL_STATIC_DRAW shows we just want to load the date once and repeatly use it
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(uint16_t), indexs, GL_STATIC_DRAW);

   // // set vertex attri
   // glEnableVertexAttribArray(0);
   // glVertexAttribPointer(
   //    0, 
   //    3, 
   //    GL_FLOAT,
   //    GL_FALSE,
   //    3 * sizeof(float),
   //    0
   // );
   float xarr[] = {-0.5, 0.5, 0.5};
   float yarr[] = {0.5, 0.5, -0.5};

   float vertices[] = {
      -0.5, 0.5, 0, 
      0.5,  0.5, 0,
      0.5, -0.5, 0,
      // -0.5, -0.5, 0,
   };
   float vertices2[] = {
      // -0.5, 0.5, 0,
      0.5,  0.5, 0,
      0.5, -0.5, 0,
      -0.5, -0.5, 0,
   };
   float vertices3[] = {
   // x     a    a    y
      0.5,  0.5, 0,  0.1,
      0.5, -0.5, 0,  0.4,
      -0.5, -0.5, 0.5, -0.9,
   };


   GLuint vertexArrId;
   glGenVertexArrays(1, &vertexArrId);
   glBindVertexArray(vertexArrId);
   
   
   GLuint vBufferId1 = CreateBuffer(GL_ARRAY_BUFFER, xarr, 3 * 1 * sizeof(float), GL_STATIC_DRAW);
   GLuint vBufferId2 = CreateBuffer(GL_ARRAY_BUFFER, yarr, 3 * 1 * sizeof(float), GL_STATIC_DRAW);

   

   GLint index2 = CreateVertexAttribute(vBufferId1, 1, GL_FLOAT, 0, 0);
   GLint index1 = CreateVertexAttribute(vBufferId2, 1, GL_FLOAT, 0, 0);
   // GLint index2 = CreateVertexAttribute(vBufferId, 1, GL_FLOAT, 4 * sizeof(float), 3 * sizeof(float));

   // SDL_Log("%d, %d", index1, index2);
   glEnableVertexAttribArray(index1);
   glEnableVertexAttribArray(index2);

   glBindVertexArray(0);


   GLuint vertexShader = CreateShader(std::string("../vert.glsl"), GL_VERTEX_SHADER);
   GLuint fragShader = CreateShader(std::string("../frag.glsl"), GL_FRAGMENT_SHADER);
   std::vector<GLuint> shaders;
   shaders.push_back(vertexShader);
   shaders.push_back(fragShader);

   GLuint shaderProgram = CreateProgram(shaders);
   DeleteShader(vertexShader);
   DeleteShader(fragShader);


   //ready to draw
   glBindVertexArray(vertexArrId);
   glUseProgram(shaderProgram);


   while (1)
   {
      // renderer.DoDraw();
      glClearColor(0.5, 1.0, 1.0, 1.0);
      //clear thr color buffer using clear color 
      glClear(GL_COLOR_BUFFER_BIT);
      
      // start draw
      // glBindVertexArray(0);
      // glBindVertexArray(vertexArrId);
      // glDrawArrays(GL_TRIANGLES, 0, 3);
      // glBindVertexArray(vertexArrId2);
      // glDrawArrays(GL_TRIANGLES, 0, 3);
      // glBindVertexArray(vertexArrId);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      

      SDL_GL_SwapWindow(renderer.window);
   }
   renderer.Finalize();
}
