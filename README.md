# GameEngine-Cpp_OpenGL_PhysX

Hi!
This folder contains everything about my game engine that is during the process of realization.

**Legend:**
* External_Libs ~ contains all external libraries that are used (GLEW and GLFW).
* Repos ~ contains the project with application (Game engine).
* Versions_And_Notes ~ contains all notes written by me and latest versions of game engine.

**Goals:**
1. Implement rendering system by using OpenGL: 
* GLFW for creating the context and handling windows and user inputs. 
* GLEW for manipulating the context in a modern way and handling platform depended extensions.
* GLM for supporting math operations (matrices, vectors).
2. Implement Collision and Physics system by using PhysX from Nvidia.
3. Implement audio system.
4. Implement animation system.
5. Implement AI system.

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

![window_moving_translation_model_matrices](https://user-images.githubusercontent.com/72278818/129083963-c3e6e636-8b54-4472-bbc7-8a3d4bb4aac3.gif)

b) **Rotation:**

![rotation_by_using_uniforms_model_matrices](https://user-images.githubusercontent.com/72278818/129088692-66de82a2-ada7-4d30-9888-f5951a89c0cf.gif)

c) **Scaling:**

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
