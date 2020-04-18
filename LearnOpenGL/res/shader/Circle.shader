#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_MVP;

out vec4 v_Color;

void main()
{
	v_Color = a_Color;
	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec2 u_resolution;
uniform float u_halfRadius;

in vec4 v_Color;

void main() {
    float dist = 0.0;
    dist = distance(gl_FragCoord.xy, u_resolution.xy / 2.0);

    float value = smoothstep(u_halfRadius - (u_halfRadius * 0.005), 
	u_halfRadius + (u_halfRadius * 0.005), dist);

    color = vec4(vec3(v_Color - value), 1.0);
}