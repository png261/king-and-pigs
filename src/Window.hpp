#pragma once

#include <string>
#include "Color.hpp"
#include "SDL.hpp"
#include "Stopwatch.hpp"

class Window final
{
public:
    Window(const unsigned int width, const unsigned int height, const std::string title = "");
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

    void resize(const std::string title, const unsigned int width, const unsigned int height);

    void fill(const Color color);

    void clear();
    void setBackgroundColor(const Color color = Color(0, 0, 0));
    void setTitle(const std::string title);

    unsigned int getDelta() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    SDL_Renderer* getRenderer() const;

    void delayFramerateIfNeeded();

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    unsigned int m_width;
    unsigned int m_height;

    unsigned int m_originalWidth;
    unsigned int m_originalHeight;

    bool m_bFullscreen;

    std::string m_title;
    Color m_bgColor;
    Stopwatch m_framerateStopwatch;

    unsigned int m_framerate;
    unsigned int m_frameDelay;
    unsigned int m_currentFrameDelta;
};
