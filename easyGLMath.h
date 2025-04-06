#pragma once
#include <cstdint>


double map(double x, double inmin, double inmax, double outmin, double outmax) {
    return outmin + (x - inmin) * (outmax - outmin) / (inmax - inmin);
}

double mapRgbaToFloat(uint8_t x){
    return map(x,0,255,0,1);
}