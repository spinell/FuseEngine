#pragma once

#include "EditorPanel.h"

namespace fuse {

/// @brief
class LogPanel : public EditorPanel {
public:
    LogPanel();
    ~LogPanel() override = default;

    LogPanel(const LogPanel&)              = delete;
    LogPanel& operator=(const LogPanel&)   = delete;
    LogPanel(const LogPanel&&)             = delete;
    LogPanel&& operator=(const LogPanel&&) = delete;

    void onImGui(bool& isOpen) override;
};


} // namespace fuse
