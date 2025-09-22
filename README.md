<img src="https://www.wolframcloud.com/obj/resourcesystem/images/f2d/f2dcb501-fd59-4986-b598-2f30ac56d0ac/6009562e6fbfd7a5.png" align="right" width=150 style="margin:20px"/>

# <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=150 style="margin:0px"/></a> Ultra Basic Batch Render | ft. QuadTrees 😎


<em>Simple <a href="https://www.opengl.org"><img src="https://upload.wikimedia.org/wikipedia/commons/e/e9/Opengl-logo.svg" align="center" width=50/></h1></a> project to test the efficiency of QuadTrees and batch rendering.

---

# What I did 💭

- Batch Rendering with customizable batch size
- Up to 8 (I chose 8 just because, but it could depend on the machine) texture units
- Quad Tree implementation to reduce overhead
- Quad Tree can return a list of quads to be rendered
- Quad Tree can use lambdas to call a function directly on every found quad
- Mouse can seamlessly move the scene and change color of intersecting quads

<img src="/assets/200k.png" alt="200k" width="300"/>
<img src="/assets/10k.png" alt="10k" width="300"/>
<img src="/assets/1k.png" alt="1k" width="300"/>

# Sadly 😔
**There is not much to say, I'll keep exploring rendering techniques on future projects**

---

# Improvements 🤯
- [ ] QuadTree could store its memory in root branch and not spread deep in the tree 🌲
- [ ] The renderer could feature a VBO per texture so that the batch is not flushed until there is no more room for quads with that given texture or a new texture is uploaded
- [ ] Instancing/Batching hybrid approach (This simple only-quad project would have worked better instancing, but the point was to test QuadTrees and batching)
- [ ] Multi-threading 🤓
- [ ] Clean up the code (there is always room for that) 🧹

---

# References

[QuadTrees](https://en.wikipedia.org/wiki/Quadtree)
[OpenGL](https://docs.gl/)