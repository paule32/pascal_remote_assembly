# include <iostream>

# include "Integer.h"

int main(int argc, char **argv)
{
    Integer< int         > num1 = 42;
    Integer< std::string > num2 = std::string("127");
    
    return 0;
}
