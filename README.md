# GameEngine-Cpp_OpenGL_PhysX

Hi!
This folder contains everything about my game engine that is during the process of realization.

**Legend:**
* External_Libs ~ contains all external libraries that are used (GLEW, GLFW, GLM).
* Repos ~ contains the project with application (Game engine).
* Versions_And_Notes ~ contains all notes written by me and latest versions of game engine.

**Goals:**
1. Implement rendering system by using OpenGL: 

![image](https://user-images.githubusercontent.com/72278818/132967531-90064a08-7c76-4446-8647-a42ddb85d93b.png)

* GLFW for creating the context and handling windows and user inputs. 
* GLEW for manipulating the context in a modern way and handling platform depended extensions.
* GLM for supporting math operations (matrices, vectors).
3. Implement Collision and Physics system by using PhysX from Nvidia.

![20130308_physx](https://user-images.githubusercontent.com/72278818/132967499-428c2fd5-fbd7-4e26-98aa-c15a98157c6c.jpg)

4. Implement audio system.
5. Implement animation system.
6. Implement AI system.

# Current progress:

**1. Date: 6.08.2021**

**1. Creating the window with context using GLFW and initializing GLEW for using modern OpenGL:**

1.1 Initialization library with GLFW (for creating a window and the context). -> **_glfwInit()_**

1.2 Setting up the window hints ~ window configuration.

1.3 Creating the window ~ getting the pointer to this. -> **_glfwCreateWindow(...)_**

1.4 Setting up the current context to be our window.

1.5 Initialization library with GLEW (for handling OpenGL context in a modern way and using the platform dependend extensions). -> **_glewInit()_**

1.6 Getting the size of frame buffer.

1.7 Setting the view port with the size of frame buffer (width and height). -> **_glViewport(0, 0, bufferWidth, bufferHeight)_**

1.8 Activating the platform depended extensions. -> **_glwExperimental=GL_TRUE_**

1.9 Looping the running window. -> **_glfwWindowShouldClose(mainWindow)_**

1.9.1 Polling the events (like user input). -> **_glfwPollEvents()_**

1.9.2 Clearing the screen with red color. -> **_glClearColor(...) and then glClear(GL_COLOR_BUFFER_BIT)_**

1.9.3 Swaping buffers. -> **_glfwSwapBuffers(mainWindow)_**

1.10 Window with the context is created.

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/128518820-7ddc77f0-a302-4de6-8367-76a57da42c92.png)

**2. Date: 9.08.2021**

**Drawing first triangle:**

**1. Setting up the VAO (The thing that we are going to draw):** 

1.1 Creating the VAO (Vertex Array Objects).

1.2 Binding the VAO.

1.3 Creating the VBO (Vertex Buffer Objects).

1.4 Binding the VBO.

1.5 Inserting the data filled with vertices to VBO.

1.6 Set up the attribute pointers.

1.7 Done VAO.


**2. Setting up the program with shaders:**

2.1 Creatng empty program.

2.2 Creating empty shaders.

2.3 Filling the shaders with source code.

2.4 Compiling the shaders.

2.5 Linking the shaders to one program.

2.6 Validing the program.

2.7 Shader program is done.


**3. Drawing the triangle:**

3.1 Binding the Shader Program.

3.2 Binding the VAO.

3.3 Calling the function glDrawArrays to draw the triangle.

3.4 Unbinding the Shader Program.

3.5 Unbinding the VAO.

3.6 Triangle is drawn.

**General idea is: First bind the shader program, then send/set data to uniforms in the shader program and then render object!**

**Rendering pipeline:**

![image](https://user-images.githubusercontent.com/72278818/133353650-dfd49ff2-d827-497f-8b6a-7f2b1ae6c564.png)

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/128777097-bc424d23-56b7-4c5d-b0ab-b6aa6b4274f2.png)

**3. Date: 10.08.2021**

Moving window by using uniforms (the easiest way -> without model matrices):

![window_moving](https://user-images.githubusercontent.com/72278818/128925107-7e71ac97-a1b1-48f2-a3f9-dc1ac24f1a77.gif)

**4. Date: 11.08.2021**

Appling operations to the triangle by using uniforms and _**model matrices:**_
1. Creating uniform variable in the vertex shader ex.: with name **_"model"_**.
2. Storing information about location of uniform variable in the appliacation variable. -> **_uniformModel = glGetUniformLocation(shader, "model")_**
3. Passing the data do program shader that will be stored in the uniform variable. -> **_glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model))_**

