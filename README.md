# Terrain
This is a terrain generating program based on OpenGL and GLFW.
Note that the basic Camera header and Shader header files were based on https://learnopengl.com/

This is the screenshot of the result.
![Screenshot](screenshots/Terrain.png)

I used GL_TRIANGLE_STRIP and a heightmap to make the terrains. Here are the grids that form this terrain.
![Screenshot](screenshots/TerrainGrid.png)

I also made the sequence of the indices of the vertices, considering the command glEnable(GL_CULL_FACE). Therefore the performance is significantly better than algorithms that don't use face culling.  
I came up with the algorithm which sets the order of the indices in order to do face culling.  
For putting on textures, I used the 3D planar projection method, which can be found in section 1.5 of this link 
https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch01.html
