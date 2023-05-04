#version 330

in vec3 fNormal;
in vec3 fPosition;
in vec2 TexCoord;

uniform sampler2D mTexture;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;


void main()                                                             
{
    
    vec3 color = texture(mTexture, TexCoord).rgb;

    vec3 ambient = 0.05 * color;

    vec3 lightDir = normalize(LightPosition - fPosition);

    vec3 normal = normalize(fNormal);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 diffuse = diff * color;
    
    vec3 viewDir = normalize(ViewPosition - fPosition);

    vec3 reflectDir =  reflect(-lightDir, normal);

    float spec = 0.0f;

    spec = pow(max(dot(viewDir, reflectDir), 0.0f), 8.0f);

    vec3 specular = vec3(0.3) * spec;

     gl_FragColor = vec4(ambient + diffuse + specular, 0.0f);

}