#include "Base64.h"

#include <iostream>

int main()
{
    std::cout << Base64::encode("Ow!", 3) << "\n";    // T3ch
    std::cout << Base64::encode("Ow!c", 4) << "\n";   // T3chYw==
    std::cout << Base64::encode("Ow!cd", 5) << "\n";  // T3chY2Q=
    
    char buf[100] = { 0 };
    unsigned int size = 0;
    std::cout << Base64::decode("T3ch", buf, &size) << "\n";
    std::cout << "1-> " << buf << "\n";
    memset(buf, 0, 100);
    std::cout << Base64::decode("T3chYw==", buf, &size) << "\n";
    std::cout << "2-> " << buf << "\n";
    memset(buf, 0, 100);
    std::cout << Base64::decode("T3chY2Q=", buf, &size) << "\n";
    std::cout << "3-> " << buf << "\n";

    getchar();
    return 0;
}