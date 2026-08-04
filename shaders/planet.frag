#version 330 core

out vec4 fragment_color;

in vec3 fragment_position;
in vec3 normal;

uniform vec3 light_position;      
uniform vec3 view_position;       
uniform vec3 object_color;   
uniform vec3 light_color;   

void main()
{
    float ambient_light_strength = 0.1;
    vec3 ambient = ambient_light_strength * light_color;
  	
    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(light_position - fragment_position);
    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light_color;
    
    float specular_lighting_strength = 0.5;
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_direction = reflect(-light_direction, norm);  
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
    vec3 specular = specular_lighting_strength * spec * light_color;  

    vec3 result = (ambient + diffuse + specular) * object_color;
    fragment_color = vec4(result, 1.0);
}