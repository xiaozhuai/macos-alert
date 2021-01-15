//
// Created by xiaozhuai on 2021/1/15.
//

#include "Alert.h"
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

int Alert::Show() {
    NSAlert *alert = [[NSAlert alloc] init];

    alert.icon = [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:m_icon.c_str()]];

    alert.window.title = [NSString stringWithUTF8String:m_title.c_str()];

    [alert setMessageText:[NSString stringWithUTF8String:m_message.c_str()]];

    if (!m_subMessage.empty()) {
        [alert setInformativeText:[NSString stringWithUTF8String:m_subMessage.c_str()]];
    }

    for (int i = 0; i < m_buttons.size(); ++i) {
        auto b = [alert addButtonWithTitle:[NSString stringWithUTF8String:m_buttons[i].c_str()]];
        b.highlighted = m_defaultButton == i;
    }

    [[NSRunningApplication currentApplication] activateWithOptions:NSApplicationActivateAllWindows];

    int result = (int) [alert runModal];
    int btnIndex = (int) (result - NSAlertFirstButtonReturn);
    [alert release];
    return btnIndex;
}
