# Terrain
This is a terrain generating program based on OpenGL and GLFW.
Note that the basic Camera header and Shader header files were based on https://learnopengl.com/

This is the result of the screenshot
![Screenshot](screenshots/Terrain.png)

I used GL_TRIANGLE_STRIP to make the terrains. Here are the grids that made this terrain.
![Screenshot](screenshots/TerrainGrid.png)

I also made the sequence of the indices of the vertices, considering the command glEnable(GL_CULL_FACE);
The indices order algorithm was developed by me.

For putting on textures, I used the 3D planar projection method, which can be found in section 1.5 of this link 
https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch01.html
