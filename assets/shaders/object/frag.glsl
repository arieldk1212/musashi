#version 330 core

in vec2 vUv;
in vec3 FragPos;

out vec4 Frag;

uniform vec2 uUvScale;
uniform vec2 uUvOffset;
uniform sampler2D uZombie;

void main() {
    vec2 SpriteUv = uUvOffset + (vUv * uUvScale);
    Frag = texture(uZombie, SpriteUv);
}
