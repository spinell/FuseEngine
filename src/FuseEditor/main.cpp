#include "EditorApplication.h"

#include <memory>

int main() {
    auto app = std::make_unique<fuse::EditorApplication>();
    app->run();
    app.reset();
    return 0;
}
