#include <iostream>
#include <random>
#include <limits> // ��� ��������� ������������ �������� int
#include <unordered_map> // ��� �������� ������� ��������� �������
#include "../LibraryCPP/array.h" // ���������� ������������ ���� � ������������ ��������� Array � ������� ��� ������ � �������

using namespace std;

// ������� ��� ���������� ������� ���������� ������� � �������� ���������
void fillRandom(Array* arr, int minVal, int maxVal) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr, i, distrib(gen));
    }
}
// ������� ��� ���������� ������������� �������� ����� ��������� � ������� ���������
// ��������� ��������� �� ������ (Array* arr), ����������� �������� (int minVal) � ������������ �������� (int maxVal)
Data findMaxEvenIndex(const Array* arr) {
    size_t size = array_size(arr);

    std::cerr << "findMaxEvenIndex: size = " << size << std::endl; // ���������

    if (size == 0) {
        std::cerr << "findMaxEvenIndex: Array is empty, returning min!!!!!" << std::endl;
        return numeric_limits<Data>::min();
    }

    //if (!size % 2 > 0)size -= 1;

    // �������������� ������������ �������� ����������� ��������� ��������� ���� Data
    Data maxVal = numeric_limits<Data>::min();

    // �������� �� ��������� ������� � ������� ���������
    for (size_t i = 0; i < size; i += 2) {
        Data val = array_get(arr, i);
        if (val > maxVal) {
            maxVal = val;
        }
    }

    return maxVal;
}
// ������� ��� ����������� �������� ����� �������������� ����� � �������
// ��������� ��������� �� ������ (const Array* arr)
Data findMostFrequent(const Array* arr) {
    size_t size = array_size(arr);

    // ������� unordered_map ��� �������� ������� ������� ��������
    // ���� - ������� ������� (Data), �������� - ���������� ��������� ����� ��������
    unordered_map<Data, int> counts;

    // �������� �� ���� ��������� �������
    for (size_t i = 0; i < size; ++i) {
        counts[array_get(arr, i)]++;
    }

    // �������������� �������� ����� ������������� ������� ������ ��������� �������
    Data mostFrequent = array_get(arr, 0);

    // �������������� ������������ ���������� ��������� �����
    int maxCount = 0;

    // �������� �� ���� ����� (�������, ���������� ���������) � unordered_map
    for (const auto& pair : counts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }

    return mostFrequent;
}

int main() {

    // 1. ����� ������������� �������� ����� ��������� � ������� ���������

    size_t size1;
    //cout << "������� ������ ������� �������: ";
    cin >> size1;

    Array* arr1 = array_create(size1);

    fillRandom(arr1, 1, 100); // ��������� ���������� ������� �� 1 �� 100

    /*cout << "������ 1: ";
    for (size_t i = 0; i < array_size(arr1); ++i) {
        cout << array_get(arr1, i) << " ";
    }
    cout << endl;*/

    Data maxEven = findMaxEvenIndex(arr1);
    //cout << "������������ ������� � ������ ��������: " << maxEven << endl;
    cout << maxEven << endl;

    // ����������� ������
    array_delete(arr1);


    // 2. ����������� �������� ����� �������������� �����


    size_t size2;
    //cout << "������� ������ ������� �������: ";
    cin >> size2;

    Array* arr2 = array_create(size2);

    fillRandom(arr2, 1, 10); // ��������� ���������� ������� �� 1 �� 10

    ///*cout << "������ 2: ";
    //for (size_t i = 0; i < array_size(arr2); ++i) {
    //    cout << array_get(arr2, i) << " ";
    //}
    //cout << endl;*/

    Data mostFrequent = findMostFrequent(arr2);
    //cout << "�������� ����� ������������� ��������: " << mostFrequent << endl;
    cout << mostFrequent << endl;

    // ����������� ������
    array_delete(arr2);

    return 0;
}