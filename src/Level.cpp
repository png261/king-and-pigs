#include "Level.h"
#include "Game.h"
#include "Layer.h"
#include "TextureManager.h"
#include "TileLayer.h"

Level::Level() {}

Level::~Level()
{
    for (auto& layer : m_layers) {
        delete layer;
    }

    m_layers.clear();
}

void Level::render()
{
    for (auto& layer : m_layers) {
        layer->render();
    }
}

void Level::update()
{
    for (auto& layer : m_layers) {
        layer->update(this);
    }
}
