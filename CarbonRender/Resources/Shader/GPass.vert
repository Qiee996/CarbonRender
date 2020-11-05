#version 430

layout(location = 0) in vec4 msPos;
layout(location = 1) in vec3 msN;
layout(location = 2) in vec3 msT;
layout(location = 3) in vec4 uvs;
layout(location = 4) in vec4 vColor;
layout(location = 5) in vec3 msB;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;
uniform vec2 uvTilling0;
uniform vec4 uvTilling1;

out vec4 wsP;
out vec2 uvD;
out vec2 uvN;
out vec2 uvS;
out vec4 vertexColor;
out vec3 N;
out vec3 T;
out vec3 B;

void main ()
{
	wsP = modelMat * msPos;
	gl_Position = proMat * viewMat * wsP;

	T = msT;
	B = msB;
	N = msN;
	
	uvD = uvs.xy * uvTilling0.xy;
	uvN = uvs.xy * uvTilling1.xy;
	uvS = uvs.xy * uvTilling1.zw;
	vertexColor = vColor;
}