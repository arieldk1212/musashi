#version 330 core

in vec3 FragPos;
in vec2 vUv;

out vec4 Frag;

uniform sampler2D Zombie;

void main() {
    Frag = texture(Zombie, vUv);
}
