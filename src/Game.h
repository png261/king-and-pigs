#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
  public:
    static Game *Instance() {
        static Game *s_pInstance = new Game();
        return s_pInstance;
    }
    bool init(const char *title, int x, int y, int w, int h, Uint32 flags);
    void handleEvents();
    void update();
    void render();
    void clean();

    SDL_Renderer *getRenderer() { return m_pRenderer; }

    int getWidth() const { return m_width; }

    int getHeight() const { return m_width; }

    bool running() const { return m_bRunning; }
    void quit() { m_bRunning = false; }

  private:
    Game(){};
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    int m_width;
    int m_height;

    bool m_bRunning;
};

#endif
