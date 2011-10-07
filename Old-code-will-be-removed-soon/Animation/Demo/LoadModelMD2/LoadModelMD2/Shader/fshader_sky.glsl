precision lowp float;
uniform samplerCube u_texture;
varying vec3 v_uv;
void main()
{             
	//gl_FragColor =  vec4 ( 1.0, 0.0, 0.0, 1.0 );
	gl_FragColor=textureCube(u_texture,v_uv);
} 
