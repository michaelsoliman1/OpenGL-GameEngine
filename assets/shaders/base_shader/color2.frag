#version 330 core

// Here we will define Uniform Variable
// they are called uniform because every run of the shader (under the same draw call) will see the same value
// so it is uniform across all executions of the shader
//uniform vec3 color;
//uniform float time;
//uniform bool flicker;

// The output that goes to the frame buffer
out vec4 frag_color;

// Just a constant
#define PI 3.1415926535897932384626433832795

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(1280,720);
    // Convert RGB to RGBA (in other words, add an alpha value).
    frag_color = vec4(uv,0.0, 1.0);

}
