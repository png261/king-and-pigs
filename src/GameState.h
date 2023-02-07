#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

class GameState {
  public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual void exit() = 0;
    virtual void resume() = 0;
    virtual void enter() = 0;

    virtual std::string getStateID() const = 0;

  protected:
    GameState() : m_loadingComplete(false), m_exiting(false) {}
    std::vector<std::string> m_textureIDList;
    bool m_loadingComplete;
    bool m_exiting;
};

#endif
