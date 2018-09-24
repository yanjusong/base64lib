#include "Base64.h"

#include <map>

static std::map<char, int> b64decode = 
{
    { 'A', 0 },
    { 'B', 1 },
    { 'C', 2 },
    { 'D', 3 },
    { 'E', 4 },
    { 'F', 5 },
    { 'G', 6 },
    { 'H', 7 },
    { 'I', 8 },
    { 'J', 9 },
    { 'K', 10 },
    { 'L', 11 },
    { 'M', 12 },
    { 'N', 13 },
    { 'O', 14 },
    { 'P', 15 },
    { 'Q', 16 },
    { 'R', 17 },
    { 'S', 18 },
    { 'T', 19 },
    { 'U', 20 },
    { 'V', 21 },
    { 'W', 22 },
    { 'X', 23 },
    { 'Y', 24 },
    { 'Z', 25 },
    { 'a', 26 },
    { 'b', 27 },
    { 'c', 28 },
    { 'd', 29 },
    { 'e', 30 },
    { 'f', 31 },
    { 'g', 32 },
    { 'h', 33 },
    { 'i', 34 },
    { 'j', 35 },
    { 'k', 36 },
    { 'l', 37 },
    { 'm', 38 },
    { 'n', 39 },
    { 'o', 40 },
    { 'p', 41 },
    { 'q', 42 },
    { 'r', 43 },
    { 's', 44 },
    { 't', 45 },
    { 'u', 46 },
    { 'v', 47 },
    { 'w', 48 },
    { 'x', 49 },
    { 'y', 50 },
    { 'z', 51 },
    { '0', 52 },
    { '1', 53 },
    { '2', 54 },
    { '3', 55 },
    { '4', 56 },
    { '5', 57 },
    { '6', 58 },
    { '7', 59 },
    { '8', 60 },
    { '9', 61 },
    { '+', 62 },
    { '/', 63 },
};

static char b64encode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char getBase64Char(int key)
{
    return b64encode[key];
}

static int getBase64Value(char ch)
{
    std::map<char, int>::iterator it = b64decode.find(ch);
    if (it != b64decode.end()) {
        return it->second;
    } else {
        return -1;
    }
}

std::string Base64::encode(void *p, unsigned int size)
{
    int remainder = size % 3;
    int count = size / 3;
    const char *s = (const char *)p;
    std::string base64Str;
    unsigned char c1, c2, c3;
    int k1, k2, k3, k4;

    for (int i = 0; i < count; ++i) {
        c1 = s[i * 3 + 0];
        c2 = s[i * 3 + 1];
        c3 = s[i * 3 + 2];

        k1 = c1 >> 2;
        k2 = ((c1 & 0x03) << 4) | (c2 >> 4);
        k3 = ((c2 & 0x0f) << 2) | (c3 >> 6);
        k4 = c3 & 0x3f;

        base64Str += getBase64Char(k1);
        base64Str += getBase64Char(k2);
        base64Str += getBase64Char(k3);
        base64Str += getBase64Char(k4);
    }

    if (1 == remainder) {
        c1 = s[count * 3];
        k1 = c1 >> 2;
        k2 = (c1 & 0x03) << 4;
        base64Str += getBase64Char(k1);
        base64Str += getBase64Char(k2);
        base64Str += "==";
    } else if (2 == remainder) {
        c1 = s[count * 3];
        c2 = s[count * 3 + 1];
        k1 = c1 >> 2;
        k2 = ((c1 & 0x03) << 4) | (c2 >> 4);
        k3 = ((c2 & 0x0f) << 2);
        base64Str += getBase64Char(k1);
        base64Str += getBase64Char(k2);
        base64Str += getBase64Char(k3);
        base64Str += "=";
    }

    return base64Str;
}

bool Base64::decode(const std::string &str, void *p, unsigned int *size)
{
    int strLen = str.length();
    if (strLen < 4 || strLen % 4 != 0) {
        return false;
    }
    int remainder = 0;
    remainder += (str[strLen - 1] == '=' ? 1 : 0);
    remainder += (str[strLen - 2] == '=' ? 1 : 0);
    
    int count = strLen / 4;
    count -= (remainder == 0 ? 0 : 1);
    unsigned char c1, c2, c3, c4;
    char *s = (char *)p;
    int pi = 0;

    for (int i = 0; i < count; ++i) {
        c1 = getBase64Value(str[i * 4 + 0]);
        c2 = getBase64Value(str[i * 4 + 1]);
        c3 = getBase64Value(str[i * 4 + 2]);
        c4 = getBase64Value(str[i * 4 + 3]);

        if (c1 == -1 || c2 == -1 || c3 == -1 || c4 == -1) {
            return false;
        }

        s[pi++] = (c1 << 2) | (c2 >> 4);
        s[pi++] = (c2 << 4) | (c3 >> 2);
        s[pi++] = (c3 << 6) | c4;
    }

    if (1 == remainder) {
        c1 = getBase64Value(str[count * 4 + 0]);
        c2 = getBase64Value(str[count * 4 + 1]);
        c3 = getBase64Value(str[count * 4 + 2]);

        if (c1 == -1 || c2 == -1 || c3 == -1) {
            return false;
        }

        s[pi++] = (c1 << 2) | (c2 >> 4);
        s[pi++] = (c2 << 4) | (c3 >> 2);
    } else if (2 == remainder) {
        c1 = getBase64Value(str[count * 4 + 0]);
        c2 = getBase64Value(str[count * 4 + 1]);

        if (c1 == -1 || c2 == -1) {
            return false;
        }

        s[pi++] = (c1 << 2) | (c2 >> 4);
    }

    *size = pi;
    return true;
}

unsigned int Base64::getDecodeSize(const std::string &str)
{
    int strLen = str.length();
    if (strLen < 4 || strLen % 4 != 0) {
        return 0;
    }

    return strLen / 4 * 3;
}

