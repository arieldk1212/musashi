#version 330 core

in vec3 Pos;
in vec3 Normal;
in vec3 Uv;
in vec2 Color;
in vec2 TexCoords;

out vec4 Frag;

uniform sampler2D tex_a;

void main() {
    Frag = texture(tex_a, TexCoords);
}
