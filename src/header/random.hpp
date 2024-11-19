#ifndef HEADER_RANDOM_HPP_
#define HEADER_RANDOM_HPP_
#include <vector>
#include <string>
#include <tss2/tss2_sys.h>
#include <tss2/tss2_tctildr.h>
#include <tss2/tss2_tcti.h>

/// @brief エラーハンドリング
/// @param  result エラー
/// @param  message エラーメッセージ
void checkTSS2Result(TSS2_RC result, const char* message);

/// @brief TPMが利用可能かを確認
/// @return 結果
bool isTPMDevice();

/// @brief 乱数の生成
/// @param bytes_requested 
/// @return 乱数を格納した動的配列
std::vector<int> generateRandomNumber(uint16_t bytes_requested);


/// @brief Base64でデコード
/// @param input 乱数
/// @return デコード結果
std::string base64Decode(const std::string &input);

#endif