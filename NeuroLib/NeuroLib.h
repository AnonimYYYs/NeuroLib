#ifndef NEUROLIB_H
#define NEUROLIB_H

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


extern "C" {
    namespace neurolib {
        DLLEXPORT int neuro_sum(int a, int b);
    }
}

#endif //NEUROLIB_H
