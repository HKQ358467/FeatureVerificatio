#include <iostream>
#include <fstream>
#include <string>

void readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open config file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::string ip;
    int port;

    while (getline(file, line)) {
        if (line.find("ip") != std::string::npos) {
            size_t start = line.find(":") + 3;
            size_t end = line.find_last_of("\"");
            ip = line.substr(start, end - start);
        } else if (line.find("port") != std::string::npos) {
            size_t start = line.find(":") + 2;
            port = std::stoi(line.substr(start));
        }
    }

    std::cout << "IP: " << ip << ", Port: " << port << std::endl;
}

int main() {
    readConfig("config.json");
    return 0;
}