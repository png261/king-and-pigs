#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Color.hpp"
#include "SDL.hpp"
#include "Shapes.hpp"
#include "Stopwatch.hpp"

enum FontStyle {
    NORMAL = TTF_STYLE_NORMAL,
    BOLD = TTF_STYLE_BOLD,
    ITALIC = TTF_STYLE_ITALIC,
    UNDERLINE = TTF_STYLE_UNDERLINE,
    STRIKETHROUGH = TTF_STYLE_STRIKETHROUGH
};


class Window final
{
public:
    Window(const uint width, const uint height, const std::string& title = "");
    ~Window();

    void clear();
    void destroy();

    void renderImage(
        SDL_Texture* const texture,
        const SDL_Rect* const src_dest,
        const SDL_Rect* const dest_rect,
        const double angle = 0,
        const SDL_Point* center = 0,
        const SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    SDL_Texture* loadImage(const std::string& path) const;

    void freeImage(SDL_Texture* const image) const;

    void refresh() const;

    void resize(const std::string& title, const uint width, const uint height);

    void fill(const Color& color);
    void print(
        const std::string& text,
        const int x,
        const int y,
        const int size,
        const Color& color = Color(Color::BLACK),
        const int style = FontStyle::NORMAL) const;
    void drawBox(const Rectangle& rect, const Color& color = Color(Color::WHITE)) const;
    void drawOverlay(const Color& color = Color(Color::WHITE)) const;

    void setBackgroundColor(const Color& color = Color(Color::BLACK));
    void resetBackgroundColor();
    void setTitle(const std::string& title);

    uint getWidth() const;
    uint getCenterX() const;
    uint getCenterY() const;
    uint getHeight() const;
    SDL_Renderer* getRenderer() const;

    void delayFramerateIfNeeded();

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;

    uint width_;
    uint height_;

    uint framerate_;
    uint frame_delay_;

    std::string title_;
    Color background_color_;
    Stopwatch framerate_stopwatch_;
};
