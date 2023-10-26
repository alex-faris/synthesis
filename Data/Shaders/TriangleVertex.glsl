#version 100

precision lowp float;

attribute vec3 in_position;
uniform mat4 u_rotation_matrix;

void main()
{
    gl_Position = u_rotation_matrix * vec4(in_position, 1.0);
}
