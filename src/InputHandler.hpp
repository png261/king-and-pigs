#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <vector>
#include "Box2D.hpp"
#include "InputDefinitions.hpp"
#include "SDL.hpp"

class InputHandler
{
public:
    static InputHandler* Instance();

    void update();
    b2Vec2* getMousePosition() const;

    bool isKeyDown(KeyboardKey key) const;
    bool isMouseButtonDown(MouseButton buttonID) const;

    void reset();

private:
    InputHandler();

    void onKeyDown(SDL_Event& event);
    void onKeyUp(SDL_Event& event);

    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    b2Vec2* m_pMousePosition;
    std::vector<bool> m_bMouseButtonState;

    const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;

#endif
