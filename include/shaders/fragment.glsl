#version 330 core
// uniform vec4 ourColor; // can define in any shader stage, but if we
// define it we have to use it!

in vec3 ourColorVertices; // pass as input
in vec4 vertexColor;      // pass as input

out vec4 FragColor;

void main() {
  FragColor = vec4(ourColorVertices, 1.0);
  // "   FragColor = ourColor;\n" // pass to the frag shader
  // "   FragColor = vertexColor;\n" // pass to the frag shader
  // "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
}