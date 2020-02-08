#pragma once
#include "main.h"
#include <queue> 

class Menu {
    private:
        Menu();
        static Menu* menu;
        lv_obj_t *tabview;
        
        lv_obj_t *tabInfo;
        lv_obj_t *tabDebug;
        lv_obj_t *tabTerminal;
        lv_obj_t *tabYus;

        lv_obj_t *debugTextArea;
        lv_obj_t *terminalTextArea;
        const int maxLinesOnScreen = 8;
        int numTerminalLines = 0;
        int numTerminalLinesOnScreen = 0;
        std::queue<std::string> terminalOutput;
        std::vector<std::string> debugOutput;

        void constructTerminalPage();
        void constructDebugPage();
        void constructYusPage();
        void constructTabview();
    public:
        static Menu* getMenu();
        void printTerminal(const std::string str);
        void addDebugPrint(int id, const std::string str);
};