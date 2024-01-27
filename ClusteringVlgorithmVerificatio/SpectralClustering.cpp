#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 计算高斯核函数
double gaussianKernel(double x, double sigma) {
    return exp(-0.5 * (x * x) / (sigma * sigma));
}

// 构建相似度矩阵
void buildSimilarityMatrix(const vector<vector<double>>& data, vector<vector<double>>& similarityMatrix, double sigma) {
    int n = data.size();
    similarityMatrix.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double distance = 0.0;
            // 计算样本之间的欧氏距离
            for (int k = 0; k < data[i].size(); ++k) {
                distance += (data[i][k] - data[j][k]) * (data[i][k] - data[j][k]);
            }
            similarityMatrix[i][j] = gaussianKernel(sqrt(distance), sigma);
        }
    }
}

// 计算度矩阵
void computeDegreeMatrix(const vector<vector<double>>& similarityMatrix, vector<double>& degreeMatrix) {
    int n = similarityMatrix.size();
    degreeMatrix.resize(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            degreeMatrix[i] += similarityMatrix[i][j];
        }
    }
}

// 构建拉普拉斯矩阵
void buildLaplacianMatrix(const vector<vector<double>>& similarityMatrix, const vector<double>& degreeMatrix, vector<vector<double>>& laplacianMatrix) {
    int n = similarityMatrix.size();
    laplacianMatrix.resize(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            laplacianMatrix[i][j] = degreeMatrix[i] * similarityMatrix[i][j] - similarityMatrix[i][j];
        }
    }
}

// 计算特征值和特征向量
void computeEigen(const vector<vector<double>>& laplacianMatrix, vector<double>& eigenValues, vector<vector<double>>& eigenVectors) {
    // 这里省略了特征值分解的具体实现，可以使用常用的数学库如Eigen或直接调用系统库
    // 这是实现的核心部分，可以根据实际情况选择合适的库
    // 以下是一种简化的假设，仅用于演示，实际应用中应使用更稳健的方法
}

// K均值聚类
void kMeansClustering(const vector<vector<double>>& eigenVectors, int k, vector<int>& labels) {
    int n = eigenVectors.size();
    int m = eigenVectors[0].size();

    // 初始化聚类中心
    vector<vector<double>> centroids(k, vector<double>(m, 0.0));
    for (int i = 0; i < k; ++i) {
        centroids[i] = eigenVectors[i];
    }

    // 迭代次数，可以根据实际情况调整
    const int maxIterations = 100;

    // 进行K均值聚类
    for (int iter = 0; iter < maxIterations; ++iter) {
        // 分配样本到最近的聚类中心
        vector<int> newLabels(n, 0);
        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            for (int j = 0; j < k; ++j) {
                double dist = 0.0;
                for (int l = 0; l < m; ++l) {
                    dist += pow(eigenVectors[i][l] - centroids[j][l], 2);
                }
                if (dist < minDist) {
                    minDist = dist;
                    newLabels[i] = j;
                }
            }
        }

        // 更新聚类中心
        vector<vector<double>> newCentroids(k, vector<double>(m, 0.0));
        vector<int> count(k, 0);

        for (int i = 0; i < n; ++i) {
            int cluster = newLabels[i];
            for (int j = 0; j < m; ++j) {
                newCentroids[cluster][j] += eigenVectors[i][j];
            }
            count[cluster]++;
        }

        for (int i = 0; i < k; ++i) {
            if (count[i] > 0) {
                for (int j = 0; j < m; ++j) {
                    newCentroids[i][j] /= count[i];
                }
            }
        }

        // 判断是否收敛
        if (newLabels == labels) {
            break;
        }

        labels = newLabels;
        centroids = newCentroids;
    }
}

// 标准化数据
void standardizeData(vector<vector<double>>& data) {
    int n = data.size();
    int m = data[0].size();

    // 计算每个特征的均值和标准差
    vector<double> mean(m, 0.0);
    vector<double> stdDev(m, 0.0);

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            mean[j] += data[i][j];
        }
        mean[j] /= n;

        for (int i = 0; i < n; ++i) {
            stdDev[j] += pow(data[i][j] - mean[j], 2);
        }
        stdDev[j] = sqrt(stdDev[j] / n);
    }

    // 标准化数据
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            data[i][j] = (data[i][j] - mean[j]) / stdDev[j];
        }
    }
}


int main() {
    // 示例数据，假设有3个样本，每个样本有2个特征
    vector<vector<double>> data = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}};
    int k = 2;  // 聚类簇的个数
    double sigma = 1.0;  // 高斯核函数的参数

    // 标准化数据
    standardizeData(data);
    // 构建相似度矩阵
    vector<vector<double>> similarityMatrix;
    buildSimilarityMatrix(data, similarityMatrix, sigma);

    // 计算度矩阵
    vector<double> degreeMatrix;
    computeDegreeMatrix(similarityMatrix, degreeMatrix);

    // 构建拉普拉斯矩阵
    vector<vector<double>> laplacianMatrix;
    buildLaplacianMatrix(similarityMatrix, degreeMatrix, laplacianMatrix);

    // 计算特征值和特征向量
    vector<double> eigenValues;
    vector<vector<double>> eigenVectors;
    computeEigen(laplacianMatrix, eigenValues, eigenVectors);

    // K均值聚类
    vector<int> labels;
    kMeansClustering(eigenVectors, k, labels);

    // 输出聚类结果
    cout << "Cluster Labels:" << endl;
    for (int i = 0; i < data.size(); ++i) {
        cout << "Sample " << i << ": Cluster " << labels[i] << endl;
    }

    return 0;
}
