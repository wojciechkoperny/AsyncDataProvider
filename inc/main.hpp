#ifndef MAIN_HPP
#define MAIN_HPP

#include <functional>
struct workerDescr_t
{
    std::function<void *(void *)> Function;
    int FunctionArgs;
};

#endif

/*
-umiesc klase w innym pliku nazwana tak jak klsa
-doczytac functional
*/