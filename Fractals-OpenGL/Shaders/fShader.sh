#version 330 core

out vec4 FragColor;

uniform vec2 resolution;
uniform vec2 viewPort;
uniform int maxIterations;
uniform float scale;
uniform vec2 constant;
uniform vec2 focalPoint;

void main() 
{
    vec2 c = ((gl_FragCoord.xy - resolution / 2.0) / scale + focalPoint) / resolution * viewPort;

    vec2 vec = c;
    int iter = 0;

    while (length(vec) < 4.0 && iter < maxIterations)
    {
        vec = vec2(vec.x * vec.x - vec.y * vec.y + constant.x, 2.0 * vec.x * vec.y + constant.y);
        iter++;
    } 

    float mod = sqrt(length(vec));
    float smooth_it = float(iter) - log2(max(1.0f, log2(mod)));

    float color = smooth_it / maxIterations;
    FragColor = vec4(color, color, color, 1.0);
}
