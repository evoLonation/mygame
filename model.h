#pragma once
#include<map>
#include<string>
#include"opengl/basic.h"

/**
 * 关联类：MeshComponent，需要使用到Model类的
 */
class Model {
   private:
    ~Model();

//   // static part
//public:
//    // model name is identifier
//    static Model* CreateModel(const std::string &modelName, const std::string &fileName);
//    static Model* GetModel(const std::string &modelName);
//    static void DeleteModel(const std::string &modelName);
//
//private:
//    static std::map<std::string, Model*> modelMap;



private:
    GLuint vaoId;
    GLuint iBufferId;
    int vertexNumber;
    int indexNumber;
public:
    GLuint getVaoId() const;
    GLuint getIBufferId() const;
    int getVertexNumber() const;
    int getIndexNumber() const;


    Model(const std::string &fileName);

private:
    void ReadFromObj(const std::string &name, float *&vertices, unsigned int *&indexs);
};