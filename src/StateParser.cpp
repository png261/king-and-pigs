#include "StateParser.hpp"

#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "TextureManager.hpp"

bool StateParser::parseState(
    const char* stateFile,
    const std::string stateID,
    std::vector<GameObject*>* const pObjects)
{
    XMLDocument doc;
    doc.LoadFile(stateFile);

    XMLElement* const pRoot = doc.RootElement();
    if (pRoot == nullptr) {
        return false;
    }

    XMLElement* pStateRoot = nullptr;
    for (XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), stateID.c_str()) == 0) {
            pStateRoot = e;
            break;
        }
    }

    if (pStateRoot == nullptr) {
        return false;
    }

    XMLElement* pTextureRoot = nullptr;
    for (XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), "TEXTURES") == 0) {
            pTextureRoot = e;
            break;
        }
    }

    if (pTextureRoot) {
        parseTextures(pTextureRoot);
    }

    XMLElement* pObjectRoot = nullptr;
    for (XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), "OBJECTS") == 0) {
            pObjectRoot = e;
            break;
        }
    }

    if (pObjectRoot) {
        parseObjects(pObjectRoot, pObjects);
    }

    return true;
}

void StateParser::parseTextures(XMLElement* const pTextureRoot)
{
    for (XMLElement* e = pTextureRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        std::string fileName = e->Attribute("filename");
        std::string textureID = e->Attribute("ID");

        TextureManager::Instance()->load(fileName, textureID);
    }
}

void StateParser::parseObjects(XMLElement* const pObjectRoot, std::vector<GameObject*>* pObjects)
{
    for (XMLElement* e = pObjectRoot->FirstChildElement(); e != nullptr;
         e = e->NextSiblingElement()) {
        int x, y, width, height, numFrames, callbackID;

        if (e->Attribute("x")) {
            x = atoi(e->Attribute("x"));
        }
        if (e->Attribute("y")) {
            y = atoi(e->Attribute("y"));
        }
        if (e->Attribute("width")) {
            width = atoi(e->Attribute("width"));
        }
        if (e->Attribute("height")) {
            height = atoi(e->Attribute("height"));
        }
        if (e->Attribute("numFrames")) {
            numFrames = atoi(e->Attribute("numFrames"));
        }
        if (e->Attribute("callbackID")) {
            callbackID = atoi(e->Attribute("callbackID"));
        }

        GameObject* const pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(
            new LoaderParams(x, y, width, height, width, height, numFrames, callbackID));
        pObjects->push_back(pGameObject);
    }
}
