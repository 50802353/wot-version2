precision mediump float;
uniform sampler2D u_texture; 
 
varying vec3 v_uv; 
void main() 
{ 
     gl_FragColor = texture2D(u_texture, vec2(v_uv)); 
}