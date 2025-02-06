#version 460 core
//----------------------- blinn phong + textures -----------------------
in vec2 TexCoords;
in vec3 Normal;
in vec3 ViewDir;

out vec4 FragColor;

uniform sampler2D u_texture;

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform float u_ka;
uniform float u_kd;
uniform float u_ks;
uniform float u_shininess;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material u_material;

void main()
{
    // I = Me + Ma*Ia*Ka + Ip*fat[Md*kd*(N.L) + Ms*ks*(N.H)^n]
    // H = normalize(L+V)
    vec3 norm = normalize(Normal);
    vec3 light_dir = normalize(-u_light_dir);
    vec3 view_dir = normalize(ViewDir);

    vec3 half_vector = normalize(light_dir + view_dir);  // H
    float light_angle = max(dot(norm, light_dir), 0.0);  // N.L
    float view_angle = max(dot(norm, half_vector), 0.0); // N.H

    // fat = 1 / Kc + Kl * d + Kq * d^2
    float kc = 1.0;
    float kl = 0.09;
    float kq = 0.032;
    float d = length(u_light_dir);
    float fat = min(1.0 / (kc + kl * d + kq * pow(d, 2.0)), 1.0);

    // (N.H)^n
    float specular_reflection = light_angle > 0.0 ? pow(view_angle, u_shininess * u_material.shininess) : 0.0;
    // Ma*Ia*Ka
    vec3 ambient = u_ka * u_light_color * u_material.ambient;
    // Ip*fat*Md*kd*(L.N)
    vec3 diffuse = u_kd * u_light_color * light_angle * u_material.diffuse * fat;
    // Ip*fat*Ms*ks*(N.H)^n
    vec3 specular = u_ks * u_light_color * specular_reflection * u_material.specular * fat;

    FragColor = vec4(ambient + diffuse + specular, 1) * texture(u_texture, TexCoords);
}
