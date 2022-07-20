#pragma once
#include<map>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include"opengl/basic.h"

class Model {
   public:
   Model(const std::string &name);
   ~Model();

   // static part
   public:
   // model name is identifier
   static void CreateModel(const std::string &modelName, const std::string &fileName);
   static Model* GetModel(const std::string &modelName);
   static void DeleteModel(const std::string &modelName);
   
   private:
   static std::map<std::string, Model*> modelMap;


   public:
   GLuint vaoId;
   GLuint vBufferId;
   GLuint iBufferId;


   float *locations;
   int vertexNumber;
   unsigned int *indexs;
   int indexNumber;
   private:
   void ReadFromObj(const std::string &name);

   
   
};