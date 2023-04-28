#pragma once

#include <memory>
#include <vector>

#include "Layer.hpp"
#include "Object.hpp"

class ObjectLayer final : public Layer
{
public:
    void update();
    void render() const;

    void addObject(std::unique_ptr<Object> object);

private:
    std::vector<std::unique_ptr<Object>> objects_;
};
