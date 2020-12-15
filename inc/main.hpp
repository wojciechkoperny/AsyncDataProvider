#ifndef MAIN_HPP
#define MAIN_HPP

#include <functional>
typedef struct
{
    std::function<void *(void *)> Function;
    int FunctionArgs;
} workerDescr_t;

#endif

/*
-umiesc klase w innym pliku nazwana tak jak klsa
-doczytac functional
*/