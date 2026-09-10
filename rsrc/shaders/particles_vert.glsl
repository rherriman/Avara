layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec4 vertexSpecular;
layout(location = 3) in float vertexGlow;
layout(location = 4) in float vertexReserved1;
layout(location = 5) in float vertexReserved2;
layout(location = 6) in float vertexReserved3;
layout(location = 7) in vec3 vertexNormal;
layout(location = 8) in mat4 instanceTransform;

uniform float maxShininess;
uniform float maxGlow;
uniform mat4 view;
uniform mat4 proj;

out vec4 fragmentColor;
out vec3 fragmentSpecular;
out float fragmentShininess;
out float fragmentGlow;
out vec3 fragmentNormal;
out vec3 fragPos;

void main() {
    vec4 pos = vec4(vertexPosition_modelspace, 1.0);
    gl_Position = proj * view * instanceTransform * pos;
    fragmentColor = vertexColor;
    fragmentSpecular = vertexSpecular.rgb;
    fragmentShininess = vertexSpecular.a * maxShininess;
    fragmentGlow = vertexGlow * maxGlow;
    fragmentNormal = vertexNormal * mat3(transpose(instanceTransform));
    fragPos = (pos * instanceTransform).xyz;
}
