#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    vector<double> getRoots() const {
        vector<double> roots;

        double discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            roots.push_back((-b + std::sqrt(discriminant)) / (2 * a));
            roots.push_back((-b - std::sqrt(discriminant)) / (2 * a));
        }

        return roots;
    }
};

class Student {


public:
    string name;
    int id;
    int score;
    Student(string name, int id) : name(name), id(id), score(0) {}

    virtual vector<double> getAnswer(const QuadraticEquation& task) const = 0;

    int getScore() const {
        return score;
    }

    void addScore(int points) {
        score += points;
    }
};

class ExcellentStudent : public Student {
public:
    ExcellentStudent(string name, int id) : Student(name, id) {}

    std::vector<double> getAnswer(const QuadraticEquation& task) const override {
        return task.getRoots();
    }
};

class AverageStudent : public Student {
public:
    AverageStudent(string name, int id) : Student(name, id) {}

    vector<double> getAnswer(const QuadraticEquation& task) const override {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 1);
        if (dis(gen) == 0) {
            return task.getRoots();
        }
        else {
            return vector<double>();
        }
    }
};

class PoorStudent : public Student {
public:
    PoorStudent(string name, int id) : Student(name, id) {}

    vector<double> getAnswer(const QuadraticEquation& task) const override {
        return vector<double>();
    }
};

class Teacher {
private:
    vector<Student*> students;

    vector<QuadraticEquation> generateTasks(int count) const {
        vector<QuadraticEquation> tasks;

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-10, 10);

        for (int i = 0; i < count; i++) {
            double a = dis(gen);
            double b = dis(gen);
            double c = dis(gen);
            tasks.emplace_back(a, b, c);
        }

        return tasks;
    }

public:
    void addStudent(Student* student) {
        students.push_back(student);
    }


    void checkAnswers() {
        vector<QuadraticEquation> tasks = generateTasks(4);

        for (auto student : students) {
            int score = 0;
            for (auto task : tasks) {
                vector<double> expected = task.getRoots();
                vector<double> actual = student->getAnswer(task);

                bool isCorrect = actual == expected;

                if (isCorrect) {
                    score += 2; 
                }
            }

            student->addScore(score); 

            cout << "Student " << student->id << " (" << student->name << "): " << student->getScore() << " points\n";
        }
    }
};

int main() {
    Teacher teacher;
 
    Student* student1 = new ExcellentStudent("Alice", 1);
    Student* student2 = new AverageStudent("Bob", 2);
    Student* student3 = new PoorStudent("Charlie", 3);
    Student* student4 = new AverageStudent("Gleb", 4);

 
    teacher.addStudent(student1);
    teacher.addStudent(student2);
    teacher.addStudent(student3);
    teacher.addStudent(student4);

    teacher.checkAnswers();

  
    delete student1;
    delete student2;
    delete student3;
    delete student4;

    return 0;
}