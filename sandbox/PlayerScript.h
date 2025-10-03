#pragma once
#include <FuseCore/scene/components/CNativeScript.h>

struct PlayerScript : public fuse::NativeScript {
    void onCreate() override;
    void onUpdate(float /*elapsed*/) override;
    void onLastUpdate(float /*elapsed*/) override;
    void onDestroy() override;
};
