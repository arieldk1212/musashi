#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;

out vec4 FragColor;

in vec3 FragPos;
in vec3 NormalCoord;

uniform vec3 ObjectColor;
uniform vec3 ViewPos;

void main() {
  vec3 ambient = light.ambient * material.ambient;

  vec3 norm = normalize(NormalCoord);
  // vec subtracting gives the direction vector
  // we normalize because we want them to end as a unit vectors.
  // when dealing with lighting we always want to normalize the vectors since we
  // only care about the direction and not magnitude.
  // ensure its 1.0
  vec3 lightDir = normalize(light.position - FragPos);
  // 0.0 because negative is useless in colors, therefore its 0, we use max and
  // 0 for lower bound.
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = (diff * material.diffuse) * light.diffuse; // get the color

  vec3 viewDir = normalize(ViewPos - FragPos);
  // -lightDir because we want the dir from the light source towards the
  // fragment, currently its from the fragment towards the light source.
  // we would not need to negate it if we calculate the lightDir like this:
  // FragPos - Light Pos
  vec3 reflectDir = reflect(-lightDir, norm);
  // 32 is the shininess (scattering) value, we keep it at 32 to not be too
  // distracting
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = (material.specular * spec) * light.specular;

  // vec3 result = (ambient + diffuse + specular) * ObjectColor;
  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
}