#include"model.h"
#include"opengl/basic.h"

std::map<std::string, Model*> Model::modelMap;


Model::Model(const std::string &fileName){
   ReadFromObj(fileName);
   vaoId = CreateVertexArray(locations, indexs, 3, vertexNumber, indexNumber);
   // glGenVertexArrays(1, &vaoId);
   // glBindVertexArray(vaoId);
   // vBufferId = CreateBuffer(GL_ARRAY_BUFFER, locations, 
   //                      vertexNumber * 3 * sizeof(float), GL_STATIC_DRAW);
   // CreateVertexAttribute(0, vBufferId, 3, GL_FLOAT, 0, 0);
   // iBufferId = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indexs, 
   //                      indexNumber * sizeof(unsigned int), GL_STATIC_DRAW);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);
   // glEnableVertexAttribArray(0);
   // glBindVertexArray(0);
   delete[] locations;
   delete[] indexs;

}
Model::~Model(){
   // delete[] locations;
   // delete[] indexs;
   glDeleteVertexArrays(1, &vaoId);
}

void Model::CreateModel(const std::string &modelName, const std::string &fileName){
   modelMap.insert(std::pair<std::string, Model*>(modelName, new Model(fileName)));
}
Model* Model::GetModel(const std::string &modelName){
   return modelMap[std::string(modelName)];
}
void Model::DeleteModel(const std::string &modelName){
   Model* deletedModel = GetModel(modelName);
   delete deletedModel;
}


void Model::ReadFromObj(const std::string &name){
   std::ifstream in(name);
   std::string str;
   std::vector<float> locationList;
   std::vector<unsigned int> indexList;
   while (std::getline(in, str))
   {
      // std::cout << str;
      std::istringstream instr(str);
      
      
      switch(instr.get()){
         case 'v':
            if(instr.get() != ' ')break;
            float c;
            for(int i = 0;i < 3; i++){
               instr >> c;
               locationList.push_back(c);
            }
            break;
         case 'f':
            int index;
            std::string tmp;
            for(int i = 0;i < 3; i++){
               instr >> index >> tmp;
               indexList.push_back(index);
            }
            break;
      }
   }
   locations = new float[locationList.size()];
   indexs = new unsigned int[indexList.size()];
   vertexNumber = locationList.size() / 3;
   indexNumber = indexList.size();
   for(int i = 0; i < locationList.size(); i++){
      locations[i] = locationList[i];
   }
   for(int i = 0; i < indexList.size(); i++){
      
      // notice!!! minus 1
      indexs[i] = indexList[i] - 1;
   }
   return;
}