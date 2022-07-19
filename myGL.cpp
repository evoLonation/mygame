#include"myGL.h"

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
/*
delete shader object, they are useless after creating program by them.
*/
void DeleteShader(GLuint shaderId){
   glDeleteShader(shaderId);
}

/**
 * use shaderList's shaders to create a program object, 
 * during this process, will attach and detach shaders
 */
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
   glBindBuffer(bufferType, 0);
   
   return vBufferId;
}



/**
 * create a new vertex attribute with data
 * bufferId: 
 * size: Specifies the number of components per generic vertex attribute.
 * type: Specifies the data type of each component in the array. 
 * available: GL_FLOAT, etc.
 * 
 * offset: 
 * 
 * return new attrib index
 */
GLint CreateVertexAttribute(GLuint bufferId, int size, GLenum type, int interval, int offset){
   glBindBuffer(GL_ARRAY_BUFFER, bufferId);
   // set vertex attri
   static GLint index = 0;
   glVertexAttribPointer(
      index, 
      size,
      type,
      GL_FALSE,
      interval, 
      (void*)offset
   );
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   return index++;
}

void BindAttribToVAO(GLuint vaoId, GLint index){
   glBindVertexArray(vaoId);
   glEnableVertexAttribArray(index);
   glBindVertexArray(0);
}

