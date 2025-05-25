#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class Button {
private:
    float x, y, width, height;
    Color defaultColor;
    Color hoverColor;
    std::string text;
    int fontSize;
    Color textColor;

public:
    Button(float x, float y, float width, float height, const std::string& text, int fontSize,
           Color defaultColor = DARKGRAY, Color hoverColor = BLACK, Color textColor = WHITE);

    void Draw() const;
    bool IsHovered() const;
    bool IsClicked() const;
    void SetTextColor(Color color);
    void setColor(Color color);
};

#endif //BUTTON_H
