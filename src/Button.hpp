#pragma once

#include <functional>

#include "Animation.hpp"
#include "Shapes.hpp"
#include "UiObject.hpp"

class Button final : public UiObject
{
public:
    Button();

    void load(const LoaderParams& params) override;
    void update() override;
    void draw() const override;

    void setTitle(const std::string& title);
    void setTexture(const std::string& texture_id);
    void setBackgroundColor(
        const Color& normal_color,
        const Color& hovered_color = ColorName::GRAY,
        const Color& disabled_color = ColorName::GRAY);
    void setFontColor(const Color& color);
    void setBorderRadius(const int border_radius);

    void onClick(const std::function<void()>& callback);
    void disable();
    void enable();
    bool isDisabled() const;
    bool isHovered() const;

private:
    std::function<void()> callback_;

    bool is_disabled_;
    bool is_hovered_;

    Rectangle rectangle_;
    std::string texture_id_;
    int border_radius_;

    std::string title_;
    Color font_color_;

    Color normal_color_;
    Color hovered_color_;
    Color disabled_color_;
};
