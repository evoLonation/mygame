#version 330

in vec2 fragColorPos;
uniform sampler2D uTexture;
out vec4 outColor;

void main(){
   // outColor = vec4(1.0, 0.1, 0.4, 1.0);
   outColor = texture(uTexture, fragColorPos);
   
}