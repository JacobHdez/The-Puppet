#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_VP;
uniform mat4 u_model;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = u_VP * u_model * vec4(aPos, 1.0);
	FragPos = vec3(u_model * vec4(aPos, 1.0));
	Normal = aNormal;
}

#shader fragment
#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_lightPos;

out vec4 FragColor;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;

	vec3 result = (ambient + diffuse) * u_objectColor;
	FragColor = vec4(result, 1.0);
}