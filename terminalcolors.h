#ifndef TERMINALCOLORS_H
#define TERMINALCOLORS_H

typedef struct RGB
{
    int r;
    int g;
    int b;
} RGB;

// Sets the foreground (text) color based on the RGB value.
void textColor(RGB color);

// Sets the background color based on the RGB value.
void backgroundColor(RGB color);

// Resets the terminal colors to default.
void resetColor();

#endif // TERMINALCOLORS_H