**To remember:**

Rotation is always applied about the pivot point which is [0, 0, 0] (center of the screen).
So if we first move the object and then rotate, we will have diffrent result than first rotate and then move.

a) **Translation:**

**Theory:**

![image](https://user-images.githubusercontent.com/72278818/133167777-45677134-3cdb-4441-af32-d68981f37ff8.png)

**Effect:**

![window_moving_translation_model_matrices](https://user-images.githubusercontent.com/72278818/129083963-c3e6e636-8b54-4472-bbc7-8a3d4bb4aac3.gif)

b) **Rotation:**

**Theory:**

![image](https://user-images.githubusercontent.com/72278818/133167921-c6e905f3-0a9c-46c8-a773-1e63de517ff6.png)

**Angle must be in radians.**

**Effect:**

![rotation_by_using_uniforms_model_matrices](https://user-images.githubusercontent.com/72278818/129088692-66de82a2-ada7-4d30-9888-f5951a89c0cf.gif)

c) **Scaling:**

**Theory:**

![image](https://user-images.githubusercontent.com/72278818/133167801-25e1d691-6e91-4abd-9f84-5332a17fd1e1.png)

**Effect:**

![scaling_by_using_uniforms_model_matrices](https://user-images.githubusercontent.com/72278818/129107390-50e9ee26-5106-4b69-9f04-474c6faaf7f9.gif)

d) **Together: Translation, rotation and scaling**

![All_model_matrices_operations_translation_rotation_scaling](https://user-images.githubusercontent.com/72278818/129107905-5b436671-7f1e-4c3d-bb81-80bf45792892.gif)

**5. Date: 18.08.2021**

**To remember:**

Theory about coordinate systems and how to move from to another:

**Moving between spaces using matrices:**

**Screen Space** <-(Part of rendering Pipeline)- **Clipping Space** <-(Projection Matrix)- **View Space** <-(View Matrix)- **World Space** <-(Model Matrix)- **Local Space** 

**Setting the position of the vertex according to the camera (in the vertex shader we are using uniform matrices):**

gl_Position = **projection_matrix** (ortogonal or perspective (setting the way of looking from the camera) * **view_matrix** (see from the point of camera) * **model_matrix** (move object in the world space) * **vec4(pos, 1.0)** (local position)

**6. Date: 19.08.2021**

**1. Interpolation** between three points is made during the process of rasterization and fragment shader.
Fragment shader interpolate between values to get a specific one for example if you have red and blue vertex, fragment shader will interpolate between them and the center will be some mix blue and red. You won't notice the interpolation if you have vertecies with the same colour!

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/130041157-e59acef9-8d0e-44f5-aebc-e1efdf8d6168.png)

**2. Indexed Draws**

**Steps:**

**AFTER BINDING VAO:**

1. Put indices in the array.
2. Generate IBO id -> **_glGenBuffers(1, &IBO);_**
3. Bind the IBO with selected id. -> **_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);_**
4. Put the data to this buffer (GL_ELEMENT_ARRAY_BUFFER). -> **_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);_**
5. Done.

**AFTER THIS BIND VBO**

When we want do draw:

**AFTER BINDING VAO:**
1. Bind the IBO -> **_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, "ID of IBO");_**
2. Draw the elements -> **_gLDrawElements(GL_TRIANGLES, "Number of vertices", "Type of indices", 0);_**

**Effect:**

**a) Without Depth Test:**

![pyramid](https://user-images.githubusercontent.com/72278818/130054273-f91f6823-477c-4239-b92a-6b5599f2adba.gif)

**b) With Depth Test:**

Steps to achive it:
1. Enable the Depth test before setting the viewport. -> **_glEnable(DEPTH_TEST);_**
2. When we are clearing the colour buffer, we have to clear the depth buffer. -> **_glClear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);_**

