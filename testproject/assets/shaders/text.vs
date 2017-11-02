#version 330 core

layout(location = 0) in vec2 vertexPosScreen;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

void main() {
    vec2 vertexPosH = vertexPosScreen - vec2(400, 300);
    vertexPosH /= vec2(400, 300);
    gl_Position = vec4(vertexPosH, 0, 1);

    UV = vertexUV;
}