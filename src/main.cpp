#include <iostream>
#include <unistd.h>
#include "Alert.h"
#include "INI.h"

inline std::string &trim(std::string &str, const char *characters = " \t\r\n") {
    return str.erase(0, str.find_first_not_of(characters))
            .erase(str.find_last_not_of(characters) + 1);
}

void showUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << R"(
./macos-alert <<EOF
title = Test
message = Hello world!
subMessage = Have fun playing with macos-alert
icon = icon.png
buttons = Yes, No
needRet = true
EOF
)" << std::endl;
    std::cout << "Options are in ini format" << std::endl;
    std::cout << "Valid options:" << std::endl;
    std::cout << "  title            [string] Title" << std::endl;
    std::cout << "  message          [string] Message" << std::endl;
    std::cout << "  subMessage       [string] Sub message" << std::endl;
    std::cout << "  icon             [string] Icon file" << std::endl;
    std::cout << "  buttons          [array]  Buttons (eg: Yes, NO)" << std::endl;
    std::cout << "  defaultButton    [int]    Default button index" << std::endl;
    std::cout << "  needRet          [bool]   Print result" << std::endl;
    std::cout << "  needFork         [bool]   Fork child process, non-blocking" << std::endl;
    std::cout << "  pidFile          [string] If needFork, write child pid to file" << std::endl;
    std::cout << "  retFile          [string] If needFork & needRet, write result to file" << std::endl;
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            showUsage();
            return 0;
        } else {
            showUsage();
            return 1;
        }
    }

    INI::File ini;
    ini.Load(std::cin, true);

    auto title = ini.GetValue("title", "").AsString();
    auto message = ini.GetValue("message", "").AsString();
    auto subMessage = ini.GetValue("subMessage", "").AsString();
    auto icon = ini.GetValue("icon", "").AsString();
    auto buttonsV = ini.GetValue("buttons", "").AsArray();
    std::vector<std::string> buttons;
    for (int i = 0; i < buttonsV.Size(); ++i) {
        auto button = buttonsV.GetValue(i, "").AsString();
        trim(button);
        if (button.empty()) continue;
        buttons.emplace_back(button);
    }
    auto defaultButton = ini.GetValue("defaultButton", 0).AsInt();
    auto needRet = ini.GetValue("needRet", true).AsBool();
    auto needFork = ini.GetValue("needFork", false).AsBool();
    auto pidFile = ini.GetValue("pidFile", "").AsString();
    auto retFile = ini.GetValue("retFile", "").AsString();

    if (needFork) {
        if (fork() == 0) { // child
            int pid = getpid();

            if (!pidFile.empty()) {
                std::ofstream opid(pidFile);
                if (opid) {
                    opid << std::to_string(pid);
                }
            }

            Alert alert(title, message, subMessage, icon, buttons, defaultButton);
            auto ret = alert.Show();

            if (needRet && !retFile.empty()) {
                std::ofstream oret(retFile);
                if (oret) {
                    oret << buttons[ret];
                }
            }
        }
    } else {
        Alert alert(title, message, subMessage, icon, buttons, defaultButton);
        auto ret = alert.Show();

        if (needRet) {
            std::cout << buttons[ret] << std::endl;
        }
    }

    return 0;
}
