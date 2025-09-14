#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int windowWidth = 800, windowHeight = 600;
float birdY = 300, birdVelocity = 0, gravity = -0.3f, jumpStrength = 8.0f;
int score = 0, lives = 3, level = 1;
bool gameOver = false;

struct Pipe {
    float x;
    float gapY;
    int style; // tower style: 1=Stone, 2=Red Castle, 3=Metal
} pipe;

struct Cloud {
    float x, y;
    float speed;
} clouds[3];

struct RainDrop {
    float x, y;
    float speed;
};
const int maxDrops = 200;
RainDrop rain[maxDrops];

float gapSize = 150.0f;
float groundOffset = 0;

// ==================== Game Reset ====================
void resetGame() {
    birdY = 300;
    birdVelocity = 0;
    score = 0;
    lives = 3;
    level = 1;
    gapSize = 150.0f;
    pipe.x = windowWidth;
    pipe.gapY = rand() % (windowHeight - 200) + 100;
    pipe.style = rand() % 3 + 1; // Random tower style
    groundOffset = 0;
    gameOver = false;

    for (int i = 0; i < 3; i++) {
        clouds[i].x = rand() % windowWidth;
        clouds[i].y = windowHeight - (rand() % 200 + 100);
        clouds[i].speed = 0.5f + (rand() % 10) / 20.0f;
    }

    for (int i = 0; i < maxDrops; i++) {
        rain[i].x = rand() % windowWidth;
        rain[i].y = rand() % windowHeight;
        rain[i].speed = 4 + rand() % 4;
    }
}

// ==================== Text ====================
void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// ==================== Background ====================
void drawGradientBackground() {
    glBegin(GL_QUADS);
    if (level == 1) {
        glColor3f(0.4f, 0.7f, 1.0f); // Blue sky
        glVertex2f(0, windowHeight);
        glVertex2f(windowWidth, windowHeight);
        glColor3f(0.7f, 0.9f, 1.0f);
        glVertex2f(windowWidth, 0);
        glVertex2f(0, 0);
    } else if (level == 2) {
        glColor3f(1.0f, 0.6f, 0.2f); // Sunset/orange
        glVertex2f(0, windowHeight);
        glVertex2f(windowWidth, windowHeight);
        glColor3f(1.0f, 0.8f, 0.5f);
        glVertex2f(windowWidth, 0);
        glVertex2f(0, 0);
    } else if (level == 3) {
        // Rainy gray gradient
        glColor3f(0.2f, 0.2f, 0.25f); // Dark gray top
        glVertex2f(0, windowHeight);
        glVertex2f(windowWidth, windowHeight);
        glColor3f(0.4f, 0.4f, 0.45f); // Lighter gray bottom
        glVertex2f(windowWidth, 0);
        glVertex2f(0, 0);
    }
    glEnd();
}

// ==================== Bird ====================
void drawBird() {
    int segments = 100;

    glPushMatrix();

    // Body
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.85f, 0.1f);
    glVertex2f(110, birdY);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        float x = 110 + 22 * cos(theta);
        float y = birdY + 16 * sin(theta);
        glColor3f(1.0f - (i / 100.0f) * 0.1f, 0.85f - (i / 100.0f) * 0.1f, 0.1f);
        glVertex2f(x, y);
    }
    glEnd();

    // Tail
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.7f, 0.0f);
    glVertex2f(110, birdY);
    glVertex2f(90, birdY - 10);
    glVertex2f(120, birdY - 15);

    glColor3f(0.8f, 0.6f, 0.0f);
    glVertex2f(120, birdY - 15);
    glVertex2f(130, birdY - 20);
    glVertex2f(115, birdY - 10);
    glEnd();

    // Left wing
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.8f, 0.6f, 0.0f);
    glVertex2f(110, birdY); // Wing base at body center
    glVertex2f(90, birdY + 5);
    glVertex2f(75, birdY);
    glVertex2f(90, birdY - 5);
    glVertex2f(100, birdY - 2);
    glEnd();

    // Head
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.95f, 0.0f);
    glVertex2f(138, birdY + 10);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(138 + 14 * cos(theta), birdY + 10 + 14 * sin(theta));
    }
    glEnd();

    // Eye (white)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex2f(145, birdY + 14);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(145 + 5 * cos(theta), birdY + 14 + 5 * sin(theta));
    }
    glEnd();

    // Pupil (black)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0, 0);
    glVertex2f(146, birdY + 15);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(146 + 2 * cos(theta), birdY + 15 + 2 * sin(theta));
    }
    glEnd();

    // Beak
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex2f(150, birdY + 15);
    glVertex2f(168, birdY + 19);
    glVertex2f(150, birdY + 20);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.95f, 0.45f, 0.0f);
    glVertex2f(150, birdY + 13);
    glVertex2f(168, birdY + 11);
    glVertex2f(150, birdY + 16);
    glEnd();

    glPopMatrix();
}

