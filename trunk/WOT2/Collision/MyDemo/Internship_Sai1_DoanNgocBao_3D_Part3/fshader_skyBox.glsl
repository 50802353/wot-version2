precision mediump float;
uniform samplerCube u_texture; 
 
varying vec3 v_uv; 
void main() 
{ 
     gl_FragColor = textureCube(u_texture, v_uv); 
}