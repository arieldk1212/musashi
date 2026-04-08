#version 330 core

in vec3 FragPos;
in vec3 vNormal;
in vec2 vUv;

out vec4 Frag;

uniform sampler2D tex_a;

void main() {
    Frag = texture(tex_a, vUv);
}
