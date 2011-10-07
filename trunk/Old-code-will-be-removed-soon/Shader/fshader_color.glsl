precision lowp float;
//
varying vec4 v_colors;
//
uniform mat4 u_mvpMatrix;

void main()
{
	gl_FragColor = v_colors;
}