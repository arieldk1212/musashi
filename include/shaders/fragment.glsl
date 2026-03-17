#version 330 core
// uniform vec4 ourColor; // can define in any shader stage, but if we
// define it we have to use it!

in vec2 TexCoord;         // from the vertex, texture
in vec3 ourColorVertices; // pass as input
in vec4 vertexColor;      // pass as input

out vec4 FragColor;

uniform sampler2D ourTexture1; // we pass the texture object to this uniform
uniform sampler2D ourTexture2;
uniform float mixValue;

void main() {
  // FragColor = texture(ourTexture1, TexCoord);
  // FragColor = texture(ourTexture1, TexCoord) * vec4(ourColorVertices, 1.0);
  FragColor =
      mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord),
          mixValue); // because we wrote 0.2, 80% input color from
                     // first texture and 2-% from the second.
  // FragColor =
  //     mix(texture(ourTexture1, TexCoord),
  //         texture(ourTexture2, vec2(5.0 - TexCoord.x, TexCoord.y)), 0.5);

  // FragColor = vec4(ourColorVertices, 1.0);
  // "   FragColor = ourColor;\n" // pass to the frag shader
  // "   FragColor = vertexColor;\n" // pass to the frag shader
  // "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
}