#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

std::string base64Decode(const std::string &input) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    auto isBase64 = [](unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    };

    std::string output;
    std::vector<int> charIndex(256, -1);
    for (size_t i = 0; i < base64_chars.size(); ++i) {
        charIndex[static_cast<unsigned char>(base64_chars[i])] = i;
    }

    int val = 0, bits = -8;
    for (unsigned char c : input) {
        if (charIndex[c] == -1) {
            if (c == '=') break;  // padding
            else if (!isspace(c)) throw std::invalid_argument("Invalid Base64 character");
        }

        val = (val << 6) + charIndex[c];
        bits += 6;

        if (bits >= 0) {
            output.push_back(static_cast<char>((val >> bits) & 0xFF));
            bits -= 8;
        }
    }

    return output;
}

int main() {
        std::string encodedString = "SGVsbG8gV29ybGQh"; // "Hello World!" in Base64
        std::string decodedString = base64Decode(encodedString);

        std::cout << decodedString << std::endl;
}
