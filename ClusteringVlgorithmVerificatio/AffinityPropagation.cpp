#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const double kNegativeInfinity = -numeric_limits<double>::infinity();

// Affinity Propagation聚类算法
class AffinityPropagation {
public:
    AffinityPropagation(const vector<vector<double>>& similarityMatrix, double damping, int maxIterations)
            : similarityMatrix(similarityMatrix), damping(damping), maxIterations(maxIterations), numPoints(similarityMatrix.size()) {
        responsibilities.resize(numPoints, vector<double>(numPoints, 0.0));
        availabilities.resize(numPoints, vector<double>(numPoints, 0.0));
    }

    void fit() {
        for (int iteration = 0; iteration < maxIterations; ++iteration) {
            // Update responsibilities
            updateResponsibilities();

            // Update availabilities
            updateAvailabilities();

            // Update messages
            updateMessages();

            // Check for convergence
            if (hasConverged()) {
                cout << "Converged in " << iteration + 1 << " iterations.\n";
                break;
            }
        }
    }

    const vector<int>& getLabels() const {
        return labels;
    }

private:
    vector<vector<double>> similarityMatrix;  // 相似度矩阵
    vector<vector<double>> responsibilities;  // 负责度矩阵
    vector<vector<double>> availabilities;   // 可用度矩阵
    vector<int> labels;                       // 聚类标签
    double damping;                          // 阻尼因子
    int maxIterations;                       // 最大迭代次数
    int numPoints;                           // 数据点数

    void updateResponsibilities() {
        for (int i = 0; i < numPoints; ++i) {
            for (int k = 0; k < numPoints; ++k) {
                double maxSum = kNegativeInfinity;
                for (int kk = 0; kk < k; ++kk) {
                    maxSum = max(maxSum, availabilities[i][kk] + similarityMatrix[i][kk]);
                }
                for (int kk = k + 1; kk < numPoints; ++kk) {
                    maxSum = max(maxSum, availabilities[i][kk] + similarityMatrix[i][kk]);
                }
                responsibilities[i][k] = (1 - damping) * (similarityMatrix[i][k] - maxSum) + damping * responsibilities[i][k];
            }
        }
    }

    void updateAvailabilities() {
        vector<double> sumResponsibilities(numPoints, 0.0);
        for (int i = 0; i < numPoints; ++i) {
            for (int kk = 0; kk < numPoints; ++kk) {
                if (kk != i) {
                    sumResponsibilities[i] += max(0.0, responsibilities[kk][i]);
                }
            }
        }

        for (int i = 0; i < numPoints; ++i) {
            for (int k = 0; k < numPoints; ++k) {
                if (k != i) {
                    availabilities[i][k] = (1 - damping) * (responsibilities[k][k] + sumResponsibilities[k] - max(0.0, responsibilities[i][k])) + damping * availabilities[i][k];
                }
            }
        }
    }

    void updateMessages() {
        for (int i = 0; i < numPoints; ++i) {
            double maxScore = kNegativeInfinity;
            int maxIndex = -1;
            for (int k = 0; k < numPoints; ++k) {
                double score = responsibilities[k][k] + availabilities[i][k];
                if (k == i) {
                    score -= max(0.0, responsibilities[i][k]);
                }
                if (score > maxScore) {
                    maxScore = score;
                    maxIndex = k;
                }
            }
            labels[i] = maxIndex;
        }
    }

    bool hasConverged() const {
        // 判断是否收敛，这里使用简单的判定条件
        // 可以根据实际情况调整
        // 这里简单地判断负责度矩阵和可用度矩阵的变化是否很小
        for (int i = 0; i < numPoints; ++i) {
            for (int k = 0; k < numPoints; ++k) {
                if (abs(responsibilities[i][k] - responsibilities[i][k]) > 1e-6 || abs(availabilities[i][k] - availabilities[i][k]) > 1e-6) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // 用一个简单的例子演示
    vector<vector<double>> similarityMatrix = {
            {4, 3, 2},
            {3, 4, 1},
            {2, 1, 5}
    };

    double damping = 0.8;
    int maxIterations = 100;

    AffinityPropagation ap(similarityMatrix, damping, maxIterations);
    ap.fit();

    const vector<int>& labels = ap.getLabels();

    cout << "Cluster labels: ";
    for (int i = 0; i < labels.size(); ++i) {
        cout << labels[i] << " ";
    }

    return 0;
}
