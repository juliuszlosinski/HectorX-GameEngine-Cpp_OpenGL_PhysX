# GameEngine-Cpp_OpenGL_PhysX

Hi!
This folder contains everything about my game engine that is during the process of realization.

**Legend:**
* External_Libs ~ contains all external libraries that are used (GLEW and GLFW).
* Repos ~ contains the project with application (Game engine).
* Versions_And_Notes ~ contains all notes written by me and latest versions of game engine.

**Goals:**
1. Implement rendering system by using OpenGL: 
GLFW for creating the context and handling windows and user inputs. 
GLEW for manipulating the context in a modern way and handling platform depended extensions.
2. Implement physics system by using PhysX from Nvidia.
3. Support audio.

# Current progress:

**1. Date: 6.08.2021**

Creating the window with context using GLFW and initializing GLEW for using modern OpenGL.
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

**Effect:**

![image](https://user-images.githubusercontent.com/72278818/128777097-bc424d23-56b7-4c5d-b0ab-b6aa6b4274f2.png)

**3. Date: 10.08.2021**

Moving window by using uniforms (the easiest way -> without model matrices):

![window_moving](https://user-images.githubusercontent.com/72278818/128925107-7e71ac97-a1b1-48f2-a3f9-dc1ac24f1a77.gif)

**4. Date: 11.08.2021**

Appling operations to the triangle by using uniforms and _**model matrices:**_

a) **Translation:**

![window_moving_translation_model_matrices](https://user-images.githubusercontent.com/72278818/129083963-c3e6e636-8b54-4472-bbc7-8a3d4bb4aac3.gif)

b) **Rotation:**

![rotation_by_using_uniforms_model_matrices](https://user-images.githubusercontent.com/72278818/129088692-66de82a2-ada7-4d30-9888-f5951a89c0cf.gif)

c) **Scaling:**

![scaling_by_using_uniforms_model_matrices](https://user-images.githubusercontent.com/72278818/129107390-50e9ee26-5106-4b69-9f04-474c6faaf7f9.gif)

d) **Together: Translation, rotation and scaling**

![All_model_matrices_operations_translation_rotation_scaling](https://user-images.githubusercontent.com/72278818/129107905-5b436671-7f1e-4c3d-bb81-80bf45792892.gif)
