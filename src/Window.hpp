#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "Color.hpp"
#include "SDL.hpp"
#include "Timer.hpp"

class Window
{
public:
    Window(unsigned int width, unsigned int height, std::string title = "");
    virtual ~Window();

    void destroy();

    void renderImage(
        SDL_Texture* texture,
        const SDL_Rect* srcrect,
        const SDL_Rect* dstrect,
        const double angle = 0,
        const SDL_Point* center = 0,
        const SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* loadImage(std::string filename);

    void freeImage(SDL_Texture* image);

    void refresh();

    void resize(std::string title, unsigned int width, unsigned int height);

    void fill(Color color);

    void clear();
    void setBackgroundColor(Color color = Color(0, 0, 0));
    void setTitle(std::string title);

    void delayFramerateIfNeeded();
    unsigned int getDelta() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    SDL_Renderer* getRenderer();

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
    Timer m_framerateTimer;

    unsigned int m_framerate;
    unsigned int m_frameDelay;
    unsigned int m_currentFrameDelta;
};

#endif
