#pragma once

#include <box2d/box2d.h>
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
    Window(const int width, const int height, const std::string& title = "");
    ~Window();

    void init();
    void clear() const;
    void handleEvents(SDL_Event& event);
    void destroy();

    void loadFont(const std::string& font_path);

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

    void resize(const std::string& title, const int width, const int height);

    void minimize() const;

    void maximize() const;

    void setIcon(const std::string& filepath) const;

    void fill(const Color& color) const;

    void print(
        const std::string& text,
        const int x,
        const int y,
        const int size,
        const Color& color = Color(ColorName::BLACK),
        const int style = FontStyle::NORMAL) const;

    void drawBox(
        const Rectangle& rect,
        const int border_radius,
        const Color& color = Color(ColorName::WHITE)) const;

    void drawOverlay(const Color& color = Color(ColorName::WHITE)) const;

    void setBackgroundColor(const Color& color = Color(ColorName::BLACK));
    void setTitle(const std::string& title);

    int getWidth() const;
    b2Vec2 getCenter() const;
    int getHeight() const;
    SDL_Renderer* getRenderer() const;

    void delayFramerateIfNeeded();

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    TTF_Font* font_;

    int width_;
    int height_;

    int framerate_;
    int frame_delay_;

    std::string title_;
    Color background_color_;
    Stopwatch framerate_stopwatch_;
};
