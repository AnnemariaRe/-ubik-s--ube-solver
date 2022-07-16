#include <fstream>
#include <iostream>
#include <glut.h>
#include "RubiksCube.cpp"

const int CUBE_SIZE = 15;
const int TIMER = 5;
// обозначаем цвета
unsigned int color[6] = { 0x008000, 0x122FAA, 0xFFF44F, 0xFFFFFF, 0xFF5E00, 0xE32636 };

// проекции угла поворота на оси
int x = 24;
int y = 44;
int z = 0;
// отдаление
double translateZ = -35.0;

RubiksCube cube;

void display() {
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, translateZ);
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    cube.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int) {
    glutTimerFunc(TIMER, timer, 0);
    if (cube.current != -1)
        cube.Rotate(cube.current, 3, -1);

    display();
}

void specialKeys(int key, int, int) {
    // клавиши влево/вправо вращают по Y
    // клавиши вверх/вниз вращают по X
    if (key == GLUT_KEY_UP) {
        x += 5;
        if (x >= 360) x -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_DOWN) {
        x -= 5;
        if (x < 0) x += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT) {
        y += 5;
        if (y >= 360) y -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT) {
        y -= 5;
        if (y < 0) y += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F1) {
        cube.Rotate(0, 3, 1);
    }

    if (key == GLUT_KEY_F2) {
        cube.Rotate(0, 3, -1);
    }

    if (key == GLUT_KEY_F3) {
        cube.Rotate(1, 3, 1);
    }

    if (key == GLUT_KEY_F4) {
        cube.Rotate(1, 3, -1);
    }

    if (key == GLUT_KEY_F5) {
        cube.Rotate(2, 3, 1);
    }

    if (key == GLUT_KEY_F6) {
        cube.Rotate(2, 3, -1);
    }

    if (key == GLUT_KEY_F7) {
        cube.Rotate(3, 3, 1);
    }

    if (key == GLUT_KEY_F8) {
        cube.Rotate(3, 3, -1);
    }

    if (key == GLUT_KEY_F9) {
        cube.Rotate(4, 3, 1);
    }

    if (key == GLUT_KEY_F10) {
        cube.Rotate(4, 3, -1);
    }

    if (key == GLUT_KEY_F11) {
        cube.Rotate(5, 3, 1);
    }

    if (key == GLUT_KEY_F12) {
        cube.Rotate(5, 3, -1);
    }
}

void processMenu(int option) {
    switch (option) {
    case 1:
        cube.read();
        cube.random_generate();
        break;
    case 2:
        cube.solve();
        break;
    case 3:
        cube.pattern();
        break;
    }
}

void createGLUTMenus() {
    glutCreateMenu(processMenu);

    glutAddMenuEntry("random generate", 1);
    glutAddMenuEntry("solve", 2);
    glutAddMenuEntry("pattern", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("Rubik's cube");
    glClearColor(0.95, 0.87, 0.96, 1);

    // освещение
    float ambient[] = { 0.9, 0.9, 0.9, 1.0 };
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // инициализируем куб
    cube.clear(CUBE_SIZE, color);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(TIMER, timer, 0);
    glutSpecialFunc(specialKeys);
    createGLUTMenus();
    glutMainLoop();



    //RubiksCube cube;

    //cube.read();
    ////cube.show();
    ////cube.save();
    //cube.random_generate();
    //cube.show();
    //cube.rotate();
    ////if (!cube.check()) std::cout << "Wrong cube :(" << std::endl;
    //cube.solve();
    ////cube.show();

    return 0;
}