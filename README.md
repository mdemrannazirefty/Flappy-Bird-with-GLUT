# Flappy Bird Game with OpenGL and GLUT

![Flappy Bird Gameplay](https://github.com/mdemrannazirefty/Flappy-Bird-Game-GLUT/blob/main/Flappy%20Bird%20Game.gif?raw=true)

This project is a classic **Flappy Bird** clone built from the ground up using **C++**, the **OpenGL** graphics library, and the **GLUT (OpenGL Utility Toolkit)**. It is a simple yet comprehensive example of how to create a 2D interactive application without a full-fledged game engine.

The game features custom-drawn graphics, basic physics simulation (gravity), collision detection, and a multi-level difficulty system. It's a great educational tool for anyone interested in learning the fundamentals of computer graphics and game development.

---

### 🎥 Demo Video

Watch the game in action on YouTube: **[Flappy Bird with OpenGL and GLUT Demo](https://youtu.be/ZSmQ_o1Cbq4)**

---

### 🛠️ Tools and Libraries Used

* **C++:** The core programming language.
* **OpenGL:** The industry-standard API for rendering 2D and 3D graphics. This project uses it for all drawing functions.
* **GLUT:** A utility library that simplifies the windowing and event handling for OpenGL applications.
* **Windows Multimedia API:** Used for playing sound effects on Windows.

---

### ✨ Key Features

* **Custom 2D Graphics:** All game objects, including the bird, pipes, clouds, and flowers, are rendered using basic OpenGL primitives (`GL_QUADS`, `GL_TRIANGLES`, `GL_TRIANGLE_FAN`, `GL_LINES`).
* **Game Physics:** A simple gravity system and a jump mechanic are implemented to control the bird's vertical movement.
* **Collision Detection:** The game accurately detects collisions between the bird and the pipes or the ground.
* **Multi-Level Difficulty:** The game progresses through three levels, with the pipes changing in speed, style, and gap size as the score increases.
* **Dynamic Background:** The game's background changes with the level, from a bright daytime sky to a sunset and a rainy, stormy environment.
* **Sound Effects:** Audio feedback is provided for jumping and hitting obstacles.

---

### ⚙️ How to Compile and Run

1.  **Prerequisites:** You need a C++ compiler (like g++) and the GLUT library set up on your system.
2.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/mdemrannazirefty/Flappy-Bird-Game-GLUT.git](https://github.com/mdemrannazirefty/Flappy-Bird-Game-GLUT.git)
    cd Flappy-Bird-Game-GLUT
    ```
3.  **Compile the code:**
    ```bash
    g++ -o flappy_bird flappy_bird.cpp -lglut -lGL -lGLU
    ```
    *Note: The exact command might vary depending on your operating system and compiler setup. You might need to link against `libwinmm.a` on Windows for sound support.*

4.  **Run the game:**
    ```bash
    ./flappy_bird
    ```

---

### 🎮 How to Play

* **Spacebar:** Press the spacebar to make the bird jump.
* **R:** Press 'R' to restart the game after it's over.
* **Esc:** Press the Escape key to exit the game.

---

### 🤝 Contribution

Feel free to fork the repository, open issues, or submit pull requests. All contributions are welcome!
