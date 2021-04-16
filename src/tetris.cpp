#include "../include/constants.hpp"
#include "../include/admin.hpp"

int main(int argc, char **argv)
{
    srand(time(NULL));

    Admin admin;
    admin.start();

    return EXIT_SUCCESS;
}