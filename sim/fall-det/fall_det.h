/**
 * @file
 * @brief
 * @author boo
 */

#ifndef FALL_DETECTION_H
#define FALL_DETECTION_H

#include "nanogui/nanogui.h"

class FDScreen : public nanogui::Screen {
public:
    FDScreen(const Eigen::Vector2i &size, const std::string &caption, bool resizable = true);
    virtual ~FDScreen();
    
private:
    Eigen::Vector2i m_size;
    nanogui::Window *m_window = nullptr;
    nanogui::GridLayout *m_layout = nullptr;
    nanogui::CheckBox *m_fall_det_cb = nullptr;
    nanogui::CheckBox *m_failure_cb = nullptr;
    nanogui::CheckBox *m_on_off_cb = nullptr;
    nanogui::Button *m_send_btn = nullptr;

    /// function that setups widgets
    void setup();
    /// function that is callback registered to send button
    void sendButton_onClicked(void);
};

#endif
