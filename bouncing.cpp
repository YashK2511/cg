#include <iostream.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\turbo c3\\bgi");

    float x = 1, y, j = 0.5, count = 0.1, i;
    setcolor(1); // Set color to a predefined color (1 is usually blue)

    for (int k = 0; k < 7; k++) {
        for (i = 90; i < 270; i += 10) {
            y = cos(i * 3.14 / 180) / j; // Calculate y based on cosine
            x += 5; // Increment x
            circle(x, y * 100 + 200, 15); // Draw circle
            floodfill(x, y * 100 + 200, 1); // Fill the circle
            line(0, 215, 800, 215); // Draw a horizontal line
            delay(50); // Delay for animation effect
            clrscr(); // Clear the screen
        }
        j += count; // Increment j
        count += 0.1; // Increment count
    }

    getch(); // Wait for a key press
    return 0;
}
