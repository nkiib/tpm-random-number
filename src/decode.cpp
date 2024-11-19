#include <iostream>
#include <string>
#include <bitset>

std::string base64Decode(const std::string &binaryStr) {
    const std::string base64Chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::string result = "";
    
    // 6ビットごとに分けてBase64に変換
    for (size_t i = 0; i < binaryStr.length(); i += 6) {
        std::string chunk = binaryStr.substr(i, 6);
        // 6ビットが足りない場合は0を埋める
        if (chunk.length() < 6) {
            chunk.append(6 - chunk.length(), '0');
        }

        // 6ビットの2進数を10進数に変換
        int index = std::bitset<6>(chunk).to_ulong();
        
        // そのインデックスに対応するBase64文字を取得
        result += base64Chars[index];
    }

    return result;
}

