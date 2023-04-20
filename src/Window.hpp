#pragma once

#include <string>

#include "Color.hpp"
#include "SDL.hpp"
#include "Shapes.hpp"
#include "Stopwatch.hpp"

class Window final
{
public:
    Window(const uint width, const uint height, const std::string& title = "");
    ~Window();

    void clear();
    void destroy();

    void renderImage(
        SDL_Texture* const texture,
        const SDL_Rect* const srcrect,
        const SDL_Rect* const dstrect,
        const double angle = 0,
        const SDL_Point* center = 0,
        const SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* loadImage(const std::string& path);

    void freeImage(SDL_Texture* const image);

    void refresh();

    void resize(const std::string& title, const uint width, const uint height);

    void fill(const Color color);
    void print(
        std::string text,
        const int fontSize,
        const int x,
        const int y,
        const Color color = Color(Color::BLACK));
    void drawBox(const Rectangle rect, const Color color = Color(Color::WHITE)) const;

    void setBackgroundColor(const Color color = Color(Color::BLACK));
    void setTitle(const std::string& title);

    uint getDelta() const;
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

    uint origin_width_;
    uint origin_height_;

    bool is_fullscreen_;

    uint framerate_;
    uint frame_delay_;
    uint current_frame_delta_;

    std::string title_;
    Color background_color_;
    Stopwatch framerate_stopwatch_;
};
