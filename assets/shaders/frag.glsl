#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 NormalCoord;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

void main() {
  float ambientStrength = 0.1;
  vec3 ambient = LightColor * ambientStrength;

  vec3 norm = normalize(NormalCoord);
  // vec subtracting gives the direction vector
  // we normalize because we want them to end as a unit vectors.
  // when dealing with lighting we always want to normalize the vectors since we
  // only care about the direction and not magnitude.
  // ensure its 1.0
  vec3 lightDir = normalize(LightPos - FragPos);
  // 0.0 because negative is useless in colors, therefore its 0, we use max and
  // 0 for lower bound.
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * LightColor; // get the color

  float specularStrength = 0.5; // try and play with 1.0
  vec3 viewDir = normalize(ViewPos - FragPos);
  // -lightDir because we want the dir from the light source towards the
  // fragment, currently its from the fragment towards the light source.
  // we would not need to negate it if we calculate the lightDir like this:
  // FragPos - Light Pos
  vec3 reflectDir = reflect(-lightDir, norm);
  // 32 is the shininess value, we keep it at 32 to not be too distracting
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  vec3 specular = specularStrength * spec * LightColor;

  vec3 result = (ambient + diffuse + specular) * ObjectColor;
  FragColor = vec4(result, 1.0);
}