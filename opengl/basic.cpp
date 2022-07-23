#include"basic.h"

/**
 * init the opengl include window and context
 */
void OpenGLInit(SDL_Window*& window, SDL_GLContext& context){
   CreateGLContext(window, context);
   GlewInit();
}

/**
 * this function do following job:
 * set GL attribute
 * create a sdl window
 * create a gl context
 */
void CreateGLContext(SDL_Window*& window, SDL_GLContext& context){
   //set GL attribute
   //set profile to core(核心配置，桌面端推荐)
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   
   //set GL version to 3.3
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   
   //set color buffer size to 8-bits 
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

   //double buffer
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   //accelerated visual
   SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

   //depth buffer
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


   //create a sdlwindow
   window = SDL_CreateWindow("Hello, Mygame!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   1024, 768, SDL_WINDOW_OPENGL);



   //create a GL context 
   context = SDL_GL_CreateContext(window);
}

void GlewInit(){
   // Prevent certain errors when use core profile
   glewExperimental = GL_TRUE;

   if(glewInit() != GLEW_OK){
      SDL_Log("glew init filed!");
      exit(1);
   }
   // clear the error generate in glew's initial
   glGetError();

   // open the depth test
   glEnable(GL_DEPTH_TEST);

   //init done
}

/**
 * this function will continue to evolve
 */
GLuint BuildProgram(){
   GLuint vertexShader = CreateShader(std::string("../shader/vert.glsl"), GL_VERTEX_SHADER);
   GLuint fragShader = CreateShader(std::string("../shader/frag.glsl"), GL_FRAGMENT_SHADER);
   std::vector<GLuint> shaders;
   shaders.push_back(vertexShader);
   shaders.push_back(fragShader);

   GLuint shaderProgramId = CreateProgram(shaders);
   DeleteShader(vertexShader);
   DeleteShader(fragShader);
   return shaderProgramId; 
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
   GLuint bufferId;
   glGenBuffers(1, &bufferId);
   //set the created buffer object to target buffer object
   glBindBuffer(bufferType, bufferId);
   glBufferData(bufferType, dataSize, data, usage);
   // unbind this buffer object
   glBindBuffer(bufferType, 0);
   
   return bufferId;
}


/**
 * this function will continue to evolve
 * use datas to build a vao
 * when memberNum = 3, means only have location information
 * when memberNum = 5, means have location, colorLocation information 
 */
GLuint CreateVertexArray(float vertices[], unsigned int indexs[], int memberNum, int vertexNum, int indexNum){
   GLuint vaoId;
   glGenVertexArrays(1, &vaoId);
   glBindVertexArray(vaoId);
   GLuint vBufferId = CreateBuffer(GL_ARRAY_BUFFER, vertices, 
                        vertexNum * memberNum * sizeof(float), GL_STATIC_DRAW);
   CreateVertexAttribute(0, vBufferId, 3, GL_FLOAT, memberNum * sizeof(float), 0);
   glEnableVertexAttribArray(0);
   if(memberNum == 5){
      CreateVertexAttribute(1, vBufferId, 2, GL_FLOAT, memberNum * sizeof(float), 3 * sizeof(float));
      glEnableVertexAttribArray(1);
   }
   if(indexNum != 0){
      GLuint iBufferId = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indexs, 
                           indexNum * sizeof(unsigned int), GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);
   }
   glBindVertexArray(0);
   return vaoId;
   
}

/**
 * create a new vertex attribute with data
 * precondition: already bind a vao. this operation will change current vao's state.
 * before unbind vao, you can use glEnableVertexAttribArray(index) to open this vaa.
 * 
 * index: a indetitifier in specific vao
 * bufferId: 
 * size: Specifies the number of components per generic vertex attribute.
 * type: Specifies the data type of each component in the array. 
 *    available: GL_FLOAT, etc.
 * interval: Specifies the size of each vbb's interval, can auto computed if equals zero
 * 
 * offset: bufferId's buffer have a point bufptr, A pointer to finally started with bufptr + offset
 * 
 *
 */
GLint CreateVertexAttribute(GLint index, GLuint bufferId, int size, GLenum type, int interval, int offset){
   glBindBuffer(GL_ARRAY_BUFFER, bufferId);
   // set vertex attri
   glVertexAttribPointer(
      index, 
      size,
      type,
      GL_FALSE,
      interval, 
      (void*)offset
   );
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   return index;
}


