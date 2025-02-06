#version 460 core
//----------------------- cel shading -----------------------
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_objectColor;
uniform vec3 u_lightDir;
uniform vec3 u_viewPos;
uniform vec3 u_lightColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-u_lightDir);

    // Difusão
    float diff = max(dot(norm, lightDir), 0.0);
    if (diff > 0.85)
    {
        diff = 1.0;
    }
    else if (diff > 0.6)
    {
        diff = 0.5;
    }
    else if (diff > 0.35)
    {
        diff = 0.30;
    }
    else
    {
        diff = 0.25;
    }

    vec3 baseColor = diff * u_objectColor * u_lightColor;
    FragColor = vec4(baseColor, 1.0);
}
