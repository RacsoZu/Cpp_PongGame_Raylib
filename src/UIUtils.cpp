#include "UIUtils.h"

void DrawCenteredText(const char* text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int screenWidth = GetScreenWidth();
    int x = (screenWidth - textWidth) / 2;
    DrawText(text, x, y, fontSize, color);
}


