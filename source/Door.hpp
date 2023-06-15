#pragma once

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    virtual void load(const LoaderParams& params) override;
    virtual void update() override;
    virtual void loadAnimation() override;

    virtual void open();
    virtual void close();
    virtual bool isOpened() const;
    virtual bool isClosed() const;

protected:
    enum AnimationID {
        DOOR_CLOSED,
        DOOR_OPENING,
        DOOR_CLOSING,
    };

    bool is_opened_;
};
