#pragma once

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    virtual void load(std::unique_ptr<LoaderParams> const& params) override;
    virtual void update() override;
    virtual void loadAnimation() override;

    virtual void open();
    virtual void close();
    virtual bool isOpened() const;
    virtual bool isClosed() const;

protected:
    enum animations {
        DOOR_CLOSED,
        DOOR_OPENING,
        DOOR_CLOSING,
    };

    bool is_opened_;
};
