#include "./header/random.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <bitset>
#include <tss2/tss2_sys.h>
#include <tss2/tss2_tctildr.h>
#include <tss2/tss2_tcti.h>


void checkTSS2Result(TSS2_RC result, const char* message) {
    if (result != TSS2_RC_SUCCESS) {
        std::cerr << message << " Error code: 0x" << std::hex << result << std::endl;
        exit(1);
    }
}

bool isTPMDevice(){
    std::ifstream tpm_device("/dev/tpm0");

    return tpm_device.good();

}

std::vector<int> generateRandomNumber(uint16_t bytes_requested){
    
    TSS2_TCTI_CONTEXT *tcti_context = nullptr;
    TSS2_SYS_CONTEXT *sys_context = nullptr;

    // TCTIコンテキストの初期化
    const char* tcti_name = "device"; // 使用するTCTIの名前
    const char* tcti_conf = nullptr; // デフォルト設定を使用

    TSS2_RC result = Tss2_TctiLdr_Initialize(tcti_name, &tcti_context);
    checkTSS2Result(result, "Failed to initialize TCTI context");

    // システムコンテキストの初期化
    size_t sys_ctx_size = Tss2_Sys_GetContextSize(0);
    sys_context = (TSS2_SYS_CONTEXT*)malloc(sys_ctx_size);
    if (!sys_context) {
        std::cerr << "Failed to allocate system context" << std::endl;
        Tss2_TctiLdr_Finalize(&tcti_context);
        std::terminate();
    }


    TSS2_ABI_VERSION abi_version = TSS2_ABI_VERSION_CURRENT;
    result = Tss2_Sys_Initialize(sys_context, sys_ctx_size, tcti_context, &abi_version);
    checkTSS2Result(result, "Failed to initialize system context");

    // TPM2_GetRandom コマンドを使用して乱数を生成
    TPM2B_DIGEST random_data = { .size = 0 };

    result = Tss2_Sys_GetRandom(sys_context, nullptr, bytes_requested, &random_data, nullptr);
    checkTSS2Result(result, "Failed to get random bytes");

    std::vector<int> result_vector;
    // 生成した乱数を出力
    for (size_t i = 0; i < random_data.size; ++i) {
        result_vector.push_back(static_cast<int>(random_data.buffer[i]));
    }

    // リソースのクリーンアップ
    Tss2_Sys_Finalize(sys_context);
    free(sys_context);
    Tss2_TctiLdr_Finalize(&tcti_context);

    return result_vector;

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
