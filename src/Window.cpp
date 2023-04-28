#include "Window.hpp"

#include <stdexcept>

#include "CONSTANT.hpp"
#include "Log.hpp"

Window::Window(const uint width, const uint height, const std::string& title)
    : window_(nullptr)
    , renderer_(nullptr)
    , font_(nullptr)
    , width_(width)
    , height_(height)
    , framerate_(60)
    , frame_delay_(0)
    , title_(title)
    , background_color_(0, 0, 0)
{
    resize(title, width, height);

    if (!window_ || !renderer_) {
        throw std::runtime_error("Window: Couldn't create Window");
    }

    font_ = TTF_OpenFont((FONT_DIRECTORY + "m6x11.ttf").c_str(), 28);
    if (font_ == nullptr) {
        throw std::runtime_error("Window: Fail load font");
    }

    framerate_stopwatch_.start();

    clear();
    refresh();
}

Window::~Window()
{
    destroy();
}

void Window::resize(const std::string& title, const uint width, const uint height)
{
    // Just in case we already have a window
    destroy();

    // Taken from the Migration Guide
    // (http://wiki.libsdl.org/MigrationGuide)
    //
    // It creates a nice window independent of the user's monitor size.
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window_, &renderer_);

    if (window_ == nullptr || renderer_ == nullptr) {
        Log::error("Window::resize: Couldn't create SDL_Window or SDL_Renderer");
        return;
    }

    // And here we fake a "logical" size of the window, independent of it's real size.
    /* SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); */
    SDL_RenderSetLogicalSize(renderer_, width, height);

    setTitle(title);

    width_ = width;
    height_ = height;

    frame_delay_ = 1000.f / framerate_;
}

void Window::destroy()
{
    Log::log("window destroy");
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

void Window::refresh() const
{
    SDL_RenderPresent(renderer_);
}

SDL_Texture* Window::loadImage(const std::string& path) const
{
    SDL_Texture* const texture = IMG_LoadTexture(renderer_, path.c_str());
    if (texture == nullptr) {
        Log::error("IMG_LoadTexture: Couldn't open image '" + path + "': " + IMG_GetError());
    }
    return texture;
}

void Window::freeImage(SDL_Texture* const texture) const
{
    if (texture == nullptr) {
        return;
    }

    SDL_DestroyTexture(texture);
}

void Window::renderImage(
    SDL_Texture* const texture,
    const SDL_Rect* const src_rect,
    const SDL_Rect* const dest_rect,
    const double angle,
    const SDL_Point* center,
    const SDL_RendererFlip flip) const
{
    if (!texture || !src_rect || !dest_rect) {
        Log::warning("Window::render: Tried to show a nullptr image");
        return;
    }

    SDL_RenderCopyEx(renderer_, texture, src_rect, dest_rect, angle, center, flip);
}

void Window::fill(const Color& color)
{
    SDL_SetRenderDrawColor(renderer_, color.r(), color.g(), color.b(), color.a());
    SDL_RenderClear(renderer_);
}

void Window::clear()
{
    fill(background_color_);
}

void Window::setTitle(const std::string& title)
{
    if (window_ == nullptr) {
        return;
    }

    SDL_SetWindowTitle(window_, title.c_str());
}

void Window::setBackgroundColor(const Color& color)
{
    background_color_ = color;
}

void Window::resetBackgroundColor()
{
    background_color_ = Color(Color::BLACK);
}

void Window::delayFramerateIfNeeded()
{
    uint delta = framerate_stopwatch_.delta();

    if (delta < frame_delay_) {
        SDL_Delay(frame_delay_ - delta);
    };

    framerate_stopwatch_.restart();
}

void Window::print(
    const std::string& text,
    const int x,
    const int y,
    const int size,
    const Color& color,
    const int style) const
{
    if (font_ == nullptr) {
        Log::error("Window::print: fail to load font");
        return;
    }
    TTF_SetFontSize(font_, size);
    TTF_SetFontStyle(font_, style);

    SDL_Surface* pSurface =
        TTF_RenderText_Blended(font_, text.c_str(), {color.r(), color.g(), color.b(), color.a()});
    if (pSurface == nullptr) {
        Log::error("Window::print: fail to create surface");
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, pSurface);

    if (texture == nullptr) {
        SDL_FreeSurface(pSurface);
        Log::error("Window::print: fail to create texture");
        return;
    }

    SDL_Rect dest_rect = {x - pSurface->w / 2, y - pSurface->h / 2, pSurface->w, pSurface->h};
    SDL_RenderCopy(renderer_, texture, nullptr, &dest_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pSurface);
};

void Window::drawBox(const Rectangle& box, const Color& color) const
{
    roundedBoxRGBA(
        renderer_,
        box.x(),
        box.y(),
        box.rightmost(),
        box.bottom(),
        box.border_radius(),
        color.r(),
        color.g(),
        color.b(),
        color.a());
}

void Window::drawOverlay(const Color& color) const
{
    drawBox({0, 0, static_cast<int>(width_), static_cast<int>(height_)}, color);
}

SDL_Renderer* Window::getRenderer() const
{
    return renderer_;
}

uint Window::getWidth() const
{
    return width_;
}

uint Window::getHeight() const
{
    return height_;
}

uint Window::getCenterX() const
{
    return width_ / 2;
}

uint Window::getCenterY() const
{
    return height_ / 2;
}
