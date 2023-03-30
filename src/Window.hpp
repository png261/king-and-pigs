#pragma once

#include <string>
#include "Color.hpp"
#include "SDL.hpp"
#include "Stopwatch.hpp"

class Window final
{
public:
    Window(const uint width, const uint height, const std::string title = "");
    virtual ~Window();

    void destroy();

    void renderImage(
        SDL_Texture* const texture,
        const SDL_Rect* const srcrect,
        const SDL_Rect* const dstrect,
        const double angle = 0,
        const SDL_Point* center = 0,
        const SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* loadImage(const std::string filename);

    void freeImage(SDL_Texture* const image);

    void refresh();

    void resize(const std::string title, const uint width, const uint height);

    void fill(const Color color);

    void clear();
    void setBackgroundColor(const Color color = Color(0, 0, 0));
    void setTitle(const std::string title);

    uint getDelta() const;
    uint getWidth() const;
    uint getHeight() const;
    SDL_Renderer* getRenderer() const;

    void delayFramerateIfNeeded();

    void print(std::string text, int fontSize, int x, int y, Color color);

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
