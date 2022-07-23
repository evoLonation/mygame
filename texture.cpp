#include "texture.h"
#include "tool/tgaimage.h"

//Texture *Texture::CreateTexture(const std::string &name, const std::string &fileName) {
//    auto* texture = new Texture(fileName);
//    textureMap.insert(std::pair<std::string, Texture*>(name, texture));
//    return texture;
//}
//
//Texture *Texture::GetTexture(const std::string &name) {
//    return textureMap[std::string(name)];
//}

Texture::Texture(const std::string &fileName) {
    TGAImage tgaImage;
    tgaImage.read_tga_file("african_head_diffuse.tga");

    int colorFormat = GL_RGB;
    if(tgaImage.get_bytespp() == 4)colorFormat = GL_RGBA;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, colorFormat,
                 tgaImage.get_width(), tgaImage.get_height(), 0,
                 colorFormat, GL_UNSIGNED_BYTE, tgaImage.buffer());
    // you can free the buffer in memory right now
    // enable Bilinear Filtering （双线性过滤）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

GLuint Texture::getTextureId() const {
    return textureId;
}

