#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Function to partition the elements based on a pivot
void partition(vector<int>& arr, int pivot, std::vector<int>& S1, vector<int>& S2, vector<int>& S3) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < pivot) 
        S1.push_back(arr[i]);
    else if (arr[i] == pivot) 
        S2.push_back(arr[i]);
    else 
        S3.push_back(arr[i]);
  }
}

int selectSmall(vector<int>& arr, int k) {
    sort(arr.begin(), arr.end());
    return arr[k-1];
}

int selectKthSmallest_01(vector<int>& arr, int k) {
    if (arr.size() == 1) return arr[0];

    int pivot = arr[rand() % arr.size()];

    vector<int> S1, S2, S3;

    partition(arr, pivot, S1, S2, S3);

    if (S1.size() >= k) 
        return selectKthSmallest_01(S1, k);
    else if (S1.size()+S2.size() >= k) 
        return pivot;
    else 
        return selectKthSmallest_01(S3, k-S1.size()-S2.size());
    
}

int selectKthSmallest_02(vector<int>& arr, int k);

int medianOfMedians(vector<int>& arr) {
    int n = arr.size();
    if (n < 50) return selectSmall(arr, (n+1)/2);
    
    // Divide arr into groups of 5 elements and find medians
    vector<int> medians;
    for (int i = 0; i < n; i += 5) {
        int groupSize = (5 >= (n-i)) ? (n-i) : 5;

        vector<int> group(arr.begin() + i, arr.begin() + i + groupSize);
        
        int median = selectSmall(group, (groupSize + 1) / 2);
        
        medians.push_back(median);
    }

    // Recursively find the median of the medians
    return selectKthSmallest_02(medians, (medians.size() + 1) / 2);
}

int selectKthSmallest_02(vector<int>& arr, int k) {
    if (arr.size() < 50) return selectSmall(arr, k);
    
    int m = medianOfMedians(arr);

    vector<int> S1, S2, S3;
    partition(arr, m, S1, S2, S3);

    if (S1.size() >= k) 
        return selectKthSmallest_02(S1, k);
    else if (S1.size()+S2.size() >= k)
        return m;
    else
        return selectKthSmallest_02(S3, k-S1.size()-S2.size());
}


int main() {
    random_device rd_1;
    mt19937 gen_1(rd_1());
    
    random_device rd_2;
    mt19937 gen_2(rd_2());
    
    uniform_int_distribution<> distrib_1(-100, 100);
    uniform_int_distribution<> distrib_2(0,99);
    
    vector<int> positives(100);
    vector<int> negatives(100);

    for (int i = 0; i < positives.size(); ++i) {
        positives[i] = distrib_1(gen_1);
        negatives[i] = distrib_1(gen_2);
    }

    int k1 = distrib_2(gen_1);
    int k2 = distrib_2(gen_2);

    int resPositive, resNegative;
    chrono::time_point start = chrono::high_resolution_clock::now();
    chrono::time_point end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed;

    start = chrono::high_resolution_clock::now();
    resPositive = selectKthSmallest_01(positives, k1);
    resNegative = selectKthSmallest_01(negatives, k2);
    end = chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "\nTime taken (Algorithm #1): " << elapsed.count() * 1000 << " miliseconds" << std::endl;
    std::cout << "Positive: " << resPositive << " (" << k1 << ")" << std::endl;
    std::cout << "Negative: " << resNegative << " (" << k2 << ")" << std::endl;
    
    start = chrono::high_resolution_clock::now();
    resPositive = selectKthSmallest_02(positives, k1);
    resNegative = selectKthSmallest_02(negatives, k2);
    end = chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "\nTime taken (Algorithm #2): " << elapsed.count() * 1000 << " miliseconds" << std::endl;
    std::cout << "Positive: " << resPositive << " (" << k1 << ")" << std::endl;
    std::cout << "Negative: " << resNegative << " (" << k2 << ")" << std::endl;
}

