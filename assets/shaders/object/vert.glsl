#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUv;

out vec3 FragPos;
out vec2 vUv;

uniform mat4 uMVP;

void main() {
    vUv = aUv;

    gl_Position = uMVP * vec4(aPos, 1.0);;
}
