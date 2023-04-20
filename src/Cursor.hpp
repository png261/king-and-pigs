#pragma once

class Cursor final
{
public:
    Cursor();
    void init();
    void resetState();
    void draw();
    void hover();
    bool isHover() const;

private:
    int m_size;
    bool m_bHover;
};
