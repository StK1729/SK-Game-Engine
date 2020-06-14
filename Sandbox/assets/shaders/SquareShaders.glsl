#type vertex
#version 450 core
layout(location = 0) in vec3 v_Position;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_TransformationMatrix;

out vec3 o_Position;
void main()
{
	o_Position = v_Position;
	gl_Position = u_ViewProjectionMatrix * u_TransformationMatrix *vec4(v_Position, 1.0);
}
#type fragment
#version 450 core
layout(location = 0) out vec4 v_Color;
in vec3 o_Position;
uniform vec4 u_Color;
void main()
{
	v_Color = u_Color;
}
