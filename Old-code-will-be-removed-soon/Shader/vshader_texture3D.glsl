precision lowp float;
//
attribute vec4 a_vertices;
attribute vec3 a_texcoords;
//
varying vec3 v_texcoords;
//
uniform mat4 u_mvpMatrix;
uniform samplerCube u_activeTex;

void main()
{
	v_texcoords = a_texcoords;
	gl_Position = u_mvpMatrix * a_vertices;
}