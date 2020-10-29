#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 in_colour;
//layout (location = 2) in vec2 aTexCoord;

//out vec2 tex_coord;
out vec4 out_colour;

void main()
{
  gl_Position = position;
  //tex_coord = aTexCoord;
  out_colour = in_colour;
}
