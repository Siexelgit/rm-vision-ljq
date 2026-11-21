#include <iostream>
#include "mean.h"

int main() {
    std::vector<double> empty_vec;
    auto res = meanLength(empty_vec);
    if (res.has_value()) {
        std::cerr << "错误：空数组应该返回空！" << std::endl;
        return 1;
    }
    std::cout << "测试1通过：空数组返回nullopt" << std::endl;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    auto res2 = meanLength(data);
    if (!res2.has_value() || *res2 != 2.5) {
        std::cerr << "错误：均值计算不正确！" << std::endl;
        return 1;
    }
    std::cout << "测试2通过：均值正确" << std::endl;

    int cnt = countGreaterOrEqual(data, 3.0);
    if (cnt != 2) {
        std::cerr << "错误：阈值计数不正确！" << std::endl;
        return 1;
    }
    std::cout << "测试3通过：阈值计数正确" << std::endl;

    return 0;
}