#type vertex
#version 450 core
layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec2 v_TexCoord;
uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_TransformationMatrix;

out vec2 o_TexCoord;
void main()
{
	o_TexCoord = v_TexCoord;
	gl_Position = u_ViewProjectionMatrix * u_TransformationMatrix * vec4(v_Position, 1.0);
}

#type fragment
#version 450 core
layout(location = 0) out vec4 color;
in vec2 o_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	color = texture(u_Texture, o_TexCoord)*u_Color;
}