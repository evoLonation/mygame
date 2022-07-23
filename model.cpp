#include"model.h"
#include<map>
#include<string>
#include<vector>
#include<iostream>
#include"opengl/basic.h"



Model::Model(const std::string &fileName){
    float* vertices;
    unsigned int*  indexs;
    ReadFromObj(fileName, vertices, indexs);
    vaoId = CreateVertexArray(vertices, indexs, 5, vertexNumber, indexNumber);
    delete[] vertices;
    delete[] indexs;
}
Model::~Model(){
   glDeleteVertexArrays(1, &vaoId);
}

//Model* Model::CreateModel(const std::string &modelName, const std::string &fileName){
//   Model* model = new Model(fileName);
//   modelMap.insert(std::pair<std::string, Model*>(modelName, model));
//   return model;
//}
//Model* Model::GetModel(const std::string &modelName){
//   return modelMap[std::string(modelName)];
//}
//void Model::DeleteModel(const std::string &modelName){
//   Model* deletedModel = GetModel(modelName);
//   delete deletedModel;
//}


void Model::ReadFromObj(const std::string &name, float *&vertices, unsigned int *&indexs){
   std::ifstream in(name);
   std::string str;
   std::vector<float> locationList;
   std::vector<float> colorLocationList;
   std::vector<unsigned int> locationIndexList;
   std::vector<unsigned int> colorIndexList;
   while (std::getline(in, str))
   {
      // std::cout << str;
      std::istringstream instr(str);
      
      
      switch(instr.get()){
         case 'v':
            switch(instr.get()){
               float c;
               case ' ':
               for(int i = 0;i < 3; i++){
                  instr >> c;
                  locationList.push_back(c);
               }
               break;
               case 't':
               for(int i = 0; i < 2; i++){
                  instr >> c;
                  colorLocationList.push_back(c);
               }
               break;
            }
            break;
         case 'f':
            int locationIndex, colorIndex, normalIndex;
            char tmp;
            for(int i = 0;i < 3; i++){
               instr >> locationIndex >> tmp >> colorIndex >> tmp >> normalIndex;
               locationIndexList.push_back(locationIndex);
               colorIndexList.push_back(colorIndex);
            }
            break;
      }
   }
   // no index implement
   vertexNumber = locationIndexList.size();
   vertices = new float[vertexNumber * 5];
   for(int i = 0; i < vertexNumber; i++){
      int locationIndex = locationIndexList[i] - 1;
      vertices[i * 5] = locationList[locationIndex * 3 + 0];
      vertices[i * 5 + 1] = locationList[locationIndex * 3 + 1];
      vertices[i * 5 + 2] = locationList[locationIndex * 3 + 2];
      int colorIndex = colorIndexList[i]  - 1;
      vertices[i * 5 + 3] = 1 - colorLocationList[colorIndex * 2 + 0];
      vertices[i * 5 + 4] = 1 -  colorLocationList[colorIndex * 2 + 1];
   }
   indexNumber = 0;
   indexs = new unsigned int[0];

   ///// todo index implement
   // vertexNumber = locationList.size() / 3;
   // indexNumber = locationIndexList.size();
   // colorNumber = colorLocationList.size() / 2;

   // vertices = new float[colorNumber * 5];
   // for(int i = 0; i < colorNumber; i++){
   //    vertices
   // }

   // indexs = new unsigned int[locationIndexList.size()];
   // for(int i = 0; i < vertexNumber; i++){
   //    vertices[i * 5] = locationList[i * 3 + 0];
   //    vertices[i * 5 + 1] = locationList[i * 3 + 1];
   //    vertices[i * 5 + 2] = locationList[i * 3 + 2];
   //    vertices[i * 5 + 3] = colorLocationList[i * 2 + 0];
   //    vertices[i * 5 + 4] = colorLocationList[i * 2 + 1];

   // }
   // for(int i = 0; i < locationIndexList.size(); i++){
      
   //    // notice!!! minus 1
   //    indexs[i] = locationIndexList[i] - 1;
   // }
   // return;
}

GLuint Model::getVaoId() const {
    return vaoId;
}

GLuint Model::getIBufferId() const {
    return iBufferId;
}

int Model::getVertexNumber() const {
    return vertexNumber;
}

int Model::getIndexNumber() const {
    return indexNumber;
}
