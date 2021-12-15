
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
//in vec2 TexCoord;

//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float mixValue;

void main()
{
    // (first texture, second texture, interpolation value (0.0 = first, 1.0 = second))
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue) * vec4(ourColor, 1.0);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.s, TexCoord.t)), 0.2); // mirror on y
    FragColor = vec4(ourColor, 1.0);
}