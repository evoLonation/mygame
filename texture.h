#pragma once


#include <string>
#include <map>
#include "GLEW/glew.h"

class Texture {
public:
    Texture(const std::string & fileName);
    ~Texture();
//public:
//    static Texture* CreateTexture(const std::string & name, const std::string & fileName);
//    static Texture *GetTexture(const std::string &name);
//private:
//    static std::map<std::string, Texture*> textureMap;
private:
//    friend class Renderer;
    GLuint textureId;
public:
    GLuint getTextureId() const;

};