![pyramid_with_depth_test](https://user-images.githubusercontent.com/72278818/130055414-7c25cfd3-e55a-498b-a923-77e34b18d7cd.gif)

**3. Using projection matrix (how camera would see (not relative, because we are not using view matrix!) things ortogonal/ perspective):**

![image](https://user-images.githubusercontent.com/72278818/133353702-00c80186-d988-416b-943b-b7d0a2fe1092.png)

We are using perspective to achive 3D depth.

![image](https://user-images.githubusercontent.com/72278818/130354262-3966eb04-063c-44f1-a08e-dab70073aabe.png)


To create perspective projection matrix, we have to do:
**glm::mat4 projection = _glm::perspective("angle of looking (usually 45 deg)", "aspect ratio (bufferWidth/ bufferHeight)", "distance near plane (start looking), "far plane(end looking)");_**

We can use projection matrix without using model matrix !

**Effect:**

![projection_matrix](https://user-images.githubusercontent.com/72278818/130062290-6f92d9e4-6790-4df5-b250-4a766310488b.gif)

**4. Abstracting the code and moving it to classes.**

**UML and code:**
![image](https://user-images.githubusercontent.com/72278818/130244276-c08a32da-499c-4224-9df3-2652dbc33d47.png)

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/130121520-ae2eda3e-e1ee-441c-a587-75e40ccaccfc.png)

**7. Date: 22.08.2021**

**Getting the user input and handling mouse and keyboard by using callbacks and setting user pointer.**

![image](https://user-images.githubusercontent.com/72278818/130353044-1fe1e508-aaf0-45e6-8cd8-c9744c3175ab.png)

**Getting the view matrix:**

1. Creating Camera class with fields: position, worldUp, yaw, pitch, front, right, up, moveSpeed, turnSpeed.

![image](https://user-images.githubusercontent.com/72278818/130354179-e819d2d2-e33a-4e57-ac31-0d8d72489069.png)

2. Calculating new front vector based on pitch and yaw:

![image](https://user-images.githubusercontent.com/72278818/130353137-9fed9375-d4eb-495b-a68f-3d12c71acc45.png)

![image](https://user-images.githubusercontent.com/72278818/130353179-ecc351c1-9153-4508-94ed-79f794b49a55.png)

3. Calculating new camera's right vector by using cross product on camera's front vector and world up (sky, standard up).

![image](https://user-images.githubusercontent.com/72278818/130353185-b0268b7c-a616-41dc-a8ef-9d0da6c4408a.png)

4. Calculating new camera's up vector by using cross product on camera's front vector and camera's right vector.

![image](https://user-images.githubusercontent.com/72278818/130353217-39170dd7-55ec-4451-a519-16ccddb3c705.png)

5. Calucating view matrix based on camera's vectors (direction (front), right and up).

![image](https://user-images.githubusercontent.com/72278818/130353236-1837ad5e-ad7c-4877-99a3-996a2946613a.png)

**In the shader we are aplying this view matrix to every vertex (easy).**

**The newest class diagram with code:**

![Diagram_Game_Engine](https://user-images.githubusercontent.com/72278818/130353489-aa2451df-8cc4-4c46-ae95-c3d5b5d799ad.jpg)

**Effect:**

![Moving_Around_Camera](https://user-images.githubusercontent.com/72278818/130354188-0449bcf2-0c8e-4b71-9f4a-33f7c9f119ef.gif)

**8. Date: 27.08.2021**

**Implementing textures to the vertices:**

**Loading the image and setting the texture:**

1. Create variables for storing data: textureID, width, height, bitDepth and file location.
2. Load file and get data with image (unsigned char*) and other params (width, height, bitDepth).
3. Generate texture (similar to VBO/VAO/IBO). -> **_glGenTextures(1, &textureID);_**.
4. Bind the the texture with this id. -> **_glBindTexture(GL_TEXTURE_2D, textureID);_**
5. Set attributes/ params of texture (filters and wrapping). -> **_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T and S, GL_REPEAT);, glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG and Min_FILTER, GL_LINEAR);_**
6. Load the image to texture. -> **glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);**.
7. Generate Mimap. -> **glBindTexture(GL_TEXTURE_2D);**.
8. Unbind texture. -> **_glBindTexture(GL_TEXTURE_2D, 0);_**.
9. Texture is associated with this id :)

**Using the texture:**

1. Activating texture (sampler). -> **_glActiveTexture(GL_TEXTURE0);_**
2. Binding the texture with selected id. -> **_glBindTexture(GL_TEXTURE_2D, textureID);_**
3. Done.

**Setting the texture in fragment shader to fragments:**

1. Getting the the texture via sampler2D.
2. Getting the position of tex coord via in variables from vertex shader (Setting this via attrib pointers and layout locations).
3. Using method: **_color = texture(theTexture, TexCoord);_**
4. Done.

**UML diagram:**

![Diagram_Game_Engine_v0 2](https://user-images.githubusercontent.com/72278818/131906374-f76f0552-4b5a-419c-81c6-ccd3e18a4b46.jpg)

**Effect:**

![textures_gif](https://user-images.githubusercontent.com/72278818/131195688-679c9b52-dcc0-47eb-8056-6dbde155b582.gif)

**9. Date: 12.09.2021**

**Lighting Model:**

![image](https://user-images.githubusercontent.com/72278818/132967201-c8249708-70f7-4f89-910f-d8c892588392.png)

**Phong Lighting Model**- lighting model that is used to create an ilusion of light's reflection. We can achive it by adding three components of lighting together: 

**TARGET: Create the Directional Light (like a sun).**

![image](https://user-images.githubusercontent.com/72278818/133522959-9e4a4529-f537-495a-81e2-be0e75a22a8a.png)

**Light without position and light source.**

All the light coming in parallel together from the infinite distance.

**Needed:**
- colour,
- ambient factor,
- diffuse factor,
- specular factor,
- directon,

**1. Ambient lighting:**

![image](https://user-images.githubusercontent.com/72278818/132967208-33eb9f9d-edf1-4c2d-9a4b-f402d5e7949c.png)

- Lighting that is always present for example like a sun.
- The easiest one.

In order to get the factor of ambient lighting, we have to get the light of colour and strength of ambient.

****Factor of ambient lighting:****

**_ambient = lightColour * ambientStrength_**

****Final colour of fragment:****

**_fragColour = objectColour * ambient_**

Cases:

If ambient is 1 (full light) then all fragment is lit.

Else if ambient is 0.5 (half light) then fragment is in the half of his colour lit.

Else if ambient is 0 (zero light) the fragment is black.

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/132967297-90ff0745-dc4e-464b-bec7-6b1979d04c87.png)

**Class diagram with code:**

![Diagram_Game_Engine_v0 3](https://user-images.githubusercontent.com/72278818/132983280-8374b25c-49ad-41d6-b9cf-fb1ee3d83ea8.jpg)

**2. Diffuse Lighting/ Phong Interpolation**

![image](https://user-images.githubusercontent.com/72278818/132994750-e465f5e3-f5c7-4740-b4f4-412cb20a1f41.png)

- Lighting that is part of phong lighting model that simulate the angle of incidence of light. 
- The light is determinted by the direction of the light source. Bigger angel of the ray from the light source, makes object more dark.

In order to get the angle, we are using dot product on the normalized normal vector from the surface and light source. 

![image](https://user-images.githubusercontent.com/72278818/132994894-e4ec3b42-5bcf-4069-988b-7b30c9f4d7da.png)

**Final equation:**

_v1*v2 = |v1|*|v2| cos(alfa)_

v1 and v2 are normalized so diffuse factor is:

_v1*v2 = cos(alfa)_

Final form:

**_fragColour = objectColour * (ambient + diffuse)_**

**Creating the diffuse lighting:**
1. Setting up the direction of light (like a sun).
2. Setting up the diffuse intensity (power of the sun).
3. Setting up the color of the light that sun crates (white).
4. Getting the uniforms location for these things from the shader program.
5. Setting up the normals in the buffer data for the each vertex. In this case I'm going to use Phong Shading to create the ilusion of the smooth that is opposite to the flat shading.

![image](https://user-images.githubusercontent.com/72278818/132996457-bff0334d-6724-426e-8897-ad0f8b4fa90b.png)

![image](https://user-images.githubusercontent.com/72278818/132995960-bfdb7ef1-44af-460a-83be-0b2d289d5535.png)

![Wazne_Normals](https://user-images.githubusercontent.com/72278818/133085567-2b563e11-6a56-4e95-ad6e-421b458be855.png)

![image](https://user-images.githubusercontent.com/72278818/133353494-cfc80348-9584-4a52-ac45-d4eee4dfe51a.png)

6. Calculating the normals by using average normals from the surface. One triangle with three vertices will have calcaluted the average normal vector values for each vertex. After this Phong Interpolation will happen during the rendering pipeline.

![image](https://user-images.githubusercontent.com/72278818/132995832-cd112047-edd2-4dc1-8ba3-24aeeea1779f.png)

7. Calculating the diffuse factor in the shader by using the dot product on the normal and the direction of the light.
8. Calculating the diffuse colour with multiplying colour of the light times intensity of the light times diffuse factor.
9. Summing up this diffuse colour with ambient colour multiplying with texture colour.

**Shaders:**
![image](https://user-images.githubusercontent.com/72278818/132996029-d0b8f6eb-f354-41d4-b436-814620f5d6b4.png)

**Diagram UML:**

![Diagram_Game_Engine_v0 3](https://user-images.githubusercontent.com/72278818/132996450-87731e3b-ef1b-4c03-a432-c5643aceff49.jpg)

**Effect:**

**Phong Shading:**

![Phong_Shading](https://user-images.githubusercontent.com/72278818/133098527-6c7bd684-c0da-485b-87fa-c3a636da1594.gif)

**Flat Shading:**

![Flat_Shading](https://user-images.githubusercontent.com/72278818/133099647-200a8c0a-8a97-4686-bd93-6391ce410819.gif)

**3. Specular Lighting**

![image](https://user-images.githubusercontent.com/72278818/133165573-54857584-9ae8-44eb-9f78-18fe8e02481f.png)

**Description:**
- It's directed reflected light source.
- Position of the viewer/ camera is needed.
- Makes the mirror effect.
- Combined with ambient lighting and diffuse lighting, gives us Phong Lighting Model.

**Needed Vectors:** 
- light source, 
- normal, 
- light reflection,
- viewer/ camera,

To calculate factor, we need **angle** between the viewer/ camera and the reflected light source around the normal. If angle is bigger then we have smaller light, and if the angle is smaller then we have more light.
To get the angle we need the view/ camera vector and reflected light vector. 
We can achive the reflected light vector by reflecting light source around the normal vector.

We use **dot product** on these vectors (reflected_light and viewer) to get specular factor.

![image](https://user-images.githubusercontent.com/72278818/133167583-ea21022e-d70f-42d2-aaa1-d61c9f94463a.png)

The next step is to apply the material to the object with shininees property. 
If shininess is bigger then object has more metalic material like metalic ball or knife.
If shininess is smaller then object has more soft/mate material like wood oraz skin.

![image](https://user-images.githubusercontent.com/72278818/133166908-62ccad29-83f1-46ed-94a7-0e5ea66f7bdf.png)

**Equation of specular factor:**

![image](https://user-images.githubusercontent.com/72278818/133167446-3bf50bd6-8ea9-43d3-b381-3cfba53a0b89.png)

**Final equation of Phong Lighting model:**

![image](https://user-images.githubusercontent.com/72278818/133167470-ad091165-e576-4a3e-9adf-9785b38eb9b1.png)

**Shaders:**

![image](https://user-images.githubusercontent.com/72278818/133167315-e694e54c-654c-4440-b1a8-b3f0f108d0b0.png)

**UML diagram:**

![Diagram_Game_Engine_v0 4](https://user-images.githubusercontent.com/72278818/133243186-971b207c-e751-411d-a823-3b9426aa47b9.jpg)

**Effect:**

![Specular_lighting](https://user-images.githubusercontent.com/72278818/133249685-8231219a-3165-47ae-942d-a16d57680f8c.gif)

**Kind of lights:**

**1. Spot Lights**

![image](https://user-images.githubusercontent.com/72278818/133519162-8a2b24ee-c406-464a-ac34-4caae8cdd56a.png)

- Light with **position** and emits in every direction.
- Direction is automatically calculated by using fragment position and the lights source. We can get the fragment position by using the idea of the OpenGL interpolation in the shader. Every fragment has a colour and position.
- We can use math for direcational light to calculate the direction vector.

**Attenuation:**

We can achive it by using reciprocal of quadratic function, where the **x** is the distance between the light source and the position of the fragment. 

![image](https://user-images.githubusercontent.com/72278818/133520311-b9dc72b6-9e1f-4c5f-af57-31804b29d0cf.png)

**Equation:**

![image](https://user-images.githubusercontent.com/72278818/133521184-c54ce98b-ec5b-487b-b1b1-37b0d6d856bf.png)

**Where:**

**Distance**- distance between the fragment and the light source.

**Quadratic**- user defined value, usually the lowest one.

**Linear**- user defined value, usually lower than constant.

**Constant**- usually 1.0, because denumerical must be always greater or equal 1.0.

**Diagram UML:**

![Diagram_Game_Engine_v0 5](https://user-images.githubusercontent.com/72278818/133597952-b33aa571-60ee-4d9e-9fb0-99e1d7976a19.jpg)

**Shaders:**

**Vertex shader:**
```GLSL
#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	
	TexCoord = tex;
	
	Normal = mat3(transpose(inverse(model))) * norm;
	
	FragPos = (model * vec4(pos, 1.0)).xyz; 
}
```

**Fragment shader:**

```GLSL
#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColour);
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		direction = normalize(direction);
		
		vec4 colour = CalcLightByDirection(pointLights[i].base, direction);
		float attenuation = pointLights[i].exponent * distance * distance +
							pointLights[i].linear * distance +
							pointLights[i].constant;
		
		totalColour += (colour / attenuation);
	}
	
	return totalColour;
}

void main()
{
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	
	colour = texture(theTexture, TexCoord) * finalColour;
}
```
**Effect:**

![lights](https://user-images.githubusercontent.com/72278818/133621263-44df656d-09a7-4875-8f72-2ef5721cce1d.gif)

![lights02](https://user-images.githubusercontent.com/72278818/133622555-27691fab-093d-4ba0-b9d9-7b872eaacd48.gif)

**Spot lights:**

![image](https://user-images.githubusercontent.com/72278818/133805834-ed5600d3-7d54-4355-af16-f6fe7c4c814c.png)

Works similar to point lights.

**Has:**

**- position** ~ position of light source.

**- attenuation factor** ~ fading.

**- direction** ~ front of the light source.

**- cut-off angle** ~ describes edges of the light.

![image](https://user-images.githubusercontent.com/72278818/133806568-5a6d27e0-e7f6-4cbc-8891-2157f93bfb7f.png)

We need a way to compare "angle to fragment" with "cut off angle". We can do it by using **dot product**.

**Equation:**

![image](https://user-images.githubusercontent.com/72278818/133806839-87aca983-b749-49d0-b2aa-ad555b04324a.png)

**Where:**

**- lightVector** ~ vector from the light source to fragment.

**- lightDirection** ~ front of the light source (the direction that light facing).

Angle to fragment will have values between 0 and 1.

**Fading edges:**

We can fade the edges of the spot light by using scaling.

**General equation for scaling:**

![image](https://user-images.githubusercontent.com/72278818/133807325-5ff4ddff-daad-4e30-98aa-7fd2ed172e2f.png)

**Our equation for scaling the values of edges/ fading:**

![image](https://user-images.githubusercontent.com/72278818/133807389-05a3d7c5-8200-48fb-b623-7fbafdea31f9.png)

**Summary:**

![image](https://user-images.githubusercontent.com/72278818/133807470-34a4fb37-fbf5-45cd-9a6e-9e76a4492a13.png)

**UML diagram:**

![Diagram_Game_Engine_v0 6](https://user-images.githubusercontent.com/72278818/133807506-81680654-2afd-43f2-98a7-9113df8fd83c.jpg)

**Shaders:**

**Vertex shader:**

```GLSL
#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	
	TexCoord = tex;
	
	Normal = mat3(transpose(inverse(model))) * norm;
	
	FragPos = (model * vec4(pos, 1.0)).xyz; 
}
```

**Fragment Shader:**

```GLSL
#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light
{
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColour = vec4(light.colour * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColour);
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	
	vec4 colour = CalcLightByDirection(pLight.base, direction);
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
	
	return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	if(slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base);
		
		return colour * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}
}

vec4 CalcPointLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{		
		totalColour += CalcPointLight(pointLights[i]);
	}
	
	return totalColour;
}

vec4 CalcSpotLights()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)
	{		
		totalColour += CalcSpotLight(spotLights[i]);
	}
	
	return totalColour;
}

void main()
{
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLights();
	finalColour += CalcSpotLights();
	
	colour = texture(theTexture, TexCoord) * finalColour;
}
```
**Effect:**

![Spot_Light](https://user-images.githubusercontent.com/72278818/133827578-494cd9f3-ffe8-478d-82e7-f31be9f5801d.gif)
