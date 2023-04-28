#pragma once

#include <functional>
#include <unordered_map>

#include "Animation.hpp"
#include "Shapes.hpp"
#include "UiObject.hpp"

class Button final : public UiObject
{
public:
    Button(const std::string& text, const float border_radius = 20.0f);

    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void draw() const override;

    void onClick(const std::function<void()>& callback);
    void disable();
    void enable();
    bool isDisabled() const;

private:
    bool is_disabled_;
    std::string text_;
    Rectangle rectangle_;
    int border_radius_;

    std::function<void()> callback_;
};
