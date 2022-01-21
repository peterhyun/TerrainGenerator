# TerrainGenerator
This is a terrain generating program based on a heightmap. One of the most beginner projects I tried right after learning OpenGL.
I used OpenGL version 3.3 and GLFW for this program.
Note that the basic Camera header and Shader header files were based on https://learnopengl.com/

This is the screenshot of the result.
![Screenshot](screenshots/Terrain.png)

I used GL_TRIANGLE_STRIP to make the terrains. Here are the grids that form this terrain.
![Screenshot](screenshots/TerrainGrid.png)

I also made the sequence of the indices of the vertices so that the faces not showing will be culled via the command glEnable(GL_CULL_FACE). Therefore the performance is significantly better than algorithms that don't use face culling.

For putting on textures, I used the 3D planar projection method, which can be found in section 1.5 of this link
https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch01.html
This prevented the textures from being too stretched on steep slopes.
