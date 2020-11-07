#version 330 core

out vec4 color;

in vec4 fragColour;
in vec2 fragTexCoord;

uniform sampler2D ourTexture;

void main()
{
  vec4 maybe_colour = texture(ourTexture, fragTexCoord);

  if (maybe_colour.a < 0.1) discard;

  color = maybe_colour;
}
