#pragma once
class Message {
    public:
        char* rawString;
        Message();
        virtual void decode(char* string) = 0;
};

class OdomMessage : Message {
    public:
        OdomMessage();
        void decode(char* string);
    private:
        float x = 0;
        float y = 0;
        float theta = 0;
};

class VisionOdomMessage : Message {
    public:
        VisionOdomMessage();
        void decode(char* string);
}; 