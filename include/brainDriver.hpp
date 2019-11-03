#pragma once
#include "main.h"

class BrainDriver {
    public:
        BrainDriver();
    private:
        static void asyncReadSerialTask(void* param);
		static void resetBuffer(char* buffer);
};