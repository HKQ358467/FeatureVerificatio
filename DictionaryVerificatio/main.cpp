#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<std::string, int> dict;

    // 添加一些键值对   
    dict["abc"] = 1;
    dict["汉字"] = 2;
	dict["bce"] = 3;
    dict["123"] = 4;

    // 遍历字典，打印键值对
    for (const auto& pair : dict) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}