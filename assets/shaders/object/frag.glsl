#version 330 core

in vec3 FragPos;
// in vec3 vNormal;
// in vec2 vUv;

out vec4 FragColor;

uniform sampler2D tex_a;

void main() {
    // Frag = texture(tex_a, vUv);
    // Frag = FragPos;
    FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}
