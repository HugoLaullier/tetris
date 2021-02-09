#include "utils.hpp"

int unit_to_pix_col(int unit)
{
    return 30 * (unit + 5);
}

int unit_to_pix(int unit)
{
    return 30 * unit;
}