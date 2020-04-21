#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных методов для решения задачи.
//Рекомендуется использовать имеющиеся классы Student и Ski для решения задачи.

void sort(Student* students, Ski* skies, int left, int right)
{
    Student stud_pivot = students[(left + right) / 2];
    int ski_i = left, ski_j = right, stud_i = left, stud_j = right;
    int ski_index = ski_i;

    for (int t = left; t <= right; t++)
    {
        if (compare(stud_pivot, skies[t]) == 0)
            ski_index = t;
    }

    Ski ski_pivot = skies[ski_index];
    swap(skies[ski_index], skies[(left + right) / 2]);

    while (stud_i <= stud_j)
    {
        while (compare(students[stud_i], ski_pivot) > 0)
            stud_i++;
        while (compare(students[stud_j], ski_pivot) < 0)
            stud_j--;
        if (stud_i <= stud_j)
        {
            swap(students[stud_i], students[stud_j]);
            stud_i++;
            stud_j--;
        }
    }

    while (ski_i <= ski_j)
    {
        while (compare(stud_pivot, skies[ski_i]) < 0)
            ski_i++;
        while (compare(stud_pivot, skies[ski_j]) > 0)
            ski_j--;
        if (ski_i <= ski_j)
        {
            swap(skies[ski_i], skies[ski_j]);
            ski_i++;
            ski_j--;
        }
    }

    if (stud_j > left)
        sort(students, skies, left, stud_j);
    if (stud_i < right)
        sort(students, skies, stud_i, right);
}

void sortId(Student* students, Ski* skies, int left, int right)
{
    int i = left, j = right;
    int pivot = students[(i + j) / 2].id;

    while (i <= j)
    {
        while (students[i].id < pivot)
            i++;
        while (students[j].id > pivot)
            j--;
        if (i <= j)
        {
            swap(students[i], students[j]);
            swap(skies[i], skies[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        sortId(students, skies, left, j);
    if (i < right)
        sortId(students, skies, i, right);
}
//Задача - реализовать этот метод.
//Ответ должен быть упорядочен по возрастанию номеров студентов(!), то есть их id.
//Ответы должны быть в этих же массивах.
void findPairs(Student* students, Ski* skis, int n)
{
    sort(students, skis, 0, n - 1);
    sortId(students, skis, 0, n - 1);
}

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
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
