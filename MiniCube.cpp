#include <glut.h>
#include <fstream>


class MiniCube {
private:

    // шесть цветов граней куба
    int color[6];
    // для хранения RGB цветов
    unsigned char rgb_color[3];

public:

    // размер ребра
    double size;

    void rotate_x() {
        std::swap(color[5], color[3]);
        std::swap(color[3], color[4]);
        std::swap(color[4], color[2]);
    }

    void rotate_y() {
        std::swap(color[2], color[1]);
        std::swap(color[1], color[3]);
        std::swap(color[3], color[0]);
    }

    void rotate_z() {
        std::swap(color[0], color[4]);
        std::swap(color[4], color[1]);
        std::swap(color[1], color[5]);
    }

    void set_color(int i, int color) {
        this->color[i] = color;
    }

    unsigned char* rgb(int i) {
        // разбиваем color[i] на 3 составляющих
        rgb_color[0] = color[i] >> 16;
        rgb_color[1] = color[i] >> 8;
        rgb_color[2] = color[i];

        return rgb_color;
    }

    // отрисовка куба:

    // устанавливаем цвет и нормали
    void draw() {
        glPushMatrix();
        glBegin(GL_QUADS);

        // верх
        glColor3ubv(rgb(0));
        glNormal3f(0, 0, 1);
        glVertex3f(size, size, size);
        glVertex3f(0, size, size);
        glVertex3f(0, 0, size);
        glVertex3f(size, 0, size);

        // низ
        glColor3ubv(rgb(1));
        glNormal3f(0, 0, -1);
        glVertex3f(size, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, size, 0);
        glVertex3f(size, size, 0);

        // спереди
        glColor3ubv(rgb(2));
        glNormal3f(0, -1, 0);
        glVertex3f(size, 0, size);
        glVertex3f(0, 0, size);
        glVertex3f(0, 0, 0);
        glVertex3f(size, 0, 0);

        // сзади
        glColor3ubv(rgb(3));
        glNormal3f(0, 1, 0);
        glVertex3f(size, size, 0);
        glVertex3f(0, size, 0);
        glVertex3f(0, size, size);
        glVertex3f(size, size, size);

        // слева
        glColor3ubv(rgb(4));
        glNormal3f(-1, 0, 0);
        glVertex3f(0, size, size);
        glVertex3f(0, size, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, size);

        // справа
        glColor3ubv(rgb(5));
        glNormal3f(1, 0, 0);
        glVertex3f(size, size, 0);
        glVertex3f(size, size, size);
        glVertex3f(size, 0, size);
        glVertex3f(size, 0, 0);

        glEnd();
        glPopMatrix();
    }

    // отрисовка куба со смещением (x, y, z)
    void draw(double x, double y, double z) {
        glPushMatrix();
        glTranslated(x, y, z);
        draw();
        glPopMatrix();
    }
};