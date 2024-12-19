#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>

typedef struct coordinate {
    int x, y;
    char code[4];
} PT;

void drawwindow();
void drawline(PT p1, PT p2);
PT setcode(PT p);
int visibility(PT p1, PT p2);
PT resetendpt(PT p1, PT p2);

int main() {
    int gd = DETECT, v, gm;
    PT p1, p2, p3, p4, ptemp;

    cout << "\nEnter x1 and y1\n";
    cin >> p1.x >> p1.y;
    cout << "\nEnter x2 and y2\n";
    cin >> p2.x >> p2.y;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    drawwindow();
    delay(500);

    drawline(p1, p2);
    delay(500);
    cleardevice();

    delay(500);
    p1 = setcode(p1);
    p2 = setcode(p2);
    v = visibility(p1, p2);
    delay(500);

    switch (v) {
        case 0:
            drawwindow();
            delay(1000);
            drawline(p1, p2);
            break;
        case 1:
            drawwindow();
            delay(1000);
            break;
        case 2:
            p3 = resetendpt(p1, p2);
            p4 = resetendpt(p2, p1);
            drawwindow();
            delay(1000);
            drawline(p3, p4);
            break;
    }

    delay(5000);
    closegraph();
    return 0;
}

void drawwindow() {
    line(150, 100, 450, 100);
    line(450, 100, 450, 350);
    line(450, 350, 150, 350);
    line(150, 350, 150, 100);
}

void drawline(PT p1, PT p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

PT setcode(PT p) {
    PT ptemp;

    ptemp.code[0] = (p.y < 100) ? '1' : '0'; // Top
    ptemp.code[1] = (p.y > 350) ? '1' : '0'; // Bottom
    ptemp.code[2] = (p.x > 450) ? '1' : '0'; // Right
    ptemp.code[3] = (p.x < 150) ? '1' : '0'; // Left

    ptemp.x = p.x;
    ptemp.y = p.y;

    return ptemp;
}

int visibility(PT p1, PT p2) {
    int i, flag = 0;

    for (i = 0; i < 4; i++) {
        if ((p1.code[i] != '0') || (p2.code[i] != '0')) {
            flag = 2;
        }
    }

    for (i = 0; i < 4; i++) {
        if ((p1.code[i] == p2.code[i]) && (p1.code[i] == '1')) {
            flag = 1;
        }
    }

    if (flag == 0) return 0; // Both points are inside
    if (flag == 1) return 1; // Both points are outside
    return 2; // Line is partially inside
}

PT resetendpt(PT p1, PT p2) {
    PT temp;
    int x, y;
    float m, k;

    if (p1.code[3] == '1') x = 150; // Left
    if (p1.code[2] == '1') x = 450; // Right

    if ((p1.code[3] == '1') || (p1.code[2] == '1')) {
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
        k = (p1.y + (m * (x - p1.x)));
        temp.y = k;
        temp.x = x;

        if (temp.y <= 350 && temp.y >= 100) return temp;
    }

