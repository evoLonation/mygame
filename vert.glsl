#version 330

// layout(location = 0) in vec3 inPos1;
// layout(location = 1) in float inPos2;
layout(location = 0) in float x;
layout(location = 1) in float y;


void main(){
   // gl_Position = vec4(inPos1.x, inPos2, 0, 1.0);
   // gl_Position = vec4(inPos1, 1.0);
   gl_Position = vec4(x, y, 0, 1.0);
   // colorR = inPos2;
}