// ==================== Clouds ====================
void drawCloud(float x, float y) {
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + 20 * cos(theta), y + 15 * sin(theta));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + 25 + 20 * cos(theta), y + 20 * sin(theta));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159f / 180;
        glVertex2f(x + 50 + 20 * cos(theta), y + 15 * sin(theta));
    }
    glEnd();
}

void drawClouds() {
    for (int i = 0; i < 3; i++) {
        drawCloud(clouds[i].x, clouds[i].y);
    }
}

// ==================== Rain ====================
void drawRain() {
    glColor3f(0.f, 0.6f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < maxDrops; i++) {
        glVertex2f(rain[i].x, rain[i].y);
        glVertex2f(rain[i].x, rain[i].y - 8);
    }
    glEnd();
}

// ==================== Ground ====================
void drawGround() {
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, 50);
    glVertex2f(0, 50);
    glEnd();
}

// ==================== Towers ====================
void drawStoneTower(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.4f, 0.45f);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glColor3f(0.7f, 0.7f, 0.75f);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.25f);
    for (float wy = y + 20; wy < y + height - 20; wy += 35)
        for (float wx = x + 5; wx < x + width - 5; wx += 20) {
            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + 8, wy);
            glVertex2f(wx + 8, wy + 15);
            glVertex2f(wx, wy + 15);
            glEnd();
        }
    glColor3f(0.5f, 0.5f, 0.55f);
    float battW = 10;
    for (float bx = x; bx < x + width; bx += battW) {
        glBegin(GL_QUADS);
        glVertex2f(bx, y + height);
        glVertex2f(bx + battW/2, y + height);
        glVertex2f(bx + battW/2, y + height + 12);
        glVertex2f(bx, y + height + 12);
        glEnd();
    }
}

void drawRedCastleTower(float x, float y, float width, float height) {
    int segments = 3;
    float segH = height / segments;
    for (int i = 0; i < segments; i++) {
        float segY = y + i*segH;
        glColor3f(0.8f - i*0.1f, 0.1f, 0.1f);
        glBegin(GL_QUADS);
        glVertex2f(x, segY);
        glVertex2f(x + width, segY);
        glVertex2f(x + width, segY + segH);
        glVertex2f(x, segY + segH);
        glEnd();
        glColor3f(0.2f,0.0f,0.0f);
        glBegin(GL_QUADS);
        glVertex2f(x + 5, segY + 10);
        glVertex2f(x + 15, segY + 10);
        glVertex2f(x + 15, segY + 25);
        glVertex2f(x + 5, segY + 25);
        glEnd();
    }
    glColor3f(0.6f, 0.0f, 0.0f);
    for (float bx = x; bx < x + width; bx += 12) {
        glBegin(GL_QUADS);
        glVertex2f(bx, y + height);
        glVertex2f(bx + 6, y + height);
        glVertex2f(bx + 6, y + height + 15);
        glVertex2f(bx, y + height + 15);
        glEnd();
    }
}

void drawMetalTower(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.6f);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glColor3f(0.3f, 0.3f, 0.35f);
    glVertex2f(x + width, y);
    glVertex2f(x, y);
    glEnd();
    glColor3f(0.6f,0.6f,0.7f);
    for (float sx=x+5; sx<x+width; sx+=8){
        glBegin(GL_LINES);
        glVertex2f(sx, y); glVertex2f(sx, y+height);
        glEnd();
    }
    glColor3f(0.7f,0.7f,0.8f);
    for (float bx=x; bx<x+width; bx+=10){
        glBegin(GL_TRIANGLES);
        glVertex2f(bx, y+height);
        glVertex2f(bx+5, y+height+12);
        glVertex2f(bx+10, y+height);
        glEnd();
    }
}

