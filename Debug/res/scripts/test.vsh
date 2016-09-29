
precision mediump float;
precision mediump int;        

attribute mediump vec4 aPosition; 
attribute mediump vec4 aColor; 
//attribute mediump vec2 aTextureCoord; 

varying mediump vec4 vColor;                                 
//varying mediump vec2 vTextureCoord; 

uniform mediump mat4 uWVPMatrix;

void main()
{
    mediump vec4 pos = vec4(aPosition.xyz,1.0);
    
    gl_Position = uWVPMatrix * pos;
    
    vColor = aColor;                                
    //vTextureCoord = aTextureCoord; 
}
