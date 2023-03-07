#pragma once

#include <string>
#include <vector>

#include "GameObject.hpp"
#include "tinyxml2.h"

using namespace tinyxml2;

class StateParser final
{
public:
    bool parseState(
        const char* stateFile,
        const std::string stateID,
        std::vector<GameObject*>* const pObjects);

private:
    void parseObjects(XMLElement* const pStateRoot, std::vector<GameObject*>* const pObjects);
    void parseTextures(XMLElement* const pStateRoot);
};

