#include "Window.hpp"
#include "Log.hpp"

Window::Window(const uint width, const uint height, const std::string title)
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
    m_pFont = TTF_OpenFont("fonts/m6x11.ttf", 28);
    if (m_pFont == nullptr) {
        Log::error("Window(): Couldn't load font");
    }

    this->m_framerateStopwatch.start();

    this->clear();
    this->refresh();
}

Window::~Window()
{
    this->destroy();
}

void Window::resize(std::string title, uint width, uint height)
{
    // Just in case we already have a window
    this->destroy();

    // Taken from the Migration Guide
    // (http://wiki.libsdl.org/MigrationGuide)
    //
    // It creates a nice window independent of the user's monitor size.
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &m_pWindow, &m_pRenderer);

    if (m_pWindow == nullptr || m_pRenderer == nullptr) {
        Log::error("Window::resize: Couldn't create SDL_Window or SDL_Renderer");
        return;
    }

    // And here we fake a "logical" size of the window, independent of it's real size.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_pRenderer, width, height);

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

SDL_Texture* Window::loadImage(const std::string path)
{
    SDL_Texture* const pTexture = IMG_LoadTexture(m_pRenderer, path.c_str());
    if (pTexture == nullptr) {
        Log::error("IMG_LoadTexture: Couldn't open image '" + path + "': " + IMG_GetError());
    }
    return pTexture;
}

void Window::freeImage(SDL_Texture* const pTexture)
{
    if (pTexture == nullptr) {
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
    if (m_pWindow == nullptr) {
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
    m_currentFrameDelta = m_framerateStopwatch.delta();

    if ((m_currentFrameDelta) < (m_frameDelay)) {
        SDL_Delay((m_frameDelay)-m_currentFrameDelta);
    };

    m_framerateStopwatch.restart();
}

void Window::print(std::string text, int fontSize, int x, int y, Color color)
{
    if (m_pFont == nullptr) {
        Log::error("Window::print: fail to load font");
        return;
    }
    TTF_SetFontSize(m_pFont, fontSize);

    SDL_Surface* pSurface =
        TTF_RenderText_Blended(m_pFont, text.c_str(), {color.r(), color.g(), color.b(), color.a()});
    if (pSurface == nullptr) {
        Log::error("Window::print: fail to create surface");
        return;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    if (pTexture == nullptr) {
        Log::error("Window::print: fail to create texture");
        return;
    }

    SDL_Rect dest_rect{x - pSurface->w / 2, y - pSurface->h / 2, pSurface->w, pSurface->h};

    SDL_RenderCopy(m_pRenderer, pTexture, NULL, &dest_rect);

    SDL_DestroyTexture(pTexture);
};

void Window::drawBox(Rectangle box, Color color) const
{
    SDL_Rect rect{
        static_cast<int>(box.x),
        static_cast<int>(box.y),
        box.w,
        box.h,
    };

    SDL_SetRenderDrawColor(m_pRenderer, color.r(), color.g(), color.b(), color.a());
    SDL_RenderFillRect(m_pRenderer, &rect);
}

uint Window::getDelta() const
{
    return m_currentFrameDelta;
}

SDL_Renderer* Window::getRenderer() const
{
    return m_pRenderer;
}

uint Window::getWidth() const
{
    return m_width;
}

uint Window::getHeight() const
{
    return m_height;
}

uint Window::getCenterX() const
{
    return m_width / 2;
}

uint Window::getCenterY() const
{
    return m_height / 2;
}
