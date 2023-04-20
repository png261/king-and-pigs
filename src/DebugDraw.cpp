#include "DebugDraw.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "SDL.hpp"
#include "Utils.hpp"

DebugDraw::DebugDraw(Window* const window)
{
    m_pRenderer = window->getRenderer();
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    /* flags += b2Draw::e_jointBit; */
    /* flags += b2Draw::e_centerOfMassBit; */
    /* flags += b2Draw::e_aabbBit; */
    /* flags += b2Draw::e_pairBit; */
    b2Draw::SetFlags(flags);
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    int zoom = Camera::Instance().getZoom();

    SDL_SetRenderDrawColor(m_pRenderer, color.r * 255, color.g * 255, color.b * 255, color.a * 255);

    std::vector<SDL_Point> sdlVertices;
    for (int i = 0; i < vertexCount; ++i) {
        sdlVertices.push_back(Utils::b2Vec2ToSDLPoint(
            PhysicWorld::meterToPixel(zoom * vertices[i]) -
            zoom * Camera::Instance().getPosition()));
    }

    SDL_RenderDrawLines(m_pRenderer, sdlVertices.data(), sdlVertices.size());
    SDL_RenderDrawLine(
        m_pRenderer,
        sdlVertices.back().x,
        sdlVertices.back().y,
        sdlVertices.front().x,
        sdlVertices.front().y);
}


void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    DebugDraw::DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    int zoom = Camera::Instance().getZoom();

    SDL_SetRenderDrawColor(m_pRenderer, color.r * 255, color.g * 255, color.b * 255, color.a * 255);

    const int k_segments = 16;
    const int vertexCount = k_segments + 1;

    std::vector<b2Vec2> vertices;

    float theta = 0.0f;
    float deltaTheta = 2.0f * b2_pi / float(k_segments);

    for (int32 i = 0; i < k_segments; ++i) {
        vertices.push_back(center + radius * b2Vec2(cosf(theta), sinf(theta)));
        theta += deltaTheta;
    }
    vertices.push_back(vertices.back());

    std::vector<SDL_Point> sdlVertices;
    for (int32 i = 0; i < vertexCount; ++i) {
        sdlVertices.push_back(Utils::b2Vec2ToSDLPoint(
            PhysicWorld::meterToPixel(zoom * vertices[i]) -
            zoom * Camera::Instance().getPosition()));
    }

    SDL_RenderDrawLines(m_pRenderer, sdlVertices.data(), sdlVertices.size());
}

void DebugDraw::DrawSolidCircle(
    const b2Vec2& center,
    float radius,
    const b2Vec2&,
    const b2Color& color)
{
    DebugDraw::DrawCircle(center, radius, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    int zoom = Camera::Instance().getZoom();

    SDL_SetRenderDrawColor(m_pRenderer, color.r * 255, color.g * 255, color.b * 255, color.a * 255);
    std::vector<SDL_Point> sdlVertices;

    sdlVertices.push_back(Utils::b2Vec2ToSDLPoint(
        PhysicWorld::meterToPixel(zoom * p1) - zoom * Camera::Instance().getPosition()));
    sdlVertices.push_back(Utils::b2Vec2ToSDLPoint(
        PhysicWorld::meterToPixel(zoom * p2) - zoom * Camera::Instance().getPosition()));

    SDL_RenderDrawLines(m_pRenderer, sdlVertices.data(), sdlVertices.size());
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    int zoom = Camera::Instance().getZoom();

    SDL_Point p1 = Utils::b2Vec2ToSDLPoint(
        PhysicWorld::meterToPixel(zoom * xf.p) - zoom * Camera::Instance().getPosition());
    SDL_Point p2 = Utils::b2Vec2ToSDLPoint(
        PhysicWorld::meterToPixel(zoom * b2Vec2(xf.p.x + xf.q.c * 20.0f, xf.p.y + xf.q.s * 20.0f)) -
        zoom * Camera::Instance().getPosition());
    SDL_RenderDrawLine(m_pRenderer, p1.x, p1.y, p2.x, p2.y);
};

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    int zoom = Camera::Instance().getZoom();

    SDL_SetRenderDrawColor(m_pRenderer, color.r * 255, color.g * 255, color.b * 255, color.a * 255);
    b2Vec2 point = zoom * PhysicWorld::meterToPixel(p) - zoom * Camera::Instance().getPosition();
    size = zoom * PhysicWorld::meterToPixel(size);
    SDL_Rect rect{
        static_cast<int>(point.x - size / 2.0f),
        static_cast<int>(point.y - size / 2.0f),
        static_cast<int>(size),
        static_cast<int>(size)};
    SDL_RenderFillRect(m_pRenderer, &rect);
}
