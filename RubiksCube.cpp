#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <glut.h>
#include "MiniCube.cpp"
#include "Side.cpp"


/*                                      ______
         a b c                         |      |
         d e f                         |  up  |                        |  front - 0 - red
         g h k                   ______|______|_____________           |  back - 1 - orange
  a b c  a b c  a b c  a b c    |      |      |      |      |          |  left - 2 - blue
  d e f  d e f  d e f  d e f    | left |front |right | back |          |  right - 3 - green
  g h k  g h k  g h k  g h k    |______|______|______|______|          |  up - 4 - yellow
         a b c                         |      |                        |  down - 5 - white
         d e f                         | down |
         g h k                         |______|
*/


class RubiksCube {

private:
    Side front{}, back{}, up{}, down{}, left{}, right{}; // 6 граней куба


    int _angle[3];
    bool if_ok[3][3][3];

    MiniCube tmp[3][3];
    // 27 частей
    MiniCube arr[3][3][3];
    // храним угол поворота каждой грани
    int rotates[6];
    // размер кубика
    double size;
    // цвета граней
    unsigned int color[6];
    // скорость поворота
    int speed_turns = 3;


    // повороты:
    void Front_rotate() {
        int a = front.a;
        front.a = front.g;
        front.g = front.k;
        front.k = front.c;
        front.c = a;
        int b = front.b;
        front.b = front.d;
        front.d = front.h;
        front.h = front.f;
        front.f = b;

        int tmp_up_g = up.g;
        int tmp_up_h = up.h;
        int tmp_up_k = up.k;

        up.g = left.k;
        up.h = left.f;
        up.k = left.c;
        left.k = down.c;
        left.f = down.b;
        left.c = down.a;
        down.a = right.g;
        down.b = right.d;
        down.c = right.a;
        right.a = tmp_up_g;
        right.d = tmp_up_h;
        right.g = tmp_up_k;

        Rotate(5, speed_turns, -1);
    }

    void Front_counter_rotate() {
        int a = front.a;
        front.a = front.c;
        front.c = front.k;
        front.k = front.g;
        front.g = a;
        int b = front.b;
        front.b = front.f;
        front.f = front.h;
        front.h = front.d;
        front.d = b;

        int tmp_up_g = up.g;
        int tmp_up_h = up.h;
        int tmp_up_k = up.k;

        up.g = right.a;
        up.h = right.d;
        up.k = right.g;
        right.a = down.c;
        right.d = down.b;
        right.g = down.a;
        down.c = left.k;
        down.b = left.f;
        down.a = left.c;
        left.k = tmp_up_g;
        left.f = tmp_up_h;
        left.c = tmp_up_k;

        Rotate(5, speed_turns, 1);
    }

    void Back_rotate() {
        int a = back.a;
        back.a = back.g;
        back.g = back.k;
        back.k = back.c;
        back.c = a;
        int b = back.b;
        back.b = back.d;
        back.d = back.h;
        back.h = back.f;
        back.f = b;

        int tmp_up_a = up.a;
        int tmp_up_b = up.b;
        int tmp_up_c = up.c;

        up.a = right.c;
        up.b = right.f;
        up.c = right.k;
        right.c = down.k;
        right.f = down.h;
        right.k = down.g;
        down.k = left.g;
        down.h = left.d;
        down.g = left.a;
        left.a = tmp_up_c;
        left.d = tmp_up_b;
        left.g = tmp_up_a;

        Rotate(4, speed_turns, 1);
    }

    void Back_counter_rotate() {
        int a = back.a;
        back.a = back.c;
        back.c = back.k;
        back.k = back.g;
        back.g = a;
        int b = back.b;
        back.b = back.f;
        back.f = back.h;
        back.h = back.d;
        back.d = b;

        int tmp_up_a = up.a;
        int tmp_up_b = up.b;
        int tmp_up_c = up.c;

        up.a = left.g;
        up.b = left.d;
        up.c = left.a;
        left.g = down.k;
        left.d = down.h;
        left.a = down.g;
        down.k = right.c;
        down.h = right.f;
        down.g = right.k;
        right.c = tmp_up_a;
        right.f = tmp_up_b;
        right.k = tmp_up_c;

        Rotate(4, speed_turns, -1);
    }

    void Right_rotate() {
        int a = right.a;
        right.a = right.g;
        right.g = right.k;
        right.k = right.c;
        right.c = a;
        int b = right.b;
        right.b = right.d;
        right.d = right.h;
        right.h = right.f;
        right.f = b;

        int tmp_up_k = up.k;
        int tmp_up_f = up.f;
        int tmp_up_c = up.c;

        up.k = front.k;
        up.f = front.f;
        up.c = front.c;
        front.k = down.k;
        front.f = down.f;
        front.c = down.c;
        down.k = back.a;
        down.f = back.d;
        down.c = back.g;
        back.a = tmp_up_k;
        back.d = tmp_up_f;
        back.g = tmp_up_c;

        Rotate(0, speed_turns, 1);
    }

    void Right_counter_rotate() {
        int a = right.a;
        right.a = right.c;
        right.c = right.k;
        right.k = right.g;
        right.g = a;
        int b = right.b;
        right.b = right.f;
        right.f = right.h;
        right.h = right.d;
        right.d = b;

        int tmp_up_k = up.k;
        int tmp_up_f = up.f;
        int tmp_up_c = up.c;

        up.k = back.a;
        up.f = back.d;
        up.c = back.g;
        back.a = down.k;
        back.d = down.f;
        back.g = down.c;
        down.k = front.k;
        down.f = front.f;
        down.c = front.c;
        front.k = tmp_up_k;
        front.f = tmp_up_f;
        front.c = tmp_up_c;

        Rotate(0, speed_turns, -1);
    }

    void Left_rotate() {
        int a = left.a;
        left.a = left.g;
        left.g = left.k;
        left.k = left.c;
        left.c = a;
        int b = left.b;
        left.b = left.d;
        left.d = left.h;
        left.h = left.f;
        left.f = b;

        int tmp_up_a = up.a;
        int tmp_up_d = up.d;
        int tmp_up_g = up.g;

        up.a = back.k;
        up.d = back.f;
        up.g = back.c;
        back.k = down.a;
        back.f = down.d;
        back.c = down.g;
        down.a = front.a;
        down.d = front.d;
        down.g = front.g;
        front.a = tmp_up_a;
        front.d = tmp_up_d;
        front.g = tmp_up_g;

        Rotate(1, speed_turns, -1);
    }

    void Left_counter_rotate() {
        int a = left.a;
        left.a = left.c;
        left.c = left.k;
        left.k = left.g;
        left.g = a;
        int b = left.b;
        left.b = left.f;
        left.f = left.h;
        left.h = left.d;
        left.d = b;

        int tmp_up_a = up.a;
        int tmp_up_d = up.d;
        int tmp_up_g = up.g;

        up.a = front.a;
        up.d = front.d;
        up.g = front.g;
        front.a = down.a;
        front.d = down.d;
        front.g = down.g;
        down.a = back.k;
        down.d = back.f;
        down.g = back.c;
        back.k = tmp_up_a;
        back.f = tmp_up_d;
        back.c = tmp_up_g;

        Rotate(1, speed_turns, 1);
    }

    void Up_rotate() {
        int a = up.a;
        up.a = up.g;
        up.g = up.k;
        up.k = up.c;
        up.c = a;
        int b = up.b;
        up.b = up.d;
        up.d = up.h;
        up.h = up.f;
        up.f = b;

        int tmp_back_c = back.c;
        int tmp_back_b = back.b;
        int tmp_back_a = back.a;

        back.c = left.c;
        back.b = left.b;
        back.a = left.a;
        left.c = front.c;
        left.b = front.b;
        left.a = front.a;
        front.c = right.c;
        front.b = right.b;
        front.a = right.a;
        right.c = tmp_back_c;
        right.b = tmp_back_b;
        right.a = tmp_back_a;

        Rotate(3, speed_turns, -1);
    }

