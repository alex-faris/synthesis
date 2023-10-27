#version 100

precision lowp float;

attribute vec3 in_position;
attribute vec2 in_texture_coordinates;
uniform mat4 u_rotation_matrix;

varying vec2 v_texture_coordinates;

void main()
{
	v_texture_coordinates = in_texture_coordinates;
    gl_Position = u_rotation_matrix * vec4(in_position, 1.0);
}
