#include "LogPanel.h"

#include <FuseEditor/embed/fonts/IconsMaterialDesignIcons.h>

#include <imgui.h>

namespace fuse {

LogPanel::LogPanel() = default;

void LogPanel::onImGui(bool& isOpen) {
    if (!isOpen) {
        return;
    }

    if (ImGui::Begin(ICON_MDI_VIEW_LIST "Console###Console", &isOpen)) {
    }
    ImGui::End();
}

} // namespace fuse
