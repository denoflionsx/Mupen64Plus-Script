#include "callbacks.h"

// #########################################################
// ## Universal Variables
// #########################################################

unsigned int count_frame = 0;
unsigned int ready_frame = 1;

// #########################################################
// ## Async Worker (ThreadSafe) Objects
// #########################################################

class AW_Frame;
AW_Frame* awFrame;
class AW_Frame : public AsyncWorker {
    public:
        AW_Frame(Function& callback) : AsyncWorker(callback) {}
        ~AW_Frame() {}
        void Execute() { }
        void OnOK() {
            HandleScope scope(Env());
            Callback().Call({Number::New(Env(), count_frame)});
            unsigned int ready = 1; memcpy(&ready_frame, &ready, 4);
            awFrame = new AW_Frame(Callback().Value());
        }
};
 
// #########################################################
// ## External Callback Initializer Functions
// #########################################################

void Init_Callback_Frame(Function cb) { awFrame = new AW_Frame(cb); }

// #########################################################
// ## Mupen Callback Functions
// #########################################################

#include <chrono>
#include <thread>
using namespace std;

void M64P_Callback_Frame(unsigned int frameIndex) {
    if (frameIndex < 1) return;

    while (!ready_frame)
        this_thread::sleep_for(chrono::milliseconds(1));
    
    memcpy(&count_frame, &frameIndex, 4);
    unsigned int ready = 0; memcpy(&ready_frame, &ready, 4);
    awFrame->Queue();
}