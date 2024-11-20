#include "./header/random.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <bitset>


bool isTPMDevice(){
    std::ifstream tpm_device("/dev/tpm0");

    return tpm_device.good();

}

int main(int argc, char *argv[]) {

    // TPMが利用できなかったらエラーで終了
    if(!isTPMDevice()){
        std::cout << "TPM is not available." << std::endl;
        return -1;
    }

    uint16_t bytes_requested; // 取得する乱数のバイト数
    // 引数をバイト数にする（デフォルトは16）
    if(argc == 1){
        bytes_requested = 16;
    } else {
        bytes_requested = std::stoul(argv[1]);
    }

    std::ostringstream oss;

    for(auto random_number : generateRandomNumber(bytes_requested)){
        oss << std::bitset<6>(random_number);
    }

    std::cout << base64Decode(oss.str()) << std::endl;

    return 0;
}
