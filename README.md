# Grassy Hill
By Adam Belfki and Joshua Qin

## Overview
This project uses SDL and OpenGL to render an infinite expanse of rolling grass-textured hills, generated procedurally using Perlin noise. Our project was inspired by "Bliss", the default wallpaper for Windows XP and the most viewed photograph in the world. This was the final project deliverable for Northeastern's CS 4300/5310 summer 2022 class on Computer Graphics.

## Technical Accomplishments
In addition to using the principles of lighting, triangle strip terrain generation, coloring, and texturing, we also applied some concepts new to the class, such as procedural terrain generation and the skybox.

### Procedural Terrain
We use Perlin noise to procedurally generate the terrain rather than reading the information from a file. The parameters used to control this procedural generation include the seed to the prlin noise function, scale, persistence, octaves, lacunarity, exponentiation, and terrain height. Each of these options can be adjusted by the user by holding down the corresponding number key `0` + either `Left Shift` to decrease the value or `Right Shift` to increase it.



We pre-set the constants to provide something similar to a rolling hills and mountains effect.

### Infinite Terrain Generation
In addition to procedurally generating the terrain, the terrain also generates itself now infinitely.

In order to accomplish this, we first tried to recompute the heights of all the vertexes within a certain radius of the user. This didn't work well, because the overhead of sending the buffers to the shaders caused noticeable lag even on higher end machines.

Instead, we divided the world into terrain boxes of 128x128 units in area. A single unit represents the most granular scale that we can calculate the heightmaps for. We then calculate which terrain box the user is located in, and then render not only the terrain box the user is in but all the terrain boxes directly adjacent on the top, down, left, right, and diagonals. This way, the user will be able to see rendered terrain in any direction. All of this is calculated using the Perlin noise method, calculated into a heightmap, and passed on to the shader as a VBO.

As the user walks past the boundaries for a terrain box, all terrain boxes that are not adjacent to where the user is currently standing will be de-rendered. We figure out which terrain boxes are adjacent to the one that the user is currently standing in, and we render those boxes at the same time.

For implementing this method, the information that we are rendering and de-rendering is a giant array representing the height map. When figuring out what the next heightmap should be, we actually take the clever approach to optimizing this process. Since we’re only adding three, at most five new blocks of height mapped terrain every time, we can keep most of our data instead of recalculating it. In our code, we shift all of the data that doesn’t need to be recalculated in the array, and we calculate the new heights as necessary.

### SkyBox
The SkyBox is a giant cube that is drawn around the entire visible world. This cube is drawn first, and mapped to a panoramic texture on the inside, giving the illusion of a 360 degree background. We chose to texture our skybox with carefully selected blue sky and white clouds. The skybox's view is then changed such that the user can pan around the skybox with the camera, but the position of the skybox is never changed relative to the user's camera. Because the skybox was simply set a fixed distance from the user, we did not need to pass in index buffers; a separate shader was used to draw the skybox, and custom overrides were made on top of existing abstractions.

Implementing the skybox was particularly difficult, because it required rendering through multiple shaders as well as modifying many of the abstractions in the starter code to work with the unconventional object.

TODO: Adam add comments

### First-Person Walking Mode
In order for users to truly appreciate grassy hill, we decided to create a first-person mode where the y position of the camera would be locked to a certain distance above the y position of the terrain at any given point.

TODO: Adam add comments

## Challenges
We faced a lot of challenges.

The initial scope of the project was going to be much broader. We were going to add a sun as a centralized source of light, add fog, add some very basic physics and moving around options, etc. Most importantly though, we had planned to add a field of billboard grass via GPU instancing, which was originally going to be the main point of the project. All of that had to be cut due to time constraints.

The main challenge we ran into was working with the program architecture provided in the starter code. We found that while the program structure worked well for rendering a set number of objects in a SceneNode, it was very difficult to adopt the same structure alongside more complex strategies we were implementing, like with the skybox and GPU instancing.

The biggest challenge that we were not able to solve is, despite our best attempts to optimize it, there can still be a slight lag especially on machines without dedicated GPUs when leaving one terrain area and entering another. There was also a memory leak that occurred when this happened, although we traced the memory leak to a section of the starter code that we did not write. Although we explored the option of asynchronously updating the vertex shaders VBOs, we decided instead to adopt a simpler solution of "tell the user to get a better computer."

We both worked in different timezones; Adam moved between Rabat and Boston, and Joshua had a full-time job.

### Lessons Learned
If we could go back in time, we would've started this project at least a week earlier. We also learned a lot about C++ and circular dependencies (they're bad)

## Credits
The following resources were used to help build this project:
SkyBox tutorial: https://www.mbsoftworks.sk/tutorials/opengl3/10-skybox/
LearnOpenGL Cubemap tutorial: https://learnopengl.com/Advanced-OpenGL/Cubemaps
3D World Generation #2 (Perlin noise: https://www.youtube.com/watch?v=U9q-jM3-Phc&t=432s
Texture for the skybox: https://favpng.com/png_view/skybox-texture-mapping-cube-mapping-desktop-wallpaper-png/H0P4RPYu
Grass texture: https://www.istockphoto.com/illustrations/grass-texture
Starter code: http://www.mshah.io/comp/Summer22/Graphics/public/index.php