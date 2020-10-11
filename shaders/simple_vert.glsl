#version 330 core

layout (location = 0) in vec4 position;
// layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
  gl_Position = position;
  TexCoord = aTexCoord;
}
