#ifndef BASE_64_H_20180923
#define BASE_64_H_20180923

#include <string>

class Base64
{
public:
    static std::string encode(void *p, unsigned int size);
    static bool decode(const std::string &str, void *p, unsigned int *size);
    static unsigned int getDecodeSize(const std::string &str);
};

#endif // !BASE_64_H_20180923
