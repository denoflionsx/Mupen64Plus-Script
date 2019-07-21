#include "callbacks.h"

// #########################################################
// ## Universal Variables
// #########################################################

unsigned int count_frame = 0;
static unsigned int ready_frame = 1;

// #########################################################
// ## Threading Handlers
// #########################################################

#ifdef WIN32

#include <windows.h>

HANDLE mutex_frame = CreateMutex(NULL, FALSE, NULL); 

bool mutex_frame_get() {
    bool ready;
    DWORD dWait = WaitForSingleObject(mutex_frame, INFINITE);
    switch (dWait) {
        case WAIT_OBJECT_0: 
            __try { ready = ready_frame; }
            __finally { 
                if (! ReleaseMutex(mutex_frame)) 
                    printf("FRAME_CALLBACK_EXCEPTION\n"); 
            } break; 

        case WAIT_ABANDONED: 
            printf("FRAME_CALLBACK_EXCEPTION\n"); 
            break;
    } return ready;
}

void mutex_frame_set(int ready) {
    DWORD dWait = WaitForSingleObject(mutex_frame, INFINITE);
    switch (dWait) {
        case WAIT_OBJECT_0: 
            __try { ready_frame = ready; }
            __finally { 
                if (! ReleaseMutex(mutex_frame)) 
                    printf("FRAME_CALLBACK_EXCEPTION\n"); 
            } break; 

        case WAIT_ABANDONED: 
            printf("FRAME_CALLBACK_EXCEPTION\n"); 
            break;
    }
}

#else

#include <pthread.h>

pthread_mutex_t mutex_frame = PTHREAD_MUTEX_INITIALIZER;

bool mutex_frame_get() {
    bool ready;
    pthread_mutex_lock(&mutex_frame);
    ready = ready_frame;
    pthread_mutex_unlock(&mutex_frame);
    return ready;
}

void mutex_frame_set(int ready) {
    pthread_mutex_lock(&mutex_frame);
    ready_frame = ready;
    pthread_mutex_unlock(&mutex_frame);
}

#endif

// #########################################################
// ## Async Worker (ThreadSafe) Objects
// #########################################################

class AW_Frame;
AW_Frame* awFrame;
class AW_Frame : public AsyncWorker {
    public:
        AW_Frame(Function& callback) : AsyncWorker(callback) {}
        ~AW_Frame() {}
        void Execute() {}
        void OnOK() {
            HandleScope scope(Env());
            Callback().Call({Number::New(Env(), count_frame)});
            awFrame = new AW_Frame(Callback().Value());
            mutex_frame_set(1);
        }
        void OnError(const Napi::Error& e) {
            printf("FRAME_CALLBACK_EXCEPTION(Node Thread)\n");
            awFrame = new AW_Frame(Callback().Value());
            mutex_frame_set(1);
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
    while (!mutex_frame_get())
        this_thread::sleep_for(chrono::milliseconds(1));
    
    memcpy(&count_frame, &frameIndex, 4);
    mutex_frame_set(0);
    awFrame->Queue(); 
}