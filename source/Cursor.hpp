#pragma once

class Cursor final
{
public:
    Cursor();
    void init();
    void reset();
    void draw() const;
    void hover();
    bool isHover() const;

private:
    int size_;
    bool is_hover_;
};
