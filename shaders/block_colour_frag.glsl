#version 330 core

in vec4 fragColour;
in vec2 fragTexCoord;

out vec4 outColour;

void main()
{
  outColour = fragColour;
}
