#include "Window.hpp"

#include <iostream>
#include <stdexcept>

#include "CONSTANT.hpp"
#include "Log.hpp"

Window::Window(const int width, const int height, const std::string& title)
    : window_(nullptr)
    , renderer_(nullptr)
    , width_(width)
    , height_(height)
    , font_(nullptr)
    , framerate_(60)
    , frame_delay_(0)
    , title_(title)
    , background_color_(0, 0, 0)
{}

Window::~Window()
{
    destroy();
}

void Window::init()
{
    SDL_CreateWindowAndRenderer(
        width_,
        height_,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
        &window_,
        &renderer_);

    if (!window_ || !renderer_) {
        throw std::runtime_error("Window: Couldn't create Window");
    }

    SDL_RenderSetLogicalSize(getRenderer(), width_, height_);
    setTitle(title_);

    loadFont(FONT_DIRECTORY + "m6x11.ttf");

    frame_delay_ = 1000.f / framerate_;
    framerate_stopwatch_.start();

    clear();
    refresh();
}

void Window::loadFont(const std::string& font_path)
{
    font_ = TTF_OpenFont((font_path).c_str(), 28);
    if (font_ == nullptr) {
        throw std::runtime_error("Window: Fail load font");
    }
}

void Window::handleEvents(SDL_Event& event)
{
    if (event.type != SDL_WINDOWEVENT) {
        return;
    }

    switch (event.window.event) {
    case SDL_WINDOWEVENT_MINIMIZED:
        minimize();
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        maximize();
        break;
    }
}

void Window::resize(const std::string& title, const int width, const int height)
{
    SDL_RenderSetLogicalSize(renderer_, width, height);
    SDL_SetWindowSize(window_, width, height);

    width_ = width;
    height_ = height;
}

void Window::minimize() const
{
    SDL_MinimizeWindow(window_);
}

void Window::maximize() const
{
    SDL_MaximizeWindow(window_);
}

void Window::setIcon(const std::string& path) const
{
    SDL_Surface* const icon = IMG_Load(path.c_str());
    if (icon == nullptr) {
        return;
    }
    SDL_SetWindowIcon(window_, icon);
};

void Window::destroy()
{
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

void Window::fill(const Color& color) const
{
    SDL_SetRenderDrawColor(renderer_, color.r(), color.g(), color.b(), color.a());
    SDL_RenderClear(renderer_);
}

void Window::clear() const
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

void Window::delayFramerateIfNeeded()
{
    const int delta = framerate_stopwatch_.delta();

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

    SDL_Surface* const pSurface =
        TTF_RenderText_Blended(font_, text.c_str(), {color.r(), color.g(), color.b(), color.a()});
    if (pSurface == nullptr) {
        Log::error("Window::print: fail to create surface");
        return;
    }

    SDL_Texture* const texture = SDL_CreateTextureFromSurface(renderer_, pSurface);

    if (texture == nullptr) {
        SDL_FreeSurface(pSurface);
        Log::error("Window::print: fail to create texture");
        return;
    }

    SDL_Rect const dest_rect = {x - pSurface->w / 2, y - pSurface->h / 2, pSurface->w, pSurface->h};
    SDL_RenderCopy(renderer_, texture, nullptr, &dest_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(pSurface);
};

void Window::drawBox(const Rectangle& box, const int border_radius, const Color& color) const
{
    roundedBoxRGBA(
        renderer_,
        box.x(),
        box.y(),
        box.rightmost(),
        box.bottom(),
        border_radius,
        color.r(),
        color.g(),
        color.b(),
        color.a());
}

void Window::drawOverlay(const Color& color) const
{
    drawBox({0, 0, static_cast<int>(width_), static_cast<int>(height_)}, 0, color);
}

SDL_Renderer* Window::getRenderer() const
{
    return renderer_;
}

int Window::getWidth() const
{
    return width_;
}

int Window::getHeight() const
{
    return height_;
}

b2Vec2 Window::getCenter() const
{
    return {width_ * 0.5f, height_ * 0.5f};
}
