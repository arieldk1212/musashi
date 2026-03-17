#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColorVertices; // usage for coloring
out vec4 vertexColor;      // usage for coloring

void main() {
  // gl_Position = vec4(aPos, 1.0); // if we add - it flips the triangle
  gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0); // flipped!
  // gl_Position = vec4(aPos.x + 0.5, -aPos.y, aPos.z, 1.0); // offset! can also
  // be done with uniform vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // color dark
  // red
  // ourColorVertices = aPos; // becuase
  ourColorVertices = aColor;
}