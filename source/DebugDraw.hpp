#pragma once

#include <box2d/box2d.h>
#include "Window.hpp"

class DebugDraw final : public b2Draw
{
public:
    DebugDraw(Window* const window);

    void DrawPolygon(const b2Vec2* vertices, const int32 vertexCount, const b2Color& color)
        override;

    void DrawSolidPolygon(const b2Vec2* vertices, const int32 vertexCount, const b2Color& color)
        override;

    void DrawCircle(const b2Vec2& center, const float radius, const b2Color& color) override;

    void DrawSolidCircle(
        const b2Vec2& center,
        const float radius,
        const b2Vec2& axis,
        const b2Color& color) override;

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

    void DrawTransform(const b2Transform& xf) override;

    void DrawPoint(const b2Vec2& p, const float size, const b2Color& color) override;

private:
    Window* window_;
    SDL_Renderer* renderer_;
};
