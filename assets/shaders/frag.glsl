#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float kMixValue;
uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform vec3 ObjectColor;
uniform vec3 LightColor;

void main() {
  // FragColor = mix(texture(ourTexture0, TexCoord),
  // texture(ourTexture1, TexCoord), kMixValue);
  FragColor = vec4(LightColor * ObjectColor, 1.0);
}