precision lowp float;
//
attribute vec4 a_vertices;
attribute vec4 a_colors;
//
varying vec4 v_colors;
//
uniform mat4 u_mvpMatrix;

void main()
{
	v_colors = a_colors;
	gl_Position = u_mvpMatrix * a_vertices;
}