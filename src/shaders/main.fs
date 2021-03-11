#version 330 core

in vec2 UV;
in vec3 positionWorldspace;
in vec3 normalCameraspace;
in vec3 eyeDirectionCameraspace;
in vec3 lightDirectionCameraspace;

out vec4 color;

uniform sampler2D textureSampler;
uniform mat4 MV;
uniform vec3 lightPositionWorldspace;

void main(){
	vec3 ambientLight = vec3(0.2, 0.2, 0.2);
    // Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower =	150.0f;
	
	// Material properties
	vec3 MaterialDiffuseColor = texture( textureSampler, UV ).rgb;
	vec3 MaterialAmbientColor = vec3(0.5,0.5,0.5) * MaterialDiffuseColor;
	// vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);
	vec3 MaterialSpecularColor = vec3(0.2,0.2,0.2);

	// Distance to the light
	// float distance = length( lightPositionWorldspace - positionWorldspace );
	float distance = 50;

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( normalCameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( lightDirectionCameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(eyeDirectionCameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color.rgb = 
	// 	// Ambient : simulates indirect lighting
		MaterialAmbientColor +
	// 	// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
	// 	// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
	// color.rgb = 
	// // 	// Ambient : simulates indirect lighting
	// 	MaterialAmbientColor +
	// // 	// Diffuse : "color" of the object
	// 	MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
	// // 	// Specular : reflective highlight, like a mirror
	// 	MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance) + ambientLight;
	// color.rgb = texture( textureSampler, UV ).rgb;
    color.a = 1.0;

	// color.r = positionWorldspace.z / 2;

	// color.rgb = normalize(positionWorldspace);
}