#version 330 core

uniform rangesBlock
{
  float ranges[5];
};

uniform colorsBlock
{
  vec3 colors[5];
};

out vec4 FragColor;

uniform vec2 resolution;
uniform vec2 viewPort;
uniform int iterations;
uniform float scale;
uniform vec2 constant;
uniform vec2 focalPoint;

int getRange(int currIterations)
{
    int range = 0;

    for (int i = 0; i < 5; i++)
    {
        range = i;
        if (ranges[i] > currIterations) 
        {
            break;
        }
    }
    range--;
    return range;
}

void main() 
{
    vec2 c = ((gl_FragCoord.xy - resolution / 2.0) / scale + focalPoint) / resolution * viewPort;

    vec2 vec = c;
    int iter = 0;

    while (length(vec) < 4.0 && iter < iterations)
    {
        vec = vec2(vec.x * vec.x - vec.y * vec.y + constant.x, 2.0 * vec.x * vec.y + constant.y);
        iter++;
    } 

    float mod = sqrt(length(vec));
    float smooth_it = float(iter) - log2(max(1.0f, log2(mod)));
    float color = smooth_it / iterations;

    int range = getRange(iter);

    float t = smoothstep(0.0, 1.0, color);
    FragColor = vec4(mix(colors[range], colors[range+1], t) * color, 1.0);
}
