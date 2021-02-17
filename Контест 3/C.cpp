#include <vector>
#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

void quickSort(vector<pair<Student, Ski>> &arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[(high + low) / 2].first.id;

    while (i <= j)
    {
        while (i <= j && arr[i].first.id < pivot)
            i++;
        while (i <= j && arr[j].first.id > pivot)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };

    if (low < j)
        quickSort(arr, low, j);
    if (i < high)
        quickSort(arr, i, high);
}

void divide_and_sort(vector<Student> &students, vector<Ski> &skies, vector<pair<Student, Ski>> &result)
{
    vector<Ski> smallSkies;
    vector<Ski> bigSkies;
    Student student = students[students.size() / 2];
    Ski ski;

    for (int i = 0; i < students.size(); ++i)
    {
        if (compare(student, skies[i]) > 0)
        {
            bigSkies.push_back(skies[i]);
        } else if (compare(student, skies[i]) < 0)
        {
            smallSkies.push_back(skies[i]);
        } else
        {
            ski = skies[i];
        }
    }

    smallSkies.shrink_to_fit();
    bigSkies.shrink_to_fit();
    vector<Student> smallStudents;
    vector<Student> bigStudents;

    for (auto s : students)
    {
        if (compare(s, ski) > 0)
        {
            smallStudents.push_back(s);
        } else if (compare(s, ski) < 0)
        {
            bigStudents.push_back(s);
        }
    }

    smallStudents.shrink_to_fit();
    bigStudents.shrink_to_fit();
    vector<Student>().swap(students);
    vector<Ski>().swap(skies);

    result.emplace_back(make_pair(student, ski));

    if (smallStudents.size() > 1)
    {
        divide_and_sort(smallStudents, smallSkies, result);
    } else if (smallStudents.size() == 1)
    {
        result.emplace_back(make_pair(smallStudents[0], smallSkies[0]));
    }

    if (bigStudents.size() > 1)
        divide_and_sort(bigStudents, bigSkies, result);
    if (bigStudents.size() == 1)
        result.emplace_back(make_pair(bigStudents[0], bigSkies[0]));
}

void findPairs(Student *&students, Ski *&skis, int n)
{
    vector<pair<Student, Ski>> result;
    vector<Student> students2;
    vector<Ski> skies;

    for (int i = 0; i < n; ++i)
    {
        students2.push_back(students[i]);
        skies.push_back(skis[i]);
    }

    delete[] students;
    delete[] skis;

    divide_and_sort(students2, skies, result);
    quickSort(result, 0, n - 1);

    students = new Student[n];
    skis = new Ski[n];

    for (int i = 0; i < n; ++i)
    {
        students[i] = result[i].first;
        skis[i] = result[i].second;
    }
}

int main()
{
    ReadWriter rw;

    Student *students = nullptr;
    Ski *skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}
