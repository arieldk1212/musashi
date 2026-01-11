Phase 1 (Days 1-3): The Sprite Renderer. Don't write unique code for every shape. Write one SpriteRenderer class that takes a texture, position, and rotation, and draws a quad. Use instanced rendering if you want to be fancy, but simple VBOs are fine for now.

Phase 2 (Days 4-7): The Game Loop & Input. Since you're already using GLFW, wrap the input into an InputManager. Map keys to actions (e.g., GLFW_KEY_SPACE -> Jump).

Phase 3 (Week 2): Collision & Gameplay. Stick to AABB (Axis-Aligned Bounding Box) collisions. It's just simple math:

Shaders: Spend time on a single "Post-Processing" shader. Adding a simple Bloom effect or a CRT filter makes a low-budget OpenGL game look intentional and "retro-cool."

Batching: If you want to handle thousands of objects (like a Vampire Survivors clone), you must implement Batch Rendering. It’s the difference between 10 FPS and 1000 FPS.
