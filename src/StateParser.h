#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*>* pObjects);

private:
    void parseObjects(XMLElement* pStateRoot, std::vector<GameObject*>* pObjects);
    void parseTextures(XMLElement* pStateRoot);
};

#endif
