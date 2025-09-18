#pragma once

namespace fuse {

/// @brief Base class for all panel.
class EditorPanel {
public:
    EditorPanel() = default;

    virtual ~EditorPanel() = default;

    EditorPanel(const EditorPanel&)            = delete;
    EditorPanel(EditorPanel&&)                 = delete;
    EditorPanel& operator=(const EditorPanel&) = delete;
    EditorPanel& operator=(EditorPanel&&)      = delete;

    /// @brief
    virtual void onImGui(bool& isOpen) = 0;
};


} // namespace fuse
