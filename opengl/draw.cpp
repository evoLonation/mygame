// #include"draw.h"

// GLuint CreateVertexArray(float vertices[], unsigned int indexs[], int vertexNum, int indexNum){
//    GLuint vaoId;
//    glGenVertexArrays(1, &vaoId);
//    glBindVertexArray(vaoId);
//    vBufferId = CreateBuffer(GL_ARRAY_BUFFER, vertices, 
//                         vertexNum * 3 * sizeof(float), GL_STATIC_DRAW);
//    CreateVertexAttribute(0, vBufferId, 3, GL_FLOAT, 0, 0);
//    iBufferId = CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indexs, 
//                         indexNum * sizeof(unsigned int), GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBufferId);
//    glEnableVertexAttribArray(0);
//    glBindVertexArray(0);
//    return vaoId;
// }


// void SetViewProj(const BaseMatrix4& viewProj){
//    glUniformMatrix4fv(glGetUniformLocation(programId, "viewProj"), 1, GL_TRUE, viewProj.GetAsFloatPtr());
// }


// void DrawActor(GLuint vaoId, const BaseMatrix4& worldTrans);