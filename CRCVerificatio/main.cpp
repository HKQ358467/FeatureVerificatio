#include <iostream>
#include <iomanip>
#include <cstdint>

// CRC-8 多项式 G(X) = x^8 + x^5 + x^4 + 1
const uint8_t CRC_POLYNOMIAL = 0x31; // 0x31 对应二进制 110001

// 计算 CRC-8 校验码
uint8_t calculateCRC8(const uint8_t *data, size_t length) {
    uint8_t crc = 0;

    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i]; // 异或操作

        for (int j = 0; j < 8; ++j) {
            if ((crc & 0x80) != 0) {
                crc = (crc << 1) ^ CRC_POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int main() {
    // 示例数据
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};

    // 计算 CRC-8 校验码
    uint8_t crcResult = calculateCRC8(data, sizeof(data) / sizeof(data[0]));

    // 输出结果
    std::cout << "Data: ";
    for (uint8_t byte : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }

    std::cout << "\nCRC-8 Checksum: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(crcResult) << std::endl;

    return 0;
}
