# 🐦 Flappy Bird Game in C++ with OpenGL GLUT

![Flappy Bird Game](https://github.com/mdemrannazirefty/Flappy-Bird-Game-GLUT/raw/main/assets/gameplay.png)

## 🎮 Project Overview

This project is a C++ implementation of the popular **Flappy Bird game** using **OpenGL** and **GLUT**. The game replicates the classic bird-flapping experience, featuring:

- Smooth 2D graphics with dynamic backgrounds.
- Real-time physics for gravity and bird movement.
- Collision detection with pipes and obstacles.
- Score and level tracking.
- Fun visual effects like clouds, flowers, rain, and swaying grass.

### Why This Project?

The project was implemented to:

- Gain practical experience with **OpenGL and GLUT** graphics programming.
- Understand **2D game mechanics**, such as collision detection, physics simulation, and procedural obstacle generation.
- Explore creative design of graphics using C++ without external game engines.

### Significance

This game demonstrates the ability to create engaging, interactive graphics applications with minimal dependencies. It's ideal for learners to understand **game programming, graphics rendering, and animation in C++**.

### Target Audience

- Students learning computer graphics or game development.
- Hobbyists and indie game developers exploring 2D game mechanics.
- Anyone interested in classic arcade-style games and OpenGL programming.

## 📹 Demo Video

Check out the gameplay: [Flappy Bird Demo](https://youtu.be/ZSmQ_o1Cbq4)

## 🛠️ Tools and Libraries Used

- **C++**: Core language for implementation.
- **OpenGL**: For rendering 2D graphics.
- **GLUT**: Windowing and input handling.
- **Math Functions**: `sin`, `cos`, `fmod`, and constants like `M_PI` for animation and shapes.
- **Audio (Windows only)**: `PlaySound()` function to play jump and hit sounds.
- Key OpenGL functions used include:
  - `glBegin()`, `glEnd()`, `glVertex2f()` – drawing shapes.
  - `glColor3f()` – coloring objects.
  - `glRasterPos2f()` and `glutBitmapCharacter()` – text rendering.
  - `glPushMatrix()` / `glPopMatrix()` – managing transformations.
  - `glutTimerFunc()` – controlling frame updates.

## 🧠 Knowledge Applied

### a) For Job Market Purpose

- Understanding graphics programming fundamentals.
- Implementing **real-time game physics and collision detection**.
- Using **OpenGL and C++** for interactive applications.

### b) For Higher Study Purpose

- Learning **procedural content generation** for games.
- Applying mathematical concepts for animations and movements.
- Building **2D game engines** as a foundation for advanced studies.



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
