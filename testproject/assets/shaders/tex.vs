#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 positionWorldspace;
out vec3 normalCameraspace;
out vec3 eyeDirectionCamera;
out vec3 lightDirectionCamera;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPos;

void main() {
    gl_Position = MVP * vec4(vertexPos, 1);

    positionWorldspace = (M * vec4(vertexPos, 1)).xyz;

    vec3 vertexPosCamera = (V * M * vec4(vertexPos, 1)).xyz;
    eyeDirectionCamera = vec3(0, 0, 0) - vertexPosCamera;

    vec3 lightPosCamera = (V * vec4(lightPos, 1)).xyz;
    lightDirectionCamera = lightPosCamera + eyeDirectionCamera;

    normalCameraspace = (V * M * vec4(vertexNormal, 0)).xyz;

    UV = vertexUV;
}