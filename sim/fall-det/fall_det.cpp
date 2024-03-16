#include "fall_det.h"

FDScreen::FDScreen(const Eigen::Vector2i &size, const std::string &caption, bool resizable)
    : nanogui::Screen(size, caption, resizable)
{
    m_size = size;
    setup();
}

FDScreen::~FDScreen() {

}

void FDScreen::setup() {
    m_window = new nanogui::Window(this, "");
    m_layout = new nanogui::GridLayout();

    m_layout->setColAlignment({nanogui::Alignment::Maximum, nanogui::Alignment::Fill});
    m_layout->setSpacing(0, 16);
    m_layout->setSpacing(1, 0);
    m_layout->setMargin(10);

    m_window->setPosition(Eigen::Vector2i(0, 0));
    m_window->setLayout(m_layout);
    m_window->setFixedSize(m_size);
    
    {
	new nanogui::Label(m_window, "Fall Detected?", "sans", 18);
	m_fall_det_cb = new nanogui::CheckBox(m_window, "");
	m_fall_det_cb->setChecked(false);
    }
    {
	new nanogui::Label(m_window, "Sensor Failed?", "sans", 18);
	m_failure_cb = new nanogui::CheckBox(m_window, "");
	m_failure_cb->setChecked(false);
    }
    {
	new nanogui::Label(m_window, "On / Off", "sans", 18);
	m_on_off_cb = new nanogui::CheckBox(m_window, "");
	m_on_off_cb->setChecked(true);
    }
    {
	m_send_btn = new nanogui::Button(m_window, "Send", ENTYPO_ICON_PUBLISH);
	m_send_btn->setCallback([=] {this->sendButton_onClicked();});	    
	m_send_btn->setFixedWidth(100);
	m_send_btn->setFixedHeight(24);
	m_send_btn->setFontSize(18);
    }
    
    this->setVisible(true);
    this->performLayout();
    
    return;
}


void FDScreen::sendButton_onClicked(void) {
    std::cout << "Fall Detection Data:" << std::endl;
    std::cout << "Detected : "  << m_fall_det_cb->checked() << std::endl;
    std::cout << "Failure  : "  << m_failure_cb->checked() << std::endl;
    std::cout << "On/Off   : "  << m_on_off_cb->checked() << std::endl;
    
    return;
}
