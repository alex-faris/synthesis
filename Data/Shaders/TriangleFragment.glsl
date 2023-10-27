#version 100

precision lowp float;

varying vec2 v_texture_coordinates;

uniform sampler2D u_texture;

void main()
{
    gl_FragColor = texture2D(u_texture, v_texture_coordinates);
}
