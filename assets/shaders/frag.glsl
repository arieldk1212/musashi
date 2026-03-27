#version 330 core

in vec3 FragPos;
in vec3 NormalCoord;

out vec4 FragColor;

uniform float kMixValue;
uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;

void main() {
  float ambientStrength = 0.2;
  vec3 ambient = LightColor * ambientStrength;

  vec3 norm = normalize(NormalCoord);
  vec3 lightDir =
      normalize(LightPos - FragPos); // vec subtracting gives the distance
  // we normalize because we want them to end as a unit vectors.
  // when dealing with lighting we always want to normalize the vectors since we
  // only care about the direction and not magnitude.

  // 0.0 because negative is useless in colors, therefore its 0, we use max and
  // 0 for lower bound.
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * LightColor; // get the color

  vec3 result = (ambient + diffuse) * ObjectColor;

  FragColor = vec4(result, 1.0);
}