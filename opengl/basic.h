#include <GLEW/glew.h>
#include<SDL/SDL.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

/**************************************
 *             init part
 **************************************/

/**
 * init the opengl include window and context
 */
void OpenGLInit(SDL_Window*& window, SDL_GLContext& context);

/**
 * this function do following job:
 * set GL attribute
 * create a sdl window
 * create a gl context
 */
void CreateGLContext(SDL_Window*& window, SDL_GLContext& context);

void GlewInit();

/**************************************
 *             program part
 **************************************/

/**
 * this function will continue to evolve
 */
GLuint BuildProgram();

/*
将编写好的shader文件编译并创建，返回对应的id
remember use DeleteShader
*/
GLuint CreateShader(std::string&& fileName, GLenum shaderType);
/*
delete shader object, they are useless after creating program by them.
*/
void DeleteShader(GLuint shaderId);

/**
 * use shaderList's shaders to create a program object, 
 * during this process, will attach and detach shaders
 */
GLuint CreateProgram(const std::vector<GLuint> &shaderList);


/**************************************
 *             vbo part
 **************************************/

/*
create a buffer object which the type is signed by bufferType
bufferType maybe:
GL_ARRAY_BUFFER

usage​ is a hint to the GL implementation as to how a buffer object's data store will be accessed.
usage maybe:
GL_STATIC_DRAW: we just want to load the date once and repeatly use it to do draw working

*/
GLuint CreateBuffer(GLenum bufferType, const void* data, int dataSize, GLenum usage);

/**************************************
 *             vao part
 **************************************/

/**
 * this function will continue to evolve
 * use datas to build a vao
 */
GLuint CreateVertexArray(float vertices[], unsigned int indexs[], int memberNum, int vertexNum, int indexNum);


GLint CreateVertexAttribute(GLint index, GLuint bufferId, int size, GLenum type, int interval, int offset);

