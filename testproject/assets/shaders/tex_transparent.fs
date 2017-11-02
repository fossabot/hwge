#version 330 core

in vec2 UV;
in vec3 positionWorldspace;
in vec3 normalCameraspace;
in vec3 eyeDirectionCamera;
in vec3 lightDirectionCamera;

out vec4 color;

uniform sampler2D texSampler;
uniform mat4 MV;
uniform vec3 lightPos;

void main() {
    // Light emission
    vec3 lightColor = vec3(1, 1, 1);
    float lightPower = 50.0f;

    // Material
    vec3 materialDiffuseColor = texture(texSampler, UV).rgb;
    vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
    vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

    // Distance to the light
    float distance = length(lightPos - positionWorldspace);

    // Normal of the computed fragment
    vec3 n = normalize(normalCameraspace);

    // direction of the light
    vec3 l = normalize(lightDirectionCamera);

    // clamped above 0
    // light is at the verical of the triangle -> 1
    // light is perpendicular to the triangle -> 0
    // light is behind the triangle -> 0
    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 E = normalize(eyeDirectionCamera);
    vec3 R = reflect(-l, n);

    // clamped to 0
    // looking into the reflection -> 1
    // looking else where -> <1
    float cosAlpha = clamp(dot(E, R), 0, 1);

    color.rgb = 
        // Ambient : simulates indirect lighting
        materialAmbientColor +
        // Diffuse : the "color" of the object
        materialDiffuseColor * lightColor * lightPower * cosTheta / (distance * distance) +
        // Specular : reflective highlight, like a mirror
        materialSpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / (distance * distance);
    
    color.a = texture(texSampler, UV).a;
}