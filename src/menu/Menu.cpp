#include "Menu.hpp"
#include "Orange.h"
#include "HeLied.hpp"

Menu *Menu::menu = NULL;
Menu *Menu::getMenu() {
	if (menu == NULL) {
		menu = new Menu();
	}
	return menu;
}

Menu::Menu() : terminalOutput(), debugOutput(10, "") {
    constructTabview();
    constructTerminalPage();
    constructDebugPage();
    // constructYusPage();


    lv_obj_t *label = lv_label_create(tabInfo, NULL);
    lv_label_set_text(label, "help");
    if(HeLied::getRobot()->drive->turnsMirrored) {
        lv_label_set_text(label, "You are on red.");

    } else {
        lv_label_set_text(label, "You are on blue.");
    }
}

void Menu::printTerminal(const std::string str) {
    if(numTerminalLinesOnScreen < maxLinesOnScreen) {
        numTerminalLinesOnScreen++;
        terminalOutput.push(std::to_string(numTerminalLines) + " " + str);
    } else {
        // Delete top line
        terminalOutput.push(std::to_string(numTerminalLines) + " " + str);
        terminalOutput.pop();
    }
    numTerminalLines++;
    //Now print to screen
    std::string screenOut;
    std::queue tempCopy(terminalOutput);
    while(!tempCopy.empty()) {
        screenOut = screenOut + tempCopy.front() + std::string("\n");
        tempCopy.pop();
    }
    lv_label_set_text(terminalTextArea, screenOut.c_str());
}

void Menu::addDebugPrint(int id, const std::string str) {
    if(id < maxLinesOnScreen && id >= 0) {
        debugOutput[id] = str;

        // Update debug screen
        std::string screenOut;
        for(int i=0; i<maxLinesOnScreen; i++) {
            screenOut += std::to_string(i) + " " + debugOutput[i] + std::string("\n");
        }
        lv_label_set_text(debugTextArea, screenOut.c_str());
    }
}

void Menu::constructTabview() {
    lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), NULL);
    lv_tabview_set_sliding(tabview, false);

    // Create tabs
    tabInfo = lv_tabview_add_tab(tabview, "Info");
    tabDebug = lv_tabview_add_tab(tabview, "Debug");
    tabTerminal = lv_tabview_add_tab(tabview, "Terminal");
    // tabYus = lv_tabview_add_tab(tabview, "yus");


    // Style the tab buttons
    static lv_style_t tabButtonStyle;
    lv_style_copy(&tabButtonStyle, &lv_style_btn_tgl_rel);
    tabButtonStyle.body.padding.ver = 8;
    tabButtonStyle.body.radius = 0;
    tabButtonStyle.body.main_color = LV_COLOR_MAKE(0x72,0x72,0x72);
    tabButtonStyle.body.grad_color = LV_COLOR_MAKE(0x72,0x72,0x72);
    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &tabButtonStyle);
    static lv_style_t highlightedTabButtonStyle;
    lv_style_copy(&highlightedTabButtonStyle, &lv_style_plain_color);
    highlightedTabButtonStyle.body.padding.inner = 2;
    highlightedTabButtonStyle.body.main_color = LV_COLOR_ORANGE;
    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_INDIC, &highlightedTabButtonStyle);
}

void Menu::constructDebugPage() {
    debugTextArea = lv_label_create(tabDebug, NULL);
    lv_obj_set_size(debugTextArea, 450, 160); // :(
    lv_label_set_text(debugTextArea, "0\n1\n2\n3\n4\n5\n6\n7");
}

void Menu::constructTerminalPage() {
    terminalTextArea = lv_label_create(tabTerminal, NULL);
    lv_obj_set_size(terminalTextArea, 450, 160); // :(
    lv_label_set_text(terminalTextArea, "");
}

void Menu::constructYusPage() {
    lv_obj_t *yus = lv_img_create(tabYus, NULL);
    lv_img_set_src(yus, &orange);
} 
