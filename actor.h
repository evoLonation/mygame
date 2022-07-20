#pragma once
#include"model.h"
#include"Math.h"

class Actor{
   public:
   Actor(Model* model);
   Matrix4* getWorldTrans();
   void setScale(float scale);
   void RotateZ(float theta);
   GLuint getVAOId();

   private:
   void computeWorldTrans();
   Matrix4 scale;
   Matrix4 rotation;
   Matrix4 translation;

   bool worldTransUpdate;
   public:
   Model* model;
   private:
   Matrix4 worldTransMatrix;

   
};