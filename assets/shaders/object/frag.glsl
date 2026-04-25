#version 330 core

in vec3 FragPos;
in vec2 vUv;

out vec4 Frag;

uniform sampler2D uZombie;
uniform vec2 uUvOffset;
uniform vec2 uUvScale;

void main() {
    vec2 SpriteUv = uUvOffset + (vUv * uUvScale);
    Frag = texture(Zombie, SpriteUv);
}
