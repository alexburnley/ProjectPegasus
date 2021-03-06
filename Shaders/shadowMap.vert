#version 330

layout(location = 0) in vec4 Vertex;
layout(location = 2) in vec4 Normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
	gl_Position = Projection * View * Model * Vertex;
}