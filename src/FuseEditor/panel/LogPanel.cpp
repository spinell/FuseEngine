#include "LogPanel.h"

#include <imgui.h>

namespace fuse {

LogPanel::LogPanel() {}

void LogPanel::onImGui(bool& isOpen) {
    if (!isOpen) {
        return;
    }

    if (ImGui::Begin("Console##Console", &isOpen)) {
    }
    ImGui::End();
}

} // namespace fuse
