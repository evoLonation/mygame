#include"init.h"


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

   //init done
}