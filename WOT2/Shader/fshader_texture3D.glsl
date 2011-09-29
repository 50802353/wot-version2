precision lowp float;
//
varying vec3 v_texcoords;
//
uniform mat4 u_mvpMatrix;
uniform samplerCube u_activeTex;

void main()
{
	gl_FragColor = textureCube(u_activeTex,v_texcoords);
}