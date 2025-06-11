#include "json2cpp/json2cpp.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "用法: " << argv[0] << " <json文件路径> <cpp文件路径>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "无法打开文件: " << argv[1] << "\n";
        return 1;
    }
    std::ofstream out(argv[2]);
    if (!out) {
        std::cerr << "无法打开文件: " << argv[2] << "\n";
        return 1;
    }
    to_cpp(in, out);
    return 0;
}