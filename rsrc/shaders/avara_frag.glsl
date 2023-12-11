#version 330 core

in vec4 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentPosition;

uniform vec3 cameraPosition = vec3(0, 0, 0);
uniform vec3 light0 = vec3(0, 0, 0);
uniform vec3 light0Color = vec3(1, 1, 1);
uniform vec3 light1 = vec3(0, 0, 0);
uniform vec3 light1Color = vec3(1, 1, 1);
uniform vec3 light2 = vec3(0, 0, 0);
uniform vec3 light2Color = vec3(1, 1, 1);
uniform vec3 light3 = vec3(0, 0, 0);
uniform vec3 light3Color = vec3(1, 1, 1);
uniform float ambient = 0.0;
uniform vec3 ambientColor = vec3(1, 1, 1);
uniform float lights_active = 1.0;

out vec4 color;

vec3 diffuse_light(vec3 light, vec3 lightColor) {
    return max(dot(fragmentNormal, light), 0.0) * lightColor;
}

vec3 diffuse() {
    return diffuse_light(light0, light0Color)
            + diffuse_light(light1, light1Color)
            + diffuse_light(light2, light2Color)
            + diffuse_light(light3, light3Color);

}

vec3 specular_light(vec3 light, vec3 lightColor) {
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDir = reflect(-light, fragmentNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;
    return specular;
}

vec3 specular() {
    return specular_light(light0, light0Color)
            + specular_light(light1, light1Color)
            + specular_light(light2, light2Color)
            + specular_light(light3, light3Color);
}

vec4 light_color() {
    return mix(
        ambient * vec4(ambientColor, 1.0) * fragmentColor,
        vec4((ambient * ambientColor) + diffuse() + specular(), 1.0) * fragmentColor,
        lights_active
    );
}

void main() {
    color = light_color();
}
