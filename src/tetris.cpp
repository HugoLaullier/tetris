#include "headers/constants.hpp"
#include "headers/admin.hpp"

int main(int argc, char **argv)
{
    srand(time(NULL));
    // srand(1); // DEBUG

    Admin admin;
    admin.start();

    return EXIT_SUCCESS;
}

// TODO list
/*
 - (tetrimino probability apparition)
 - music volume decrease at the end
 - (multiplayer mode online (with 2 humans))
 - valgrind memory leaks (check destructors)
 - player.hpp - sort methods
 ----------------------
 - remove debug printf and comments
 - documentation + all comment in english
 - README.md
 - cmake with options
*/