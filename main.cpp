#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"renderer.h"
void CompileShader(std::string&& fileName, GLenum shaderType, GLuint& shaderId);
GLuint CreateShader(std::string&& fileName, GLenum shaderType);
void DeleteShader(GLuint shaderId);
GLuint CreateProgram(const std::vector<GLuint> &shaderList);
GLuint CreateVertexArrayBuffer(const float vertices[], int dataSize);
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
   GLuint vertexArrId;
   glGenVertexArrays(1, &vertexArrId);
   glBindVertexArray(vertexArrId);
   
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

   float vertices[] = {
      -0.5, 0.5, 0,
      0.5,  0.5, 0,
      0.5, -0.5, 0,
      // -0.5, -0.5, 0,
   };
   GLuint vBufferId = CreateVertexArrayBuffer(vertices, 3 * 3 * sizeof(float));




   GLuint vertexShader = CreateShader(std::string("../vert.glsl"), GL_VERTEX_SHADER);
   GLuint fragShader = CreateShader(std::string("../frag.glsl"), GL_FRAGMENT_SHADER);
   std::vector<GLuint> shaders(vertexShader, fragShader);

   GLuint shaderProgram = CreateProgram(shaders);
   DeleteShader(vertexShader);
   DeleteShader(fragShader);

   glUseProgram(shaderProgram);

   // glDrawElements(
   //    GL_TRIANGLES,
   //    6, 
   //    GL_UNSIGNED_SHORT,
   //    0
   // );


   while (1)
   {
      // renderer.DoDraw();
      glClearColor(0.5, 1.0, 1.0, 1.0);
      //clear thr color buffer using clear color 
      glClear(GL_COLOR_BUFFER_BIT);
      
      // start draw
      glBindBuffer(GL_ARRAY_BUFFER, vBufferId);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      SDL_GL_SwapWindow(renderer.window);
   }
   renderer.Finalize();
}

/*
将编写好的shader文件编译并创建，返回对应的id
remember use DeleteShader
*/
GLuint CreateShader(std::string&& fileName, GLenum shaderType){
   // get file content
   std::ifstream shaderFile(fileName);
   if(!shaderFile.is_open()){
      SDL_Log("Open shader file failed!");
      return 0;
   }
   std::stringstream sstream;
   sstream << shaderFile.rdbuf();
   std::string content = sstream.str();
   const char* contentChar = content.c_str();
   
   // create and compile shader
   GLuint shaderId = glCreateShader(shaderType);
   glShaderSource(shaderId, 1, &contentChar, nullptr);
   glCompileShader(shaderId);

   //check if compile succeed
   GLint status;
   glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
   if(status == GL_FALSE){
      GLint infoLogLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, strInfoLog);
        
        const char *strShaderType = NULL;
        switch(shaderType)
        {
        case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
        case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        
        SDL_Log("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
   }
   return shaderId;
}

//delete shader object, they are useless after creating program by them.
void DeleteShader(GLuint shaderId){
   glDeleteShader(shaderId);
}
//use shaderList's shaders to create a program object, 
//during this process, will attach and detach shaders
GLuint CreateProgram(const std::vector<GLuint> &shaderList){
   //create a program
   GLuint programId = glCreateProgram();
   //attach shaders
   for(auto shaderId : shaderList){
      glAttachShader(programId, shaderId);
   }
   //link program
   glLinkProgram(programId);
   
   //check if link succeed
   GLint status;
   glGetProgramiv(programId, GL_LINK_STATUS, &status);
   if(status == GL_FALSE){
      GLint infoLogLength;
      glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
      
      GLchar *strInfoLog = new GLchar[infoLogLength + 1];
      glGetProgramInfoLog(programId, infoLogLength, nullptr, strInfoLog);
      SDL_Log("Link failure in program %d:\n%s\n", programId, strInfoLog);
      delete[] strInfoLog;
   }

   //detach shaders
   for(auto shaderId : shaderList){
      glDetachShader(programId, shaderId);
   }
   return programId;
}

/*
create a buffer object which the type is signed by bufferType
bufferType maybe:
GL_ARRAY_BUFFER

usage​ is a hint to the GL implementation as to how a buffer object's data store will be accessed.
usage maybe:
GL_STATIC_DRAW: we just want to load the date once and repeatly use it to do draw working

*/
GLuint CreateBuffer(GLenum bufferType, const void* data, int dataSize, GLenum usage){
   GLuint vBufferId;
   glGenBuffers(1, &vBufferId);
   //set the created buffer object to target buffer object
   glBindBuffer(bufferType, vBufferId);
   glBufferData(bufferType, dataSize, data, usage);
   // unbind this buffer object
   // glBindBuffer(bufferType, 0);

}

/**
 * size: Specifies the number of components per generic vertex attribute.
 * type: Specifies the data type of each component in the array. 
 * available: GL_FLOAT, etc.
 */
void SetVertexAttribute(GLuint vertexBufferId, int size, GLenum type){

   // glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
   // set vertex attri
   int index = 0;
   glEnableVertexAttribArray(index);
   glVertexAttribPointer(
      index, 
      size, 
      type,
      GL_FALSE,
      0,
      0
   );
   // glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/**
 * create and init a vertex buffer
 * 
 */
GLuint CreateVertexArrayBuffer(const float vertices[], int dataSize){
   GLuint bufferId = CreateBuffer(GL_ARRAY_BUFFER, vertices, dataSize, GL_STATIC_DRAW);
   SetVertexAttribute(bufferId, 3, GL_FLOAT);
   return bufferId;
}

