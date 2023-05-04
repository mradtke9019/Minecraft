#version 330

in vec3 fNormal;
in vec3 fPosition;

in vec2 TexCoord;
uniform sampler2D TextureSlot;


void main()                                                             
{

//vec3 normal = normalize(fNormal);
    //vec3 lightDir = normalize(LightPosition - fPosition);

    //float diffuse = max(dot(normal, lightDir), 0.0);
    //texture(texture_diffuse1, TexCoord)

     gl_FragColor = texture(TextureSlot, TexCoord);
     //gl_FragColor = vec4(TexCoord, 0.0, 1.0);
     //gl_FragColor = vec4(fNormal, 1.0);
    //FragColor = vec4(fNormal, 1.0);

}