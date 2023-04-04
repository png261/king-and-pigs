#pragma once

#include <string>
#include "Color.hpp"
#include "SDL.hpp"
#include "Shapes.hpp"
#include "Stopwatch.hpp"

class Window final
{
public:
    Window(const uint width, const uint height, const std::string title = "");
    virtual ~Window();

    void clear();
    void destroy();

    void renderImage(
        SDL_Texture* const texture,
        const SDL_Rect* const srcrect,
        const SDL_Rect* const dstrect,
        const double angle = 0,
        const SDL_Point* center = 0,
        const SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* loadImage(const std::string path);

    void freeImage(SDL_Texture* const image);

    void refresh();

    void resize(const std::string title, const uint width, const uint height);

    void fill(const Color color);
    void print(std::string text, int fontSize, int x, int y, Color color = {0, 0, 0});
    void drawBox(Rectangle rect, Color color = {255, 255, 255}) const;

    void setBackgroundColor(const Color color = Color(0, 0, 0));
    void setTitle(const std::string title);

    uint getDelta() const;
    uint getWidth() const;
    uint getCenterX() const;
    uint getCenterY() const;
    uint getHeight() const;
    SDL_Renderer* getRenderer() const;

    void delayFramerateIfNeeded();

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    TTF_Font* m_font;

    uint m_width;
    uint m_height;

    uint m_originalWidth;
    uint m_originalHeight;

    uint m_framerate;
    uint m_frameDelay;
    uint m_currentFrameDelta;

    bool m_bFullscreen;

    std::string m_title;
    Color m_bgColor;
    Stopwatch m_framerateStopwatch;
};
