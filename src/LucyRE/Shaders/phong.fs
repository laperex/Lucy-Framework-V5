#version 450 core

in vec3 normal;
// in vec4 color;
in vec3 frag_pos;
in vec3 view_pos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec4 color;
	vec4 pos;

	float ambient;
	float diffuse;
	float specular;
};

uniform Light light;
uniform Material material;

void main() {
	// blinn-phong
	// vec4 color = vec4(normal, 1);
	// if (color.x < 0)
	// 	color.x = -color.x;
	// if (color.y < 0)
	// 	color.y = -color.y;
	// if (color.z < 0)
	// 	color.z = -color.z;

	vec3 light_dir;
	if (light.pos.w == 0.0)
		light_dir = light.pos.xyz;
	else
		light_dir = normalize(light.pos.xyz - frag_pos);

	float diffuse = max(dot(light_dir, normal), 0.0);

	vec3 result = material.ambient * light.ambient;
	result += diffuse * material.diffuse * light.diffuse;

	if (diffuse != 0.0) {
		vec3 view_dir = normalize(view_pos - frag_pos);

		vec3 halfway = normalize(view_dir + light_dir);
		result += pow(max(dot(normal, halfway), 0.0), material.shininess) * material.specular * light.specular;
	}

	gl_FragData[0] = light.color * vec4(result, 1);//color;
}