#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 NormalCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  // to get the world space pos we multiply only with the model
  FragPos = vec3(model * vec4(aPos, 1.0));
  // NormalCoord = aNormal;
  // convert into mat3 to lose the translation properties, to make sure the
  // normal vector stays perpendicular to the object.
  // best to calculate this on the CPU, expensive operation.
  // non-uniform scale -> changes the normals magnitude and direction.
  // uniform scale -> changes only the normals magnitude.
  NormalCoord = mat3(transpose(inverse(model))) * aNormal;

  gl_Position = projection * view * vec4(FragPos, 1.0);
}