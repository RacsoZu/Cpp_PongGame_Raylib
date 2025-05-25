#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string& text, int fontSize,
               Color defaultColor, Color hoverColor, Color textColor)
    : x(x), y(y), width(width), height(height), text(text), fontSize(fontSize), defaultColor(defaultColor), hoverColor(hoverColor), textColor(textColor) {}

bool Button::IsHovered() const {
    return CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height});
}

void Button::Draw() const {
    Color currentColor = IsHovered() ? hoverColor : defaultColor;
    DrawRectangle(x, y, width, height, currentColor);

    int textWidth = MeasureText(text.c_str(), fontSize);
    int textX = x + (width - textWidth) / 2;
    int textY = y + (height - fontSize) / 2;

    DrawText(text.c_str(), textX, textY, fontSize, textColor);
}

bool Button::IsClicked() const {
    return IsHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::setColor(Color color) {
    this->defaultColor = color;
}

void Button::SetTextColor(Color color) {
    this->textColor = color;
}



