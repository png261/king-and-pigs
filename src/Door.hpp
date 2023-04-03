#pragma once

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    virtual ~Door() = default;
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) override;
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

    bool m_bOpened;
};
