#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid input. Number of students must be at least 1." << endl;
        return 1;
    }

    vector<Student> students;

    for (int i = 0; i < n; i++)
    {
        Student s;
        cout << "Enter name and mark of student " << i + 1 << ": ";
        cin >> s.name >> s.mark;

        if (cin.fail() || s.mark < 0 || s.mark > 100)
        {
            cout << "Invalid input. Mark must be between 0 and 100." << endl;
            return 1;
        }

        s.grade = ' ';
        students.push_back(s);
    }

    // Sort students based on marks (highest first)
    sort(students.begin(), students.end(),
         [](Student a, Student b)
         {
             return a.mark > b.mark;
         });

    // Assign grades using transform
    transform(students.begin(), students.end(),
              students.begin(),
              [](Student s)
              {
                  if (s.mark >= 90)
                      s.grade = 'A';
                  else if (s.mark >= 75)
                      s.grade = 'B';
                  else if (s.mark >= 50)
                      s.grade = 'C';
                  else
                      s.grade = 'F';

                  return s;
              });

    // Find first student scoring above 80
    auto it = find_if(students.begin(), students.end(),
                      [](Student s)
                      {
                          return s.mark > 80;
                      });

    // Calculate total marks using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, Student s)
                           {
                               return sum + s.mark;
                           });

    float average = (float)total / students.size();

    // Display results
    cout << "\nStudent Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";

    for (Student s : students)
    {
        cout << s.name << "\t"
             << s.mark << "\t"
             << s.grade << endl;
    }

    if (it != students.end())
    {
        cout << "\nFirst student scoring above 80: "
             << it->name << endl;
    }
    else
    {
        cout << "\nNo student scored above 80." << endl;
    }

    cout << "Total Marks: " << total << endl;
    cout << "Average Mark: " << average << endl;

    return 0;
}