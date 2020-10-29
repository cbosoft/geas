#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 in_colour;
layout (location = 2) in vec2 aTexCoord;

out vec4 fragColour;
out vec2 fragTexCoord;

void main()
{
  gl_Position = position;
  vec4 maybe_colour = in_colour;

  if (maybe_colour.r < 0.1)
    maybe_colour = vec4(0.5, 0.5, 0.5, 1.0);

  fragColour = maybe_colour;
  fragTexCoord = aTexCoord;
}
