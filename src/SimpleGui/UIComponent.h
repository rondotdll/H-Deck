#pragma once


namespace SGui {
    class UIComponent {
    public:
        bool focused = false;
        virtual void draw();
        virtual bool contains(int touchX, int touchY) { return false; };
    };
}