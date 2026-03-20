#version 330 core
layout(location = 0) in vec3 aPos;
// layout(location = 1) in vec3 aColor; // uncommented because we not use the
// color
layout(location = 1) in vec2 aTexCoord; // for textures! changed location to 1

out vec2 TexCoord;         // because its (S,T)
out vec3 ourColorVertices; // usage for coloring
out vec4 vertexColor;      // usage for coloring

uniform mat4 transform; // we pass the transformation matrix

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  // gl_Position =
  //     transform * vec4(aPos, 1.0); // if we add - it flips the triangle, if
  //     we were to remove the transform, it would appear statically
  gl_Position = projection * view * model * vec4(aPos, 1.0);

  // gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0); // flipped!
  // gl_Position = vec4(aPos.x + 0.5, -aPos.y, aPos.z, 1.0); // offset! can also
  // be done with uniform vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // color dark
  // red
  // ourColorVertices = aPos; // becuase
  // ourColorVertices = aColor;
  TexCoord = aTexCoord;
}