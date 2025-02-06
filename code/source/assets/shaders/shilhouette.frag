#version 460 core
//----------------------- shilhouette + rim light -----------------------
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_objectColor;
uniform vec3 u_viewPos;
uniform vec3 u_lightDir;
uniform vec3 u_lightColor;
uniform vec3 u_rimColor;
uniform vec3 u_silhouetteColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-u_lightDir);
    vec3 viewDir = normalize(u_viewPos - FragPos);

    // Rim lighting
    float rim = 1.0 - max(dot(norm, viewDir), 0.0);
    rim = pow(rim, 1.5); // intensity
    vec3 rimLight = rim * u_rimColor;
    vec3 baseColor = u_silhouetteColor + rimLight;

    FragColor = vec4(baseColor, 1.0);
}
