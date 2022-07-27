#include"model.h"
#include<map>
#include<string>
#include<vector>
#include<iostream>
#include <unordered_map>
#include"opengl/basic.h"


Model::Model(const std::string &fileName) {
    float *vertices;
    unsigned int *indexs;
    ReadFromObj(fileName, vertices, indexs);
    vaoId = CreateVertexArray(vertices, indexs, 5, vertexNumber, indexNumber);
    delete[] vertices;
    delete[] indexs;
}

Model::~Model() {
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

struct VertexIndex {
    unsigned int lIndex;
    unsigned int tIndex;
    unsigned int nIndex;

    bool operator==(const VertexIndex &vertexIndex) const {
        return lIndex == vertexIndex.lIndex && tIndex == vertexIndex.tIndex
               && nIndex == vertexIndex.nIndex;
    }
};

class IndexHasher {
public:
    std::size_t operator()(const VertexIndex &i) const {
        using std::hash;
        return hash<unsigned int>()(i.lIndex + i.tIndex + i.tIndex);
    }
};


void Model::ReadFromObj(const std::string &name, float *&vertices, unsigned int *&indexs) {
    std::ifstream in(name);
    std::string str;
    std::vector<float> locationList;
    std::vector<float> colorLocationList;
    //这里值直接指向文件中顶点成员的索引。
    std::unordered_map<VertexIndex, unsigned int, IndexHasher> primaryIndexMap;
    //这里是将VertexIndex去重后，最终的指向primaryIndex的索引。
    std::vector<unsigned int> finalIndexList;
    // start to get vertex information and index
    while (std::getline(in, str)) {
        // std::cout << str;
        std::istringstream instr(str);


        switch (instr.get()) {
            case 'v':
                switch (instr.get()) {
                    float c;
                    case ' ':
                        for (int i = 0; i < 3; i++) {
                            instr >> c;
                            locationList.push_back(c);
                        }
                        break;
                    case 't':
                        for (int i = 0; i < 2; i++) {
                            instr >> c;
                            colorLocationList.push_back(c);
                        }
                        break;
                }
                break;
            case 'f':
                unsigned int locationIndex, colorIndex, normalIndex;
                char tmp;
                for (int i = 0; i < 3; i++) {
                    instr >> locationIndex >> tmp >> colorIndex >> tmp >> normalIndex;
                    VertexIndex newIndex = {locationIndex - 1, colorIndex - 1, normalIndex - 1};
                    unsigned int finalIndex;
                    auto iterator = primaryIndexMap.find(newIndex);
                    if (iterator == primaryIndexMap.end()){
                        finalIndex = primaryIndexMap.size();
                        primaryIndexMap.insert(std::pair<VertexIndex, unsigned int>(newIndex, finalIndex));
                    }else {
                        finalIndex = (*iterator).second;
                    }
                    finalIndexList.push_back(finalIndex);
                }
                break;
        }
    }
    vertexNumber = finalIndexList.size();
    indexNumber = finalIndexList.size();
    std::vector<VertexIndex> primaryIndexList(vertexNumber);
    for(auto pair : primaryIndexMap) {
        primaryIndexList[pair.second] = pair.first;
    }

    indexs = new unsigned int[vertexNumber];
    for(int i = 0; i < finalIndexList.size(); i++) {
        indexs[i] = finalIndexList[i];
    }

    vertices = new float [vertexNumber * 5];
    for(auto index : finalIndexList) {
        VertexIndex primaryIndex = primaryIndexList[index];
        vertices[index * 5] = locationList[primaryIndex.lIndex * 3 + 0];
        vertices[index * 5 + 1] = locationList[primaryIndex.lIndex * 3 + 1];
        vertices[index * 5 + 2] = locationList[primaryIndex.lIndex * 3 + 2];
        vertices[index * 5 + 3] = 1- colorLocationList[primaryIndex.tIndex * 2 + 0];
        vertices[index * 5 + 4] = 1- colorLocationList[primaryIndex.tIndex * 2 + 1];
    }

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
