precision lowp float;
//
varying vec2 v_texcoords;
//
uniform mat4 u_mvpMatrix;
uniform sampler2D u_activeTex;

void main()
{
	gl_FragColor = texture2D(u_activeTex,v_texcoords);
}