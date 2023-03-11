#include "Window.hpp"
#include <SDL2/SDL_render.h>
#include "Log.hpp"

Window::Window(const unsigned int width, const unsigned int height, const std::string title)
    : m_pWindow(nullptr)
    , m_pRenderer(nullptr)
    , m_width(width)
    , m_height(height)
    , m_originalWidth(width)
    , m_originalHeight(height)
    , m_bFullscreen(false)
    , m_title(title)
    , m_bgColor(0, 0, 0)
    , m_framerate(60)
    , m_frameDelay(0)
    , m_currentFrameDelta(0)
{
    // Calling for the first time CREATES a window.
    // Storing it on m_pWindow
    this->resize(title, width, height);


    if (!m_pWindow || !m_pRenderer) {
        Log::error("Window(): Couldn't create Window");
        throw "Window() Fail";
    }

    this->m_framerateTimer.start();

    this->clear();
    this->refresh();
}

Window::~Window()
{
    this->destroy();
}

void Window::resize(std::string title, unsigned int width, unsigned int height)
{
    // Just in case we already have a window
    this->destroy();

    // Taken from the Migration Guide
    // (http://wiki.libsdl.org/MigrationGuide)
    //
    // It creates a nice window independent of the user's
    // monitor size.
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &m_pWindow, &m_pRenderer);

    if (!m_pWindow || !m_pRenderer) {
        Log::error("Window::resize: Couldn't create SDL_Window or SDL_Renderer");
        return;
    }

    // And here we fake a "logical" size of the window,
    // independent of it's real size.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_pRenderer, width, height);

    // Lil' title
    this->setTitle(title);

    m_width = width;
    m_height = height;

    m_frameDelay = 1000.f / m_framerate;
}

void Window::destroy()
{
    if (m_pRenderer) {
        SDL_DestroyRenderer(m_pRenderer);
        m_pRenderer = nullptr;
    }

    if (m_pWindow) {
        SDL_DestroyWindow(m_pWindow);
        m_pWindow = nullptr;
    }
}

void Window::refresh()
{
    SDL_RenderPresent(m_pRenderer);
}

SDL_Texture* Window::loadImage(const std::string filename)
{
    SDL_Texture* const pTexture = IMG_LoadTexture(m_pRenderer, filename.c_str());
    if (!pTexture) {
        Log::error("IMG_LoadTexture: Couldn't open image '" + filename + "': " + IMG_GetError());
    }
    return pTexture;
}

void Window::freeImage(SDL_Texture* const pTexture)
{
    if (!pTexture) {
        return;
    }

    SDL_DestroyTexture(pTexture);
}

void Window::renderImage(
    SDL_Texture* const texture,
    const SDL_Rect* const srcrect,
    const SDL_Rect* const dstrect,
    const double angle,
    const SDL_Point* center,
    const SDL_RendererFlip flip)
{
    if (!texture || !srcrect || !dstrect) {
        Log::warning("Window::render: Tried to show a nullptr image");
        return;
    }

    SDL_RenderCopyEx(m_pRenderer, texture, srcrect, dstrect, angle, center, flip);
}

void Window::fill(const Color color)
{
    SDL_SetRenderDrawColor(m_pRenderer, color.r(), color.g(), color.b(), color.a());
    SDL_RenderClear(m_pRenderer);
}

void Window::clear()
{
    this->fill(m_bgColor);
}

void Window::setTitle(const std::string title)
{
    if (!m_pWindow) {
        return;
    }

    SDL_SetWindowTitle(m_pWindow, title.c_str());
}

void Window::setBackgroundColor(const Color color)
{
    m_bgColor = color;
}

void Window::delayFramerateIfNeeded()
{
    m_currentFrameDelta = m_framerateTimer.delta();

    if ((m_currentFrameDelta) < (m_frameDelay)) {
        SDL_Delay((m_frameDelay)-m_currentFrameDelta);
    };

    m_framerateTimer.restart();
}

unsigned int Window::getDelta() const
{
    return m_currentFrameDelta;
}

SDL_Renderer* Window::getRenderer() const
{
    return m_pRenderer;
}

unsigned int Window::getWidth() const
{
    return m_width;
}

unsigned int Window::getHeight() const
{
    return m_height;
}
