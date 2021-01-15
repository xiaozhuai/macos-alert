//
// Created by xiaozhuai on 2021/1/15.
//

#ifndef MACOS_DIALOG_DIALOG_H
#define MACOS_DIALOG_DIALOG_H

#include <string>
#include <vector>

class Alert {
public:
    Alert(std::string title, std::string message, std::string subMessage, std::string icon, std::vector<std::string> buttons, int defaultButton = 0)
            : m_title(std::move(title)),
              m_message(std::move(message)),
              m_subMessage(std::move(subMessage)),
              m_icon(std::move(icon)),
              m_buttons(std::move(buttons)),
              m_defaultButton(defaultButton) {}

    int Show();

private:
    std::string m_title;
    std::string m_message;
    std::string m_subMessage;
    std::string m_icon;
    std::vector<std::string> m_buttons;
    int m_defaultButton = 0;
};


#endif //MACOS_DIALOG_DIALOG_H