    void Up_counter_rotate() {
        int a = up.a;
        up.a = up.c;
        up.c = up.k;
        up.k = up.g;
        up.g = a;
        int b = up.b;
        up.b = up.f;
        up.f = up.h;
        up.h = up.d;
        up.d = b;

        int tmp_back_c = back.c;
        int tmp_back_b = back.b;
        int tmp_back_a = back.a;

        back.c = right.c;
        back.b = right.b;
        back.a = right.a;
        right.c = front.c;
        right.b = front.b;
        right.a = front.a;
        front.c = left.c;
        front.b = left.b;
        front.a = left.a;
        left.c = tmp_back_c;
        left.b = tmp_back_b;
        left.a = tmp_back_a;

        Rotate(3, speed_turns, 1);
    }

    void Down_rotate() {
        int a = down.a;
        down.a = down.g;
        down.g = down.k;
        down.k = down.c;
        down.c = a;
        int b = down.b;
        down.b = down.d;
        down.d = down.h;
        down.h = down.f;
        down.f = b;

        int tmp_front_g = front.g;
        int tmp_front_h = front.h;
        int tmp_front_k = front.k;

        front.g = left.g;
        front.h = left.h;
        front.k = left.k;
        left.g = back.g;
        left.h = back.h;
        left.k = back.k;
        back.g = right.g;
        back.h = right.h;
        back.k = right.k;
        right.g = tmp_front_g;
        right.h = tmp_front_h;
        right.k = tmp_front_k;

        Rotate(2, speed_turns, 1);
    }

    void Down_counter_rotate() {
        int a = down.a;
        down.a = down.c;
        down.c = down.k;
        down.k = down.g;
        down.g = a;
        int b = down.b;
        down.b = down.f;
        down.f = down.h;
        down.h = down.d;
        down.d = b;

        int tmp_front_g = front.g;
        int tmp_front_h = front.h;
        int tmp_front_k = front.k;

        front.g = right.g;
        front.h = right.h;
        front.k = right.k;
        right.g = back.g;
        right.h = back.h;
        right.k = back.k;
        back.g = left.g;
        back.h = left.h;
        back.k = left.k;
        left.g = tmp_front_g;
        left.h = tmp_front_h;
        left.k = tmp_front_k;

        Rotate(2, speed_turns, -1);
    }

    void Front_pif_paf() {
        Front_rotate();
        Up_rotate();
        Front_counter_rotate();
        Up_counter_rotate();
    }

    void Back_pif_paf() {
        Back_rotate();
        Up_rotate();
        Back_counter_rotate();
        Up_counter_rotate();
    }

    void Right_pif_paf() {
        Right_rotate();
        Up_rotate();
        Right_counter_rotate();
        Up_counter_rotate();
    }

    void Left_pif_paf() {
        Left_rotate();
        Up_rotate();
        Left_counter_rotate();
        Up_counter_rotate();
    }

    // проверки 

    bool white_cross_check() {
        return (down.b != 5 || down.f != 5 || down.h != 5 || down.d != 5);
    }

    bool white_edges_check() {
        return (down.a != 5 || down.c != 5 || down.g != 5 || down.k != 5);
    }

    bool second_layer_check() {
        return (front.d != 0 || front.f != 0 || right.d != 3 || right.f != 3 ||
            back.f != 1 || back.d != 1 || left.d != 2 || left.f != 2);
    }

    bool yellow_cross_check() {
        return (up.b != 4 || up.f != 4 || up.h != 4 || up.d != 4);
    }

    bool check_yellow_right_cross() {
        return (front.b == 0 && right.b == 3 && back.h == 1 && left.b == 2 &&
            up.b == 4 && up.f == 4 && up.h == 4 && up.d == 4);
    }

    bool check_upper_edges() {
        return ((up.k == 4 && front.c == 0 && right.a == 3) ||
            (up.k == 4 && front.c == 3 && right.a == 0) ||
            (up.k == 0 && front.c == 4 && right.a == 3) ||
            (up.k == 0 && front.c == 3 && right.a == 4) ||
            (up.k == 3 && front.c == 0 && right.a == 4) ||
            (up.k == 3 && front.c == 4 && right.a == 0)) &&
            ((front.a == 0 && left.c == 2 && up.g == 4) ||
                (front.a == 0 && left.c == 4 && up.g == 2) ||
                (front.a == 2 && left.c == 4 && up.g == 0) ||
                (front.a == 2 && left.c == 0 && up.g == 4) ||
                (front.a == 4 && left.c == 2 && up.g == 0) ||
                (front.a == 4 && left.c == 0 && up.g == 2)) &&
            ((up.c == 4 && right.c == 3 && back.a == 1) ||
                (up.c == 4 && right.c == 1 && back.a == 3) ||
                (up.c == 3 && right.c == 4 && back.a == 1) ||
                (up.c == 3 && right.c == 1 && back.a == 4) ||
                (up.c == 1 && right.c == 3 && back.a == 4) ||
                (up.c == 1 && right.c == 4 && back.a == 3)) &&
            ((up.a == 4 && back.c == 1 && left.a == 2) ||
                (up.a == 4 && back.c == 2 && left.a == 1) ||
                (up.a == 2 && back.c == 1 && left.a == 4) ||
                (up.a == 2 && back.c == 4 && left.a == 1) ||
                (up.a == 1 && back.c == 4 && left.a == 2) ||
                (up.a == 1 && back.c == 2 && left.a == 4));
    }

    bool assembly_check() {
        if (front.a == 0 && front.b == 0 && front.c == 0 && front.d == 0 && front.e == 0 &&
            front.f == 0 && front.g == 0 && front.h == 0 && front.k == 0 &&
            back.a == 1 && back.b == 1 && back.c == 1 && back.d == 1 && back.e == 1 &&
            back.f == 1 && back.g == 1 && back.h == 1 && back.k == 1 && left.a == 2 &&
            left.b == 2 && left.c == 2 && left.d == 2 && left.e == 2 && left.f == 2 &&
            left.g == 2 && left.h == 2 && left.k == 2 && right.a == 3 && right.b == 3 &&
            right.c == 3 && right.d == 3 && right.e == 3 && right.f == 3 && right.g == 3 &&
            right.h == 3 && right.k == 3 && up.a == 4 && up.b == 4 && up.c == 4 &&
            up.d == 4 && up.e == 4 && up.f == 4 && up.g == 4 && up.h == 4 && up.k == 4 &&
            down.a == 5 && down.b == 5 && down.c == 5 && down.d == 5 && down.e == 5 &&
            down.f == 5 && down.g == 5 && down.h == 5 && down.k == 5)
            return true;
        else
            return false;
    }

    // сборка

    void first_right_cross() {
        while (white_cross_check()) {
            if (front.f == 5) {
                while (down.f == 5)
                    Down_rotate();
                Right_counter_rotate();
            }

            if (front.d == 5) {
                while (down.d == 5)
                    Down_rotate();
                Left_counter_rotate();
            }

            if (front.b == 5) {
                Front_rotate();
                while (down.f == 5)
                    Down_rotate();
                Right_counter_rotate();
            }

            if (front.h == 5) {
                Front_rotate();
                while (down.d == 5)
                    Down_rotate();
                Left_rotate();
            }

            if (left.f == 5) {
                while (down.b == 5)
                    Down_rotate();
                Front_counter_rotate();
            }

            if (left.d == 5) {
                while (down.d == 5)
                    Down_rotate();
                Back_counter_rotate();
            }

            if (left.b == 5) {
                Left_rotate();
                while (down.b == 5)
                    Down_rotate();
                Front_counter_rotate();
            }

            if (left.h == 5) {
                Left_rotate();
                while (down.h == 5)
                    Down_rotate();
                Back_rotate();
            }

            if (back.f == 5) {
                while (down.d == 5)
                    Down_rotate();
                Left_counter_rotate();
            }

            if (back.d == 5) {
                while (down.f == 5)
                    Down_rotate();
                Right_rotate();
            }

            if (back.b == 5) {
                Back_rotate();
                while (down.d == 5)
                    Down_rotate();
                Right_rotate();
            }

            if (back.h == 5) {
                Back_rotate();
                while (down.f == 5)
                    Down_rotate();
                Left_counter_rotate();
            }

            if (right.f == 5) {
                while (down.h == 5)
                    Down_rotate();
                Back_rotate();
            }

            if (right.d == 5) {
                while (down.b == 5)
                    Down_rotate();
                Front_rotate();
            }

            if (right.b == 5) {
                Right_rotate();
                while (down.h == 5)
                    Down_rotate();
                Front_rotate();
            }

            if (right.h == 5) {
                Right_rotate();
                while (down.b == 5)
                    Down_rotate();
                Left_rotate();
            }

            if (up.f == 5) {
                while (down.f == 5)
                    Down_rotate();
                Right_rotate();
                Right_rotate();
            }

            if (up.d == 5) {
                while (down.d == 5)
                    Down_rotate();
                Left_rotate();
                Left_rotate();
            }

            if (up.b == 5) {
                while (down.h == 5)
                    Down_rotate();
                Back_rotate();
                Back_rotate();
            }

            if (up.h == 5) {
                while (down.b == 5)
                    Down_rotate();
                Front_rotate();
                Front_rotate();
            }
        } // собран нижний крест

        while (front.h != front.e || down.b != 5)
            Down_rotate();
        Front_rotate();
        Front_rotate();

        while (right.h != right.e || down.f != 5)
            Down_rotate();
        Right_rotate();
        Right_rotate();

        while (back.h != back.e || down.h != 5)
            Down_rotate();
        Back_rotate();
        Back_rotate();

        while (left.h != left.e || down.d != 5)
            Down_rotate();
        Left_rotate();
        Left_rotate();

        Front_rotate();
        Front_rotate();
        Right_rotate();
        Right_rotate();
        Back_rotate();
        Back_rotate();
        Left_rotate();
        Left_rotate();  // собран правильный нижний крест
    }

