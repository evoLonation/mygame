#version 330

layout(location = 0) in vec3 inPos1;
// layout(location = 1) in float inPos2;
// layout(location = 0) in float x;
// layout(location = 1) in float y;
uniform mat4 worldTransform;
uniform mat4 toCamera;
layout(location = 1) in vec2 inColorPos;

out vec2 fragColorPos;


void main(){
    vec4 tmp = vec4(inPos1, 1.0) * worldTransform * toCamera;
//    vec4 tmp = vec4(inPos1, 1.0) * worldTransform ;
//    vec4 tmp = vec4(inPos1, 1.0) * toCamera ;
//    vec4 tmp = vec4(inPos1, 1.0) ;

//   gl_Position = vec4(inPos1, 1.0);
   // gl_Position = vec4(x, y, 0, 1.0);
   // gl_Position = vec4(tmp.x, tmp.y, 0, 1.0);
    gl_Position = tmp;
   // colorR = inPos2;
   fragColorPos = inColorPos;
}
