#version 330 core

layout(location = 0) in vec3 vertexPositionModelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormalModelspace;

out vec2 UV;
out vec3 positionWorldspace;
out vec3 normalCameraspace;
out vec3 eyeDirectionCameraspace;
out vec3 lightDirectionCameraspace;

uniform vec3 lightPositionWorldspace;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main(){
    mat4 mvp = projection * view * model;

	gl_Position =  mvp * vec4(vertexPositionModelspace, 1);

    positionWorldspace = (model * vec4(vertexPositionModelspace, 1)).xyz;

    vec3 vertexPositionCameraspace = ( view * model * vec4(vertexPositionModelspace,1)).xyz;
	eyeDirectionCameraspace = vec3(0,0,0) - vertexPositionCameraspace;

	vec3 LightPositionCameraspace = ( view * vec4(lightPositionWorldspace,1)).xyz;
	lightDirectionCameraspace = LightPositionCameraspace + eyeDirectionCameraspace;
	
	normalCameraspace = ( view * model * vec4(vertexNormalModelspace,0)).xyz;


	vec2 vertexUVs[4] = vec2[4](
		vec2(0, 0),
		vec2(1, 0),
		vec2(0, 1),
		vec2(1, 1)
	);
	
	UV = vertexUV;
}