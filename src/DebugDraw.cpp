#include "DebugDraw.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include "Camera.hpp"
#include "Game.hpp"
#include "SDL.hpp"

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::cout << "draw polygon" << std::endl;
    std::cout << vertices->x << std::endl;
    std::cout << vertices->y << std::endl;
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    SDL_Renderer* renderer = Game::Instance()->getWindow()->getRenderer();
    // Set the renderer color to the fill color.
    SDL_SetRenderDrawColor(renderer, color.r * 255, color.g * 255, color.b * 255, color.a * 255);

    // Create an array of SDL points from the Box2D vertices.
    SDL_Point sdlVertices[vertexCount];
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2 point = vertices[i] - TheCamera::Instance()->getPosition();
        sdlVertices[i] = {static_cast<int>(point.x), static_cast<int>(point.y)};
    }

    // Draw the polygon by calling SDL_RenderDrawLines.
    // The last point should connect to the first point to close the polygon.
    SDL_RenderDrawLines(renderer, sdlVertices, vertexCount);
    SDL_RenderDrawLine(
        renderer,
        sdlVertices[vertexCount - 1].x,
        sdlVertices[vertexCount - 1].y,
        sdlVertices[0].x,
        sdlVertices[0].y);

    // Draw the outline by calling SDL_RenderDrawLines again.
    SDL_RenderDrawLines(renderer, sdlVertices, vertexCount);
}

/// Draw a circle.
void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    std::cout << "draw circle" << std::endl;
}


/// Draw a solid circle.
void DebugDraw::DrawSolidCircle(
    const b2Vec2& center,
    float radius,
    const b2Vec2& axis,
    const b2Color& color)
{
    std::cout << "draw solid circle" << std::endl;
}

/// Draw a line segment.
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    std::cout << "draw segment" << std::endl;
}

/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void DebugDraw::DrawTransform(const b2Transform& xf)
{
    std::cout << "draw transform" << std::endl;
};

/// Draw a point.
void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    std::cout << "draw point " << std::endl;
}
