uniform mat4 u_mWorldMatrix;
uniform mat4 u_mViewMatrix;
uniform mat4 u_mProjectionMatrix;

attribute vec4 a_position;    
attribute vec4 a_color;	
attribute vec3 a_uv;
varying vec4 v_color;
varying vec3 v_uv;

void main()
{
	gl_Position = u_mProjectionMatrix *  u_mViewMatrix *  u_mWorldMatrix * a_position;
	//gl_Position = a_position;
	//v_color = a_color;
	v_uv = a_uv;
}

