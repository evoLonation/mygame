#include <GLEW/glew.h>
#include<SDL/SDL.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

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



/*
create a buffer object which the type is signed by bufferType
bufferType maybe:
GL_ARRAY_BUFFER

usage​ is a hint to the GL implementation as to how a buffer object's data store will be accessed.
usage maybe:
GL_STATIC_DRAW: we just want to load the date once and repeatly use it to do draw working

*/
GLuint CreateBuffer(GLenum bufferType, const void* data, int dataSize, GLenum usage);


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
GLint CreateVertexAttribute(GLuint bufferId, int size, GLenum type, int interval, int offset);


// /**
//  * indexBufferId could be zero means no index
//  */
// GLuint CreateVertexArray(GLuint vertexBufferId, GLuint indexBufferId);


// void Draw(GLuint programId, GLuint vaoId, GLenum mode, int first, int count);