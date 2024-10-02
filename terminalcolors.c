#include <stdio.h>
#include "terminalcolors.h"

// Helper function to apply an RGB color to the terminal for text or background.
void applyRGBColor(int isForeground, RGB color)
{
    if (isForeground)
    {
        printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);  // Foreground
    }
    else
    {
        printf("\033[48;2;%d;%d;%dm", color.r, color.g, color.b);  // Background
    }
}

// Sets the foreground (text) color based on the RGB value.
void textColor(RGB color)
{
    applyRGBColor(1, color);
}

// Sets the background color based on the RGB value.
void backgroundColor(RGB color)
{
    applyRGBColor(0, color);
}

// Resets the terminal colors to default.
void resetColor()
{
    printf("\033[0m"); // Reset to default
}
