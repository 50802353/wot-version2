
uniform mat4 u_mvpMatrixProjection;
uniform mat4 u_mvpMatrixView;
uniform mat4 u_mvpMatrixWorld;
attribute vec4 a_position;    
attribute vec2 a_uv;	
varying vec2 v_uv;

void main()
{
	gl_Position = u_mvpMatrixProjection * u_mvpMatrixView * u_mvpMatrixWorld *  a_position;
	//gl_Position = a_position;
	//v_color = a_color;
	v_uv=a_uv;
}

