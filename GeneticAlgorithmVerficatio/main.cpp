#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// 适应度函数
double fitness(const std::vector<int>& individual) {
    double sum = 0;
    for (int i : individual) {
        sum += i;
    }
    return sum;
}

// 选择操作
std::vector<int> selection(const std::vector<std::vector<int>>& population) {
    // 这里简单地选择适应度最高的个体
    auto best = max_element(population.begin(), population.end(),
        [](const std::vector<int>& a, const std::vector<int>& b) {
            return fitness(a) < fitness(b);
        });
    return *best;
}

// 交叉操作
std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    std::vector<int> child(parent1.size());
    for (size_t i = 0; i < parent1.size(); ++i) {
        child[i] = i < parent1.size() / 2 ? parent1[i] : parent2[i];
    }
    return child;
}

// 变异操作
void mutation(std::vector<int>& individual) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, individual.size() - 1);
    individual[dis(gen)] = dis(gen);
}

int main() {
    // 初始化种群
    std::vector<std::vector<int>> population(100, std::vector<int>(10, 0));

    for (int generation = 0; generation < 1000; ++generation) {
        std::vector<std::vector<int>> new_population;

        for (size_t i = 0; i < population.size(); ++i) {
            // 选择
            auto parent1 = selection(population);
            auto parent2 = selection(population);

            // 交叉
            auto child = crossover(parent1, parent2);

            // 变异
            mutation(child);

            new_population.push_back(child);
        }

        population = new_population;

        // 输出最好的个体的适应度
        std::cout << "Generation " << generation << ": " << fitness(selection(population)) << std::endl;
    }

    return 0;
}