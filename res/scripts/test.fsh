
precision mediump float;
precision mediump int;           

varying mediump vec4 vColor;                                 
//varying mediump vec2 vTextureCoord; 

uniform sampler2D sTexture;  
uniform sampler2D sTexture1; 
              
void main()
{             
   //vec4 color =  texture2D(sTexture, vTextureCoord) * vColor;                                                       
   //vec4 color1 =  texture2D(sTexture1, vTextureCoord) * vColor; 
   
   //gl_FragColor = mix(color,color1,0.5f);
   
   gl_FragColor = vColor;
}
