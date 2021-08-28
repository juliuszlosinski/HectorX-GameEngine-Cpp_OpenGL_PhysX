#version 330																		
																					
layout (location = 0) in vec3 pos;													
layout (location = 1) in vec2 tex;

uniform mat4 model;																
uniform mat4 projection;
uniform mat4 view;

out vec4 vCol;					
out vec2 TexCoord;

void main()																			
{																					
		gl_Position = projection * view * model * vec4(pos, 1.0);						    
		vCol= vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
        
        TexCoord=tex;
}																					
