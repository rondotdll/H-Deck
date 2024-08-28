#pragma once

namespace SGui {
    class UIComponent {
    public:
        int x, y; // position
        int w, h; // size
        bool focused = false;

        UIComponent() = default; // Default constructor
        UIComponent(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

        virtual void draw();
        virtual bool contains(int touchX, int touchY) { return false; };
    };
}