// ==================== Draw Pipe ====================
void drawPipe() {
    float pipeW = 50.0f;
    float topY = pipe.gapY + gapSize;
    float topHeight = windowHeight - topY;
    float bottomHeight = pipe.gapY - gapSize;

    if (pipe.style == 1) {
        drawStoneTower(pipe.x, topY, pipeW, topHeight);
        drawStoneTower(pipe.x, 0, pipeW, bottomHeight);
    } else if (pipe.style == 2) {
        drawRedCastleTower(pipe.x, topY, pipeW, topHeight);
        drawRedCastleTower(pipe.x, 0, pipeW, bottomHeight);
    } else {
        drawMetalTower(pipe.x, topY, pipeW, topHeight);
        drawMetalTower(pipe.x, 0, pipeW, bottomHeight);
    }
}

// ==================== Level Update ====================
void updateLevel() {
    if (score >= 5 && level == 1) { level = 2; pipe.style = rand()%3+1; gapSize = 100; }
    if (score >= 10 && level == 2) { level = 3; pipe.style = rand()%3+1; gapSize = 80; }
}

// ==================== Update Function ====================
void update(int value) {
    if (!gameOver) {
        birdVelocity += gravity;
        birdY += birdVelocity;
        pipe.x -= 2.0f;
        groundOffset -= 2.0f;
        if (groundOffset < -50) groundOffset = 0;

        if (level == 3) {
            static int dir = 1;
            pipe.gapY += dir * 2;
            if (pipe.gapY > windowHeight - 100 || pipe.gapY < 100) dir *= -1;
        }

        if (pipe.x < -50) {
            pipe.x = windowWidth;
            pipe.gapY = rand() % (windowHeight - 200) + 100;
            pipe.style = rand() % 3 + 1;
            score++;
            updateLevel();
        }

        if (birdY < 0 || birdY + 15 > windowHeight ||
            (pipe.x < 130 && pipe.x + 50 > 100 &&
             (birdY < pipe.gapY - gapSize || birdY + 15 > pipe.gapY + gapSize))) {
            lives--;
            if (lives <= 0) gameOver = true;
            else { birdY=300; birdVelocity=0; pipe.x=windowWidth; }
        }

        for (int i=0;i<3;i++){
            clouds[i].x-=clouds[i].speed;
            if(clouds[i].x<-80){ clouds[i].x=windowWidth+rand()%200; clouds[i].y=windowHeight-(rand()%200+100);}
        }

        if(level==3){
            for(int i=0;i<maxDrops;i++){
                rain[i].y-=rain[i].speed;
                if(rain[i].y<0){ rain[i].y=windowHeight+rand()%100; rain[i].x=rand()%windowWidth;}
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ==================== Display ====================
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGradientBackground();
    drawClouds();
    if(level==3) drawRain();
    drawPipe();
    drawGround();
    drawBird();

    glColor3f(1,1,1);
    drawText(10, windowHeight-20,"Score: "+std::to_string(score));
    drawText(150, windowHeight-20,"Lives: "+std::to_string(lives));
    drawText(250, windowHeight-20,"Level: "+std::to_string(level));

    if(gameOver){
        drawText(windowWidth/2-50,windowHeight/2,"GAME OVER");
        drawText(windowWidth/2-80,windowHeight/2-30,"Press R to Restart");
    }

    glutSwapBuffers();
}

// ==================== Keyboard ====================
void keyboard(unsigned char key,int,int){
    if(key==' ') birdVelocity=jumpStrength;
    if(key=='r'||key=='R') resetGame();
    if(key==27) exit(0);
}

// ==================== Init ====================
void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,windowWidth,0,windowHeight);
}

// ==================== Main ====================
int main(int argc,char** argv){
    srand(time(0));
    resetGame();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(windowWidth,windowHeight);
    glutCreateWindow("Flappy Bird Tower Edition");
    glutFullScreen();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16,update,0);
    glutMainLoop();
    return 0;
}
