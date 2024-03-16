#include "fall_det.h"

/// window width
#define WIN_WIDTH  (200)
/// window height
#define WIN_HEIGHT (160)

int main(int argc, char **argv) {
    nanogui::init();

    new FDScreen(Eigen::Vector2i(WIN_WIDTH, WIN_HEIGHT), "Fall Detection", false);

    nanogui::mainloop();
    nanogui::shutdown();

    return 0;
}