    void first_layer_edges() {
        while (white_edges_check()) {
            if (back.a == 5) {
                if ((up.c == 3 && right.c == 1) || (up.c == 1 && right.c == 3))
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();

                if (back.a == 5 && ((up.c == 3 && right.c == 0) || (up.c == 0 && right.c == 3))) {
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (back.a == 5 && ((up.c == 2 && right.c == 0) || (up.c == 0 && right.c == 2))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (back.a == 5 && ((up.c == 2 && right.c == 1) || (up.c == 1 && right.c == 2))) {
                    Up_counter_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (back.c == 5) {
                if ((up.a == 3 && left.a == 1) || (up.a == 1 && left.a == 3)) {
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (back.c == 5 && ((up.a == 3 && left.a == 0) || (up.a == 0 && left.a == 3))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (back.c == 5 && ((up.a == 2 && left.a == 0) || (up.a == 0 && left.a == 2))) {
                    Up_counter_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (back.c == 5 && ((up.a == 2 && left.a == 1) || (up.a == 1 && left.a == 2)))
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
            }

            if (up.c == 5) {
                if ((back.a == 3 && right.c == 1) || (back.a == 1 && right.c == 3))
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();

                if ((back.a == 3 && right.c == 0) || (back.a == 0 && right.c == 3)) {
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if ((back.a == 2 && right.c == 0) || (back.a == 0 && right.c == 2)) {
                    Up_rotate();
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if ((back.a == 1 && right.c == 2) || (back.a == 2 && right.c == 1)) {
                    Up_counter_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (up.a == 5) {
                if ((back.c == 3 && left.a == 1) || (back.c == 1 && left.a == 3)) {
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (up.a == 5 && ((back.c == 3 && left.a == 0) || (back.c == 0 && left.a == 3))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (up.a == 5 && ((back.c == 2 && left.a == 0) || (back.c == 0 && left.a == 2))) {
                    Up_counter_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (up.a == 5 && ((back.c == 2 && left.a == 1) || (back.c == 1 && left.a == 2)))
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
            }

            if (up.g == 5) {
                if ((front.a == 3 && left.c == 1) || (front.a == 1 && left.c == 3)) {
                    Up_rotate();
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (up.g == 5 && ((front.a == 3 && left.c == 0) || (front.a == 0 && left.c == 3))) {
                    Up_counter_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (up.g == 5 && ((front.a == 2 && left.c == 0) || (front.a == 0 && left.c == 2)))
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();

                if (up.g == 5 && ((front.a == 2 && left.c == 1) || (front.a == 1 && left.c == 2))) {
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (up.k == 5) {
                if ((front.c == 3 && right.a == 1) || (front.c == 1 && right.a == 3)) {
                    Up_counter_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (up.k == 5 && ((front.c == 3 && right.a == 0) || (front.c == 0 && right.a == 3)))
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();

                if (up.k == 5 && ((front.c == 2 && right.a == 0) || (front.c == 0 && right.a == 2))) {
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (up.k == 5 && ((front.c == 2 && right.a == 1) || (front.c == 1 && right.a == 2))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (right.c == 5) {
                if ((up.c == 3 && back.a == 1) || (up.c == 1 && back.a == 3))
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();

                if (right.c == 5 && ((up.c == 3 && back.a == 0) || (up.c == 0 && back.a == 3))) {
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (right.c == 5 && ((up.c == 2 && back.a == 0) || (up.c == 0 && back.a == 2))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (right.c == 5 && ((up.c == 2 && back.a == 1) || (up.c == 1 && back.a == 2))) {
                    Up_counter_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (right.a == 5) {
                if ((front.c == 3 && up.k == 1) || (front.c == 1 && up.k == 3)) {
                    Up_counter_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (right.a == 5 && ((front.c == 3 && up.k == 0) || (front.c == 0 && up.k == 3)))
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();

                if (right.a == 5 && ((front.c == 2 && up.k == 0) || (front.c == 0 && up.k == 2))) {
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (right.a == 5 && ((front.c == 1 && up.k == 2) || (front.c == 2 && up.k == 1))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (left.c == 5) {
                if ((up.g == 3 && front.a == 1) || (up.g == 1 && front.a == 3)) {
                    Up_rotate();
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (left.c == 5 && ((up.g == 3 && front.a == 0) || (up.g == 0 && front.a == 3))) {
                    Up_counter_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (left.c == 5 && ((up.g == 2 && front.a == 0) || (up.g == 0 && front.a == 2)))
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();

                if (left.c == 5 && ((up.g == 2 && front.a == 1) || (up.g == 1 && front.a == 2))) {
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }


            if (left.a == 5) {
                if ((up.a == 3 && back.c == 1) || (up.a == 1 && back.c == 3)) {
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (left.a == 5 && ((up.a == 3 && back.c == 0) || (up.a == 0 && back.c == 3))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (left.a == 5 && ((up.a == 2 && back.c == 0) || (up.a == 0 && back.c == 2))) {
                    Up_counter_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (left.a == 5 && ((up.a == 1 && back.c == 2) || (up.a == 2 && back.c == 1)))
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
            }

            if (front.c == 5) {
                if ((up.k == 3 && right.a == 1) || (up.k == 1 && right.a == 3)) {
                    Up_counter_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (front.c == 5 && ((up.k == 3 && right.a == 0) || (up.k == 0 && right.a == 3)))
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();

                if (front.c == 5 && ((up.k == 2 && right.a == 0) || (up.k == 0 && right.a == 2))) {
                    Up_rotate();
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();
                }

                if (front.c == 5 && ((up.k == 1 && right.a == 2) || (up.k == 2 && right.a == 1))) {
                    Up_rotate();
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if (front.a == 5) {
                if ((up.g == 3 && left.c == 1) || (up.g == 1 && left.c == 3)) {
                    Up_rotate();
                    Up_rotate();
                    while (down.k != 5 || right.k != 3 || back.g != 1)
                        Back_pif_paf();
                }

                if (front.a == 5 && ((up.g == 3 && left.c == 0) || (up.g == 0 && left.c == 3))) {
                    Up_counter_rotate();
                    while (down.c != 5 || front.k != 0 || right.g != 3)
                        Right_pif_paf();
                }

                if (front.a == 5 && ((up.g == 2 && left.c == 0) || (up.g == 0 && left.c == 2)))
                    while (down.a != 5 || left.k != 2 || front.g != 0)
                        Front_pif_paf();

                if (front.a == 5 && ((up.g == 2 && left.c == 1) || (up.g == 1 && left.c == 2))) {
                    Up_rotate();
                    while (down.g != 5 || back.k != 1 || left.g != 2)
                        Left_pif_paf();
                }
            }

            if ((front.k == 5 && right.g == 3 && down.c == 0) || (front.k == 5 && right.g == 0 && down.c == 3) ||
                (front.k == 3 && right.g == 5 && down.c == 0) || (front.k == 0 && right.g == 5 && down.c == 3))
                while (down.c != 5 || front.k != 0 || right.g != 3)
                    Right_pif_paf();

            if ((back.g == 5 && right.k == 3 && down.k == 1) || (back.g == 5 && right.k == 1 && down.k == 3) ||
                (back.g == 3 && right.k == 5 && down.k == 1) || (back.g == 1 && right.k == 5 && down.k == 3))
                while (down.k != 5 || back.g != 1 || right.k != 3)
                    Back_pif_paf();

            if ((back.k == 5 && left.g == 2 && down.g == 1) || (back.k == 5 && left.g == 1 && down.g == 2) ||
                (back.k == 2 && left.g == 5 && down.g == 1) || (back.k == 1 && left.g == 5 && down.g == 2))
                while (down.g != 5 || back.k != 1 || left.g != 2)
                    Left_pif_paf();

            if ((left.k == 5 && front.g == 0 && down.a == 2) || (left.k == 5 && front.g == 2 && down.a == 0) ||
                (left.k == 0 && front.g == 5 && down.a == 2) || (left.k == 2 && front.g == 5 && down.a == 0))
                while (down.a != 5 || left.k != 2 || front.g != 0)
                    Front_pif_paf();

            if (down.c == 5 && ((front.k != 0 && front.k != 3) || (right.g != 0 && right.g != 3)))
                Right_pif_paf();

            if (down.k == 5 && ((right.k != 1 && right.k != 3) || (back.g != 1 && back.g != 3)))
                Back_pif_paf();

            if (down.g == 5 && ((back.k != 1 && back.k != 2) || (left.g != 1 && left.g != 2)))
                Left_pif_paf();

            if (down.a == 5 && ((front.g != 0 && front.g != 2) || (left.k != 0 && left.k != 2)))
                Front_pif_paf();

            if (front.k == 5 || right.g == 5)
                Right_pif_paf();

            if (right.k == 5 || back.g == 5)
                Back_pif_paf();

            if (back.k == 5 || left.g == 5)
                Left_pif_paf();

            if (front.g == 5 || left.k == 5)
                Front_pif_paf();

            // первый слой собран
        }
    }

    void medium_layer_edges() {
        int prev, count;

        while (second_layer_check()) {
            count = 0;
            prev = -1;

            while (count > prev) {
                prev = count;

                if (front.b == 0 || right.b == 0 || back.b == 0 || left.b == 0) {
                    while (front.b != 0)
                        Up_rotate();

                    if (up.h == 3) {
                        count++;
                        Up_rotate();
                        Right_pif_paf();
                        Front_counter_rotate();
                        Up_counter_rotate();
                        Front_rotate();
                        Up_rotate();
                    }
                    else if (up.h == 2) {
                        count++;
                        Up_counter_rotate();
                        Left_counter_rotate();
                        Up_counter_rotate();
                        Left_rotate();
                        Up_rotate();
                        Front_pif_paf();
                    }
                }

                if (front.b == 3 || right.b == 3 || back.b == 3 || left.b == 3) {
                    while (right.b != 3)
                        Up_rotate();

                    if (up.f == 1) {
                        count++;
                        Up_rotate();
                        Back_pif_paf();
                        Right_counter_rotate();
                        Up_counter_rotate();
                        Right_rotate();
                        Up_rotate();
                    }
                    else if (up.f == 0) {
                        count++;
                        Up_counter_rotate();
                        Front_counter_rotate();
                        Up_counter_rotate();
                        Front_rotate();
                        Up_rotate();
                        Right_pif_paf();
                    }
                }
                if (front.b == 1 || right.b == 1 || back.b == 1 || left.b == 1) {
                    while (back.b != 1)
                        Up_rotate();

                    if (up.b == 2) {
                        count++;
                        Up_rotate();
                        Left_pif_paf();
                        Back_counter_rotate();
                        Up_counter_rotate();
                        Back_rotate();
                        Up_rotate();
                    }
                    else if (up.b == 3) {
                        count++;
                        Up_counter_rotate();
                        Right_counter_rotate();
                        Up_counter_rotate();
                        Right_rotate();
                        Up_rotate();
                        Back_pif_paf();
                    }
                }
                if (front.b == 2 || right.b == 2 || back.b == 2 || left.b == 2) {
                    while (left.b != 2)
                        Up_rotate();

                    if (up.d == 0) {
                        count++;
                        Up_rotate();
                        Front_pif_paf();
                        Left_counter_rotate();
                        Up_counter_rotate();
                        Left_rotate();
                        Up_rotate();
                    }
                    else if (up.d == 1) {
                        count++;
                        Up_counter_rotate();
                        Back_counter_rotate();
                        Up_counter_rotate();
                        Back_rotate();
                        Up_rotate();
                        Left_pif_paf();
                    }
                }
            }

            if (front.f != 0) {
                Right_pif_paf();
                Front_counter_rotate();
                Up_counter_rotate();
                Front_rotate();
                Up_rotate();
            }
            if (right.f != 3) {
                Back_pif_paf();
                Right_counter_rotate();
                Up_counter_rotate();
                Right_rotate();
                Up_rotate();
            }
            if (back.f != 1) {
                Left_pif_paf();
                Back_counter_rotate();
                Up_counter_rotate();
                Back_rotate();
                Up_rotate();
            }
            if (left.f != 2) {
                Front_pif_paf();
                Left_counter_rotate();
                Up_counter_rotate();
                Left_rotate();
                Up_rotate();
            }
        }
        // собраны ребра второго сло€
    }

    void upper_right_cross() {
        while (yellow_cross_check()) {
            if (up.b == 4 && up.f == 4 && up.h != 4 && up.d != 4) {
                Left_rotate();
                Front_pif_paf();
                Left_counter_rotate();
            }
            else if (up.b == 4 && up.f != 4 && up.h == 4 && up.d != 4) {
                Left_rotate();
                Front_pif_paf();
                Left_counter_rotate();
            }
            else if (up.b != 4 && up.f == 4 && up.h == 4 && up.d != 4) {
                Back_rotate();
                Left_pif_paf();
                Back_counter_rotate();
            }
            else if (up.b == 4 && up.f != 4 && up.h != 4 && up.d == 4) {
                Front_rotate();
                Right_pif_paf();
                Front_counter_rotate();
            }
            else if (up.b != 4 && up.f == 4 && up.h != 4 && up.d == 4) {
                Front_rotate();
                Right_pif_paf();
                Front_counter_rotate();
            }
            else if (up.b != 4 && up.f != 4 && up.h == 4 && up.d == 4) {
                Right_rotate();
                Back_pif_paf();
                Right_counter_rotate();
            }
            else if (up.b != 4 && up.f != 4 && up.h != 4 && up.d != 4) {
                Front_rotate();
                Right_pif_paf();
                Front_counter_rotate();
            }
        } // собран желтый крест

        bool check = false;
        if (check_yellow_right_cross())
            check = true;
        else {
            Up_rotate();
            if (check_yellow_right_cross())
                check = true;
            else {
                Up_rotate();
                if (check_yellow_right_cross())
                    check = true;
                else {
                    Up_rotate();
                    if (check_yellow_right_cross())
                        check = true;
                }
            } // проверка на правильный желтый крест
        }
        if (!check) {
            while (!check_yellow_right_cross()) {
                Up_rotate();
                if (right.b == 3 && back.b == 1) {
                    Right_rotate();
                    Up_rotate();
                    Right_counter_rotate();
                    Up_rotate();
                    Right_rotate();
                    Up_rotate();
                    Up_rotate();
                    Right_counter_rotate();
                    Up_rotate();
                }
                else if (right.b == 3 && front.b == 0) {
                    Front_rotate();
                    Up_rotate();
                    Front_counter_rotate();
                    Up_rotate();
                    Front_rotate();
                    Up_rotate();
                    Up_rotate();
                    Front_counter_rotate();
                    Up_rotate();
                }
                else if (front.b == 0 && left.b == 2) {
                    Left_rotate();
                    Up_rotate();
                    Left_counter_rotate();
                    Up_rotate();
                    Left_rotate();
                    Up_rotate();
                    Up_rotate();
                    Left_counter_rotate();
                    Up_rotate();
                }
                else if (left.b == 2 && back.b == 1) {
                    Back_rotate();
                    Up_rotate();
                    Back_counter_rotate();
                    Up_rotate();
                    Back_rotate();
                    Up_rotate();
                    Up_rotate();
                    Back_counter_rotate();
                    Up_rotate();
                }
                else if (right.b == 3 && left.b == 2) {
                    Back_rotate();
                    Up_rotate();
                    Back_counter_rotate();
                    Up_rotate();
                    Back_rotate();
                    Up_rotate();
                    Up_rotate();
                    Back_counter_rotate();
                }
                else if (front.b == 0 && back.b == 1) {
                    Right_rotate();
                    Up_rotate();
                    Right_counter_rotate();
                    Up_rotate();
                    Right_rotate();
                    Up_rotate();
                    Up_rotate();
                    Right_counter_rotate();
                }
            }
        }  // собран правильный желтый крест
    }

    void last_layer_edges() {
        while (!check_upper_edges()) {
            if ((up.k == 4 && front.c == 0 && right.a == 3) || (up.k == 4 && front.c == 3 && right.a == 0) ||
                (up.k == 0 && front.c == 4 && right.a == 3) || (up.k == 0 && front.c == 3 && right.a == 4) ||
                (up.k == 3 && front.c == 0 && right.a == 4) || (up.k == 3 && front.c == 4 && right.a == 0)) {
                Up_rotate();
                Right_rotate();
                Up_counter_rotate();
                Left_counter_rotate();
                Up_rotate();
                Right_counter_rotate();
                Up_counter_rotate();
                Left_rotate();
            }
            else if ((front.a == 0 && left.c == 2 && up.g == 4) || (front.a == 0 && left.c == 4 && up.g == 2) ||
                (front.a == 2 && left.c == 4 && up.g == 0) || (front.a == 2 && left.c == 0 && up.g == 4) ||
                (front.a == 4 && left.c == 2 && up.g == 0) || (front.a == 4 && left.c == 0 && up.g == 2)) {
                Up_rotate();
                Front_rotate();
                Up_counter_rotate();
                Back_counter_rotate();
                Up_rotate();
                Front_counter_rotate();
                Up_counter_rotate();
                Back_rotate();
            }
            else if ((up.c == 4 && right.c == 3 && back.a == 1) || (up.c == 4 && right.c == 1 && back.a == 3) ||
                (up.c == 3 && right.c == 4 && back.a == 1) || (up.c == 3 && right.c == 1 && back.a == 4) ||
                (up.c == 1 && right.c == 3 && back.a == 4) || (up.c == 1 && right.c == 4 && back.a == 3)) {
                Up_rotate();
                Back_rotate();
                Up_counter_rotate();
                Front_counter_rotate();
                Up_rotate();
                Back_counter_rotate();
                Up_counter_rotate();
                Front_rotate();
            }
            else if ((up.a == 4 && back.c == 1 && left.a == 2) || (up.a == 4 && back.c == 2 && left.a == 1) ||
                (up.a == 2 && back.c == 1 && left.a == 4) || (up.a == 2 && back.c == 4 && left.a == 1) ||
                (up.a == 1 && back.c == 4 && left.a == 2) || (up.a == 1 && back.c == 2 && left.a == 4)) {
                Up_rotate();
                Left_rotate();
                Up_counter_rotate();
                Right_counter_rotate();
                Up_rotate();
                Left_counter_rotate();
                Up_counter_rotate();
                Right_rotate();
            }
            else {
                Up_rotate();
                Right_rotate();
                Up_counter_rotate();
                Left_counter_rotate();
                Up_rotate();
                Right_counter_rotate();
                Up_counter_rotate();
                Left_rotate();
            }
        }   //ѕравильно поставлены углы

        for (int i = 0; i < 5; i++) {
            if (up.a != 4)
                while (up.a != 4) {
                    Back_rotate();
                    Down_rotate();
                    Back_counter_rotate();
                    Down_counter_rotate();
                }
            Up_rotate();
        } // —обрана желта€ грань

        while (!assembly_check())
            Up_rotate(); // доворачиваем последнюю сторону и кубик собран
    }

public:

    RubiksCube() = default;

    void read() {
        std::ifstream in("cube.in");

        in >> up.a >> up.b >> up.c;
        in >> up.d >> up.e >> up.f;
        in >> up.g >> up.h >> up.k;
        in >> left.a >> left.b >> left.c >> front.a >> front.b >> front.c;
        in >> right.a >> right.b >> right.c >> back.a >> back.b >> back.c;
        in >> left.d >> left.e >> left.f >> front.d >> front.e >> front.f;
        in >> right.d >> right.e >> right.f >> back.d >> back.e >> back.f;
        in >> left.g >> left.h >> left.k >> front.g >> front.h >> front.k;
        in >> right.g >> right.h >> right.k >> back.g >> back.h >> back.k;
        in >> down.a >> down.b >> down.c;
        in >> down.d >> down.e >> down.f;
        in >> down.g >> down.h >> down.k;

        in.close();
    }

    void save() const {
        std::ofstream out("cube.out");

        out << "       " << up.a << " " << up.b << " " << up.c << std::endl;
        out << "       " << up.d << " " << up.e << " " << up.f << std::endl;
        out << "       " << up.g << " " << up.h << " " << up.k << std::endl;
        out << left.a << " " << left.b << " " << left.c << "  " << front.a << " ";
        out << front.b << " " << front.c << "  " << right.a << " " << right.b;
        out << " " << right.c << "  " << back.a << " " << back.b << " " << back.c << std::endl;
        out << left.d << " " << left.e << " " << left.f << "  " << front.d << " " << front.e;
        out << " " << front.f << "  " << right.d << " " << right.e << " " << right.f << "  ";
        out << back.d << " " << back.e << " " << back.f << std::endl;
        out << left.g << " " << left.h << " " << left.k << "  " << front.g << " " << front.h;
        out << " " << front.k << "  " << right.g << " " << right.h << " " << right.k;
        out << "  " << back.g << " " << back.h << " " << back.k << std::endl;
        out << "       " << down.a << " " << down.b << " " << down.c << std::endl;
        out << "       " << down.d << " " << down.e << " " << down.f << std::endl;
        out << "       " << down.g << " " << down.h << " " << down.k << std::endl;

        out.close();
    }

    void show() const {
        //std::cout << "Current state: " << std::endl;
        std::cout << std::endl;
        std::cout << "       " << up.a << " " << up.b << " " << up.c << std::endl;
        std::cout << "       " << up.d << " " << up.e << " " << up.f << std::endl;
        std::cout << "       " << up.g << " " << up.h << " " << up.k << std::endl;
        std::cout << left.a << " " << left.b << " " << left.c << "  " << front.a << " ";
        std::cout << front.b << " " << front.c << "  " << right.a << " " << right.b;
        std::cout << " " << right.c << "  " << back.a << " " << back.b << " " << back.c << std::endl;
        std::cout << left.d << " " << left.e << " " << left.f << "  " << front.d << " " << front.e;
        std::cout << " " << front.f << "  " << right.d << " " << right.e << " " << right.f << "  ";
        std::cout << back.d << " " << back.e << " " << back.f << std::endl;
        std::cout << left.g << " " << left.h << " " << left.k << "  " << front.g << " " << front.h;
        std::cout << " " << front.k << "  " << right.g << " " << right.h << " " << right.k;
        std::cout << "  " << back.g << " " << back.h << " " << back.k << std::endl;
        std::cout << "       " << down.a << " " << down.b << " " << down.c << std::endl;
        std::cout << "       " << down.d << " " << down.e << " " << down.f << std::endl;
        std::cout << "       " << down.g << " " << down.h << " " << down.k << std::endl;
        std::cout << std::endl;
    }

    void random_generate() {
        srand(time(NULL));
        int n = rand() % 40 + 10;

        for (int i = 0; i < n; i++) {
            int x = abs(rand() % 15);

            if (x == 0) Right_rotate();
            else if (x == 1) Right_counter_rotate();
            else if (x == 2) Left_rotate();
            else if (x == 3) Left_counter_rotate();
            else if (x == 4) Front_rotate();
            else if (x == 5) Front_counter_rotate();
            else if (x == 6) Back_rotate();
            else if (x == 7) Back_counter_rotate();
            else if (x == 8) Up_rotate();
            else if (x == 9) Up_counter_rotate();
            else if (x == 10) Down_rotate();
            else if (x == 11) Down_counter_rotate();
            else if (x == 12) Right_pif_paf();
            else if (x == 13) Left_pif_paf();
            else if (x == 14) Front_pif_paf();
            else if (x == 15) Back_pif_paf();
        }

        if (check()) {
            std::cout << "Random spin: " << std::endl;
            show();
        }
        else std::cout << "Wrong cube :(" << std::endl;

    }

    void rotate() {
        std::string side;
        short direction;
        std::cout << "Input command to rotate (\"end 0\" - exit), " << std::endl;
        std::cout << "first side name then the direction (1 - direct, -1 - counter):  " << std::endl;
        std::cin >> side >> direction;

        while (true) {
            if (side == "end") break;

            if (direction == 1) {
                if (side == "front")
                    Front_rotate();
                else if (side == "back")
                    Back_rotate();
                else if (side == "left")
                    Left_rotate();
                else if (side == "right")
                    Right_rotate();
                else if (side == "up")
                    Up_rotate();
                else if (side == "down")
                    Down_rotate();
            }
            else if (direction == -1) {
                if (side == "front")
                    Front_counter_rotate();
                else if (side == "back")
                    Back_counter_rotate();
                else if (side == "left")
                    Left_counter_rotate();
                else if (side == "right")
                    Right_counter_rotate();
                else if (side == "up")
                    Up_counter_rotate();
                else if (side == "down")
                    Down_counter_rotate();
            }
            show();
            std::cin >> side >> direction;
        }

        show();
    }

    bool check_edge(int a, int b, int c, int num1, int num2, int num3) {
        if (a == num1 && b == num2 && c == num3)
            return true;
        else if (a == num1 && b == num3 && c == num2)
            return true;
        else if (a == num2 && b == num1 && c == num3)
            return true;
        else if (a == num2 && b == num3 && c == num1)
            return true;
        else if (a == num3 && b == num1 && c == num2)
            return true;
        else if (a == num3 && b == num2 && c == num1)
            return true;
        else
            return false;
    }

    bool check_rib(int a, int b, int num1, int  num2) {
        if (a == num1 && b == num2)
            return true;
        else if (a == num2 && b == num1)
            return true;
        else
            return false;
    }

    bool check() {
        std::vector<int> count(6, 0);

        count[front.a]++; count[front.b]++;
        count[front.c]++; count[front.d]++;
        count[front.e]++; count[front.f]++;
        count[front.g]++; count[front.h]++;
        count[front.k]++; count[back.a]++;
        count[back.b]++; count[back.c]++;
        count[back.d]++; count[back.e]++;
        count[back.f]++; count[back.g]++;
        count[back.h]++; count[back.k]++;
        count[left.a]++; count[left.b]++;
        count[left.c]++; count[left.d]++;
        count[left.e]++; count[left.f]++;
        count[left.g]++; count[left.h]++;
        count[left.k]++; count[right.a]++;
        count[right.b]++; count[right.c]++;
        count[right.d]++; count[right.e]++;
        count[right.f]++; count[right.g]++;
        count[right.h]++; count[right.k]++;
        count[up.a]++; count[up.b]++;
        count[up.c]++; count[up.d]++;
        count[up.e]++; count[up.f]++;
        count[up.g]++; count[up.h]++;
        count[up.k]++; count[down.a]++;
        count[down.b]++; count[down.c]++;
        count[down.d]++; count[down.e]++;
        count[down.f]++; count[down.g]++;
        count[down.h]++; count[down.k]++;

        for (int i : count)
            if (i != 9) return false;  //проверка цветов


        if (front.e != 0 || back.e != 1 || left.e != 2 || right.e != 3
            || up.e != 4 || down.e != 5) return false;  //проверка центров

        int edges = 0;

        if (check_edge(front.a, up.g, left.c, 4, 0, 2) ||
            check_edge(front.c, up.k, right.a, 4, 0, 2) ||
            check_edge(front.k, right.g, down.c, 4, 0, 2) ||
            check_edge(front.g, down.a, left.k, 4, 0, 2) ||
            check_edge(back.a, up.c, right.c, 4, 0, 2) ||
            check_edge(back.c, up.a, left.a, 4, 0, 2) ||
            check_edge(back.k, down.g, left.g, 4, 0, 2) ||
            check_edge(back.g, down.k, right.k, 4, 0, 2))
            edges++;

        if (check_edge(front.a, up.g, left.c, 4, 0, 3) ||
            check_edge(front.c, up.k, right.a, 4, 0, 3) ||
            check_edge(front.k, right.g, down.c, 4, 0, 3) ||
            check_edge(front.g, down.a, left.k, 4, 0, 3) ||
            check_edge(back.a, up.c, right.c, 4, 0, 3) ||
            check_edge(back.c, up.a, left.a, 4, 0, 3) ||
            check_edge(back.k, down.g, left.g, 4, 0, 3) ||
            check_edge(back.g, down.k, right.k, 4, 0, 3))
            edges++;

        if (check_edge(front.a, up.g, left.c, 5, 0, 3) ||
            check_edge(front.c, up.k, right.a, 5, 0, 3) ||
            check_edge(front.k, right.g, down.c, 5, 0, 3) ||
            check_edge(front.g, down.a, left.k, 5, 0, 3) ||
            check_edge(back.a, up.c, right.c, 5, 0, 3) ||
            check_edge(back.c, up.a, left.a, 5, 0, 3) ||
            check_edge(back.k, down.g, left.g, 5, 0, 3) ||
            check_edge(back.g, down.k, right.k, 5, 0, 3))
            edges++;

        if (check_edge(front.a, up.g, left.c, 2, 0, 5) ||
            check_edge(front.c, up.k, right.a, 2, 0, 5) ||
            check_edge(front.k, right.g, down.c, 2, 0, 5) ||
            check_edge(front.g, down.a, left.k, 2, 0, 5) ||
            check_edge(back.a, up.c, right.c, 2, 0, 5) ||
            check_edge(back.c, up.a, left.a, 2, 0, 5) ||
            check_edge(back.k, down.g, left.g, 2, 0, 5) ||
            check_edge(back.g, down.k, right.k, 2, 0, 5))
            edges++;

        if (check_edge(front.a, up.g, left.c, 2, 4, 1) ||
            check_edge(front.c, up.k, right.a, 2, 4, 1) ||
            check_edge(front.k, right.g, down.c, 2, 4, 1) ||
            check_edge(front.g, down.a, left.k, 2, 4, 1) ||
            check_edge(back.a, up.c, right.c, 2, 4, 1) ||
            check_edge(back.c, up.a, left.a, 2, 4, 1) ||
            check_edge(back.k, down.g, left.g, 2, 4, 1) ||
            check_edge(back.g, down.k, right.k, 2, 4, 1))
            edges++;

        if (check_edge(front.a, up.g, left.c, 3, 4, 1) ||
            check_edge(front.c, up.k, right.a, 3, 4, 1) ||
            check_edge(front.k, right.g, down.c, 3, 4, 1) ||
            check_edge(front.g, down.a, left.k, 3, 4, 1) ||
            check_edge(back.a, up.c, right.c, 3, 4, 1) ||
            check_edge(back.c, up.a, left.a, 3, 4, 1) ||
            check_edge(back.k, down.g, left.g, 3, 4, 1) ||
            check_edge(back.g, down.k, right.k, 3, 4, 1))
            edges++;

        if (check_edge(front.a, up.g, left.c, 5, 3, 1) ||
            check_edge(front.c, up.k, right.a, 5, 3, 1) ||
            check_edge(front.k, right.g, down.c, 5, 3, 1) ||
            check_edge(front.g, down.a, left.k, 5, 3, 1) ||
            check_edge(back.a, up.c, right.c, 5, 3, 1) ||
            check_edge(back.c, up.a, left.a, 5, 3, 1) ||
            check_edge(back.k, down.g, left.g, 5, 3, 1) ||
            check_edge(back.g, down.k, right.k, 5, 3, 1))
            edges++;

        if (check_edge(front.a, up.g, left.c, 5, 1, 2) ||
            check_edge(front.c, up.k, right.a, 5, 1, 2) ||
            check_edge(front.k, right.g, down.c, 5, 1, 2) ||
            check_edge(front.g, down.a, left.k, 5, 1, 2) ||
            check_edge(back.a, up.c, right.c, 5, 1, 2) ||
            check_edge(back.c, up.a, left.a, 5, 1, 2) ||
            check_edge(back.k, down.g, left.g, 5, 1, 2) ||
            check_edge(back.g, down.k, right.k, 5, 1, 2))
            edges++;

        if (edges != 8) return false;  //проверка углов

        int ribs = 0;

        if (check_rib(front.b, up.h, 2, 0) || check_rib(front.f, right.d, 2, 0) ||
            check_rib(front.h, down.b, 2, 0) || check_rib(front.d, left.f, 2, 0) ||
            check_rib(up.d, left.b, 2, 0) || check_rib(up.b, back.b, 2, 0) ||
            check_rib(up.f, right.b, 2, 0) || check_rib(right.f, back.d, 2, 0) ||
            check_rib(right.h, down.f, 2, 0) || check_rib(left.h, down.d, 2, 0) ||
            check_rib(left.d, back.f, 2, 0) || check_rib(back.h, down.h, 2, 0))
            ribs++;

        if (check_rib(front.b, up.h, 4, 0) || check_rib(front.f, right.d, 4, 0) ||
            check_rib(front.h, down.b, 4, 0) || check_rib(front.d, left.f, 4, 0) ||
            check_rib(up.d, left.b, 4, 0) || check_rib(up.b, back.b, 4, 0) ||
            check_rib(up.f, right.b, 4, 0) || check_rib(right.f, back.d, 4, 0) ||
            check_rib(right.h, down.f, 4, 0) || check_rib(left.h, down.d, 4, 0) ||
            check_rib(left.d, back.f, 4, 0) || check_rib(back.h, down.h, 4, 0))
            ribs++;

        if (check_rib(front.b, up.h, 5, 0) || check_rib(front.f, right.d, 5, 0) ||
            check_rib(front.h, down.b, 5, 0) || check_rib(front.d, left.f, 5, 0) ||
            check_rib(up.d, left.b, 5, 0) || check_rib(up.b, back.b, 5, 0) ||
            check_rib(up.f, right.b, 5, 0) || check_rib(right.f, back.d, 5, 0) ||
            check_rib(right.h, down.f, 5, 0) || check_rib(left.h, down.d, 5, 0) ||
            check_rib(left.d, back.f, 5, 0) || check_rib(back.h, down.h, 5, 0))
            ribs++;

        if (check_rib(front.b, up.h, 3, 0) || check_rib(front.f, right.d, 3, 0) ||
            check_rib(front.h, down.b, 3, 0) || check_rib(front.d, left.f, 3, 0) ||
            check_rib(up.d, left.b, 3, 0) || check_rib(up.b, back.b, 3, 0) ||
            check_rib(up.f, right.b, 3, 0) || check_rib(right.f, back.d, 3, 0) ||
            check_rib(right.h, down.f, 3, 0) || check_rib(left.h, down.d, 3, 0) ||
            check_rib(left.d, back.f, 3, 0) || check_rib(back.h, down.h, 3, 0))
            ribs++;

        if (check_rib(front.b, up.h, 2, 1) || check_rib(front.f, right.d, 2, 1) ||
            check_rib(front.h, down.b, 2, 1) || check_rib(front.d, left.f, 2, 1) ||
            check_rib(up.d, left.b, 2, 1) || check_rib(up.b, back.b, 2, 1) ||
            check_rib(up.f, right.b, 2, 1) || check_rib(right.f, back.d, 2, 1) ||
            check_rib(right.h, down.f, 2, 1) || check_rib(left.h, down.d, 2, 1) ||
            check_rib(left.d, back.f, 2, 1) || check_rib(back.h, down.h, 2, 1))
            ribs++;

        if (check_rib(front.b, up.h, 2, 5) || check_rib(front.f, right.d, 2, 5) ||
            check_rib(front.h, down.b, 2, 5) || check_rib(front.d, left.f, 2, 5) ||
            check_rib(up.d, left.b, 2, 5) || check_rib(up.b, back.b, 2, 5) ||
            check_rib(up.f, right.b, 2, 5) || check_rib(right.f, back.d, 2, 5) ||
            check_rib(right.h, down.f, 2, 5) || check_rib(left.h, down.d, 2, 5) ||
            check_rib(left.d, back.f, 2, 5) || check_rib(back.h, down.h, 2, 5))
            ribs++;

        if (check_rib(front.b, up.h, 4, 3) || check_rib(front.f, right.d, 4, 3) ||
            check_rib(front.h, down.b, 4, 3) || check_rib(front.d, left.f, 4, 3) ||
            check_rib(up.d, left.b, 4, 3) || check_rib(up.b, back.b, 4, 3) ||
            check_rib(up.f, right.b, 4, 3) || check_rib(right.f, back.d, 4, 3) ||
            check_rib(right.h, down.f, 4, 3) || check_rib(left.h, down.d, 4, 3) ||
            check_rib(left.d, back.f, 4, 3) || check_rib(back.h, down.h, 4, 3))
            ribs++;

        if (check_rib(front.b, up.h, 4, 2) || check_rib(front.f, right.d, 4, 2) ||
            check_rib(front.h, down.b, 4, 2) || check_rib(front.d, left.f, 4, 2) ||
            check_rib(up.d, left.b, 4, 2) || check_rib(up.b, back.b, 4, 2) ||
            check_rib(up.f, right.b, 4, 2) || check_rib(right.f, back.d, 4, 2) ||
            check_rib(right.h, down.f, 4, 2) || check_rib(left.h, down.d, 4, 2) ||
            check_rib(left.d, back.f, 4, 2) || check_rib(back.h, down.h, 4, 2))
            ribs++;

        if (check_rib(front.b, up.h, 4, 1) || check_rib(front.f, right.d, 4, 1) ||
            check_rib(front.h, down.b, 4, 1) || check_rib(front.d, left.f, 4, 1) ||
            check_rib(up.d, left.b, 4, 1) || check_rib(up.b, back.b, 4, 1) ||
            check_rib(up.f, right.b, 4, 1) || check_rib(right.f, back.d, 4, 1) ||
            check_rib(right.h, down.f, 4, 1) || check_rib(left.h, down.d, 4, 1) ||
            check_rib(left.d, back.f, 4, 1) || check_rib(back.h, down.h, 4, 1))
            ribs++;

        if (check_rib(front.b, up.h, 5, 1) || check_rib(front.f, right.d, 5, 1) ||
            check_rib(front.h, down.b, 5, 1) || check_rib(front.d, left.f, 5, 1) ||
            check_rib(up.d, left.b, 5, 1) || check_rib(up.b, back.b, 5, 1) ||
            check_rib(up.f, right.b, 5, 1) || check_rib(right.f, back.d, 5, 1) ||
            check_rib(right.h, down.f, 5, 1) || check_rib(left.h, down.d, 5, 1) ||
            check_rib(left.d, back.f, 5, 1) || check_rib(back.h, down.h, 5, 1))
            ribs++;

        if (check_rib(front.b, up.h, 5, 3) || check_rib(front.f, right.d, 5, 3) ||
            check_rib(front.h, down.b, 5, 3) || check_rib(front.d, left.f, 5, 3) ||
            check_rib(up.d, left.b, 5, 3) || check_rib(up.b, back.b, 5, 3) ||
            check_rib(up.f, right.b, 5, 3) || check_rib(right.f, back.d, 5, 3) ||
            check_rib(right.h, down.f, 5, 3) || check_rib(left.h, down.d, 5, 3) ||
            check_rib(left.d, back.f, 5, 3) || check_rib(back.h, down.h, 5, 3))
            ribs++;

        if (check_rib(front.b, up.h, 3, 1) || check_rib(front.f, right.d, 3, 1) ||
            check_rib(front.h, down.b, 3, 1) || check_rib(front.d, left.f, 3, 1) ||
            check_rib(up.d, left.b, 3, 1) || check_rib(up.b, back.b, 3, 1) ||
            check_rib(up.f, right.b, 3, 1) || check_rib(right.f, back.d, 3, 1) ||
            check_rib(right.h, down.f, 3, 1) || check_rib(left.h, down.d, 3, 1) ||
            check_rib(left.d, back.f, 3, 1) || check_rib(back.h, down.h, 3, 1))
            ribs++;

        if (ribs != 12) return false;

        return true;
    }

    void pattern() {
        if (assembly_check()) {
            Right_counter_rotate();
            Left_rotate();
            Up_rotate();
            Down_counter_rotate();
            Front_rotate();
            Back_counter_rotate();
            Right_counter_rotate();
            Left_rotate();
            show();
        }
        else std::cout << "Impossible to make a pattern :(" << std::endl;
    }

    void solve() {
        if (check()) {
            first_right_cross();
            show();
            std::cout << "Yellow cross is done" << std::endl;
            first_layer_edges();
            show();
            std::cout << "First layer is done" << std::endl;
            medium_layer_edges();
            show();
            std::cout << "Second layer is done" << std::endl;
            upper_right_cross();
            show();
            std::cout << "White cross is done" << std::endl;
            last_layer_edges();
            show();

            if (assembly_check()) std::cout << "Cube is solved!" << std::endl;
            else std::cout << "Impossible to solve :( " << std::endl;
        }
        else
            std::cout << "Impossible to solve :( " << std::endl;
    }


    // визуализаци€

    // номер грани дл€ поворотов
    int current;

    void clear(double size, unsigned int* color) {
        this->size = size;
        current = -1;

        int i, j, k;
        for (i = 0; i < 6; i++)
            this->color[i] = color[i];

        // верх
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                arr[i][j][2].set_color(0, color[0]);

        // низ
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                arr[i][j][0].set_color(1, color[1]);

        // спереди
        for (k = 0; k < 3; k++)
            for (j = 0; j < 3; j++)
                arr[j][0][k].set_color(2, color[2]);

        // сзади
        for (k = 0; k < 3; k++)
            for (j = 0; j < 3; j++)
                arr[j][2][k].set_color(3, color[3]);

        // слева
        for (i = 0; i < 3; i++)
            for (k = 0; k < 3; k++)
                arr[0][k][i].set_color(4, color[4]);

        // справа
        for (i = 0; i < 3; i++)
            for (k = 0; k < 3; k++)
                arr[2][k][i].set_color(5, color[5]);

        // размеры мелких деталей
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                for (k = 0; k < 3; k++)
                    arr[i][j][k].size = (size / 3) * 0.975;
    }

    void draw() {
        const float K = 0.5;
        // куб черного цвета, размер которого равен K*size
        glPushMatrix();
        glColor3f(0, 0, 0);

        float Kx = ((1 - K) / 2) * size + K * size / 2;
        float Ky = ((1 - K) / 2) * size + K * size / 2;
        float Kz = ((1 - K) / 2) * size + K * size / 2;
        glTranslatef(Kx, Ky, Kz);
        glutSolidCube(size * K);
        glPopMatrix();

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    if_ok[i][j][k] = true;

        int i, j, k;
        if (current != -1) {
            glPushMatrix();

            if (current == 0 || current == 1) {
                k = (current & 1) * 2;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        if_ok[i][j][k] = false;

                glTranslated(size / 2, size / 2, 0);   // сдвиги
                glRotatef(rotates[current], 0, 0, 1);
                glTranslated(-size / 2, -size / 2, 0);

                // рисуем
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        arr[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
            }
            else if (current == 2 || current == 3) {
                j = (current & 1) * 2;
                for (i = 0; i < 3; i++)
                    for (k = 0; k < 3; k++)
                        if_ok[i][j][k] = false;

                glTranslated(size / 2, 0, size / 2);
                glRotatef(rotates[current], 0, 1, 0);
                glTranslated(-size / 2, 0, -size / 2);

                for (i = 0; i < 3; i++)
                    for (k = 0; k < 3; k++)
                        arr[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
            }
            else if (current == 4 || current == 5) {
                i = (current & 1) * 2;
                for (j = 0; j < 3; j++)
                    for (k = 0; k < 3; k++)
                        if_ok[i][j][k] = false;

                glTranslated(0, size / 2, size / 2);
                glRotatef(rotates[current], 1, 0, 0);
                glTranslated(0, -size / 2, -size / 2);

                for (j = 0; j < 3; j++)
                    for (k = 0; k < 3; k++)
                        arr[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
            }

            glPopMatrix();
        }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    if (if_ok[i][j][k])
                        arr[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);

    }


    // проекции угла поворота на оси
    int x = 24;
    int y = 44;
    int z = 0;
    // отдаление
    double translateZ = -35.0;


    void display() {
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1, 0, 0);
        glTranslatef(0, 0, translateZ);
        glRotatef(x, 1, 0, 0);
        glRotatef(y, 0, 1, 0);
        glTranslatef(15 / -2.0, 15 / -2.0, 15 / -2.0);
        draw();
        glPopMatrix();
        glutSwapBuffers();
    }


    void rotate90(int id, int sign) {
        int i, j, k;
        // если sign = -1, значит крутим 3 раза
        if (sign == -1)
            sign = 3;

        while (sign--) {
            switch (id) {
            case 0:
                k = 0;
                // копируем повЄрнутую на 90 градусов верхнюю/нижнюю грань
                // в массив tmp, затем грани присваиваем tmp
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        tmp[j][2 - i] = arr[i][j][k];

                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        tmp[i][j].rotate_x();
                        arr[i][j][k] = tmp[i][j];
                    }
                }
                break;
            case 1:
                k = 2;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        tmp[j][2 - i] = arr[i][j][k];

                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        tmp[i][j].rotate_x();
                        arr[i][j][k] = tmp[i][j];
                    }
                }
                break;
            case 2:
                j = 0;
                for (i = 0; i < 3; i++)
                    for (k = 0; k < 3; k++)
                        tmp[k][2 - i] = arr[i][j][k];

                for (i = 0; i < 3; i++) {
                    for (k = 0; k < 3; k++) {
                        tmp[i][k].rotate_z();
                        arr[i][j][k] = tmp[i][k];
                    }
                }
                break;
            case 3:
                j = 2;
                for (i = 0; i < 3; i++)
                    for (k = 0; k < 3; k++)
                        tmp[k][2 - i] = arr[i][j][k];

                for (i = 0; i < 3; i++) {
                    for (k = 0; k < 3; k++) {
                        tmp[i][k].rotate_z();
                        arr[i][j][k] = tmp[i][k];
                    }
                }
                break;
            case 4:
                i = 0;
                for (j = 0; j < 3; j++)
                    for (k = 0; k < 3; k++)
                        tmp[k][2 - j] = arr[i][j][k];

                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        tmp[j][k].rotate_y();
                        arr[i][j][k] = tmp[j][k];
                    }
                }
                break;
            case 5:
                i = 2;
                for (j = 0; j < 3; j++)
                    for (k = 0; k < 3; k++)
                        tmp[k][2 - j] = arr[i][j][k];

                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 3; k++) {
                        tmp[j][k].rotate_y();
                        arr[i][j][k] = tmp[j][k];
                    }
                }
                break;
            }
        }
    }

    void timer(int RorL, int) {
        if (current != -1) {
            display();
            Rotate(current, 3, RorL);
        }
    }

    void Rotate(int id, int angle, int dir) {
        if (current == -1 || current == id) {
            if (dir == -1) rotates[id] -= angle;
            else if (dir == 1) rotates[id] += angle;

            if (rotates[id] % 90 != 0) {
                current = id;
                timer(dir, 0);
            }
            else {
                // угол стал кратным 90, поварачиваем на массиве
                if ((rotates[id] < 0) ^ (current == 2 || current == 3))
                    rotate90(id, 1);
                else
                    rotate90(id, -1);

                rotates[id] = 0;
                current = -1;
            }
        }
    }
};
