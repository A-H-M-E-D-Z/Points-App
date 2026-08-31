#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// ============================================================
// STUDENT
// ============================================================

struct Student {
    int id;
    string name;
    int points = 0;
};

// ============================================================
// TEACHER
// ============================================================

struct Teacher {
    string name;
};

// ============================================================
// MEDAL SYSTEM
// ============================================================

string getMedal(int points) {

    if (points >= 150)
        return "gold";

    if (points >= 50)
        return "silver";

    return "none";
}

// ============================================================
// STORAGE
// ============================================================

class StorageService {

private:

    const string fileName = "app_data.txt";

public:

    void save(
        const Teacher& teacher,
        const vector<Student>& students
    ) {

        ofstream file(fileName);

        if (!file.is_open()) {
            cout << "Error: Could not save data.\n";
            return;
        }

        // Teacher
        file << "TEACHER\n";
        file << teacher.name << "\n";

        // Students
        file << "STUDENTS\n";

        for (const auto& student : students) {

            file
                << student.id << "|"
                << student.name << "|"
                << student.points
                << "\n";
        }

        file.close();
    }

    bool load(
        Teacher& teacher,
        vector<Student>& students
    ) {

        ifstream file(fileName);

        if (!file.is_open())
            return false;

        string line;

        // TEACHER
        getline(file, line);

        if (line != "TEACHER")
            return false;

        getline(file, teacher.name);

        // STUDENTS
        getline(file, line);

        if (line != "STUDENTS")
            return false;

        students.clear();

        while (getline(file, line)) {

            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string name;
            string points;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, points, '|');

            Student student;

            student.id = stoi(id);
            student.name = name;
            student.points = stoi(points);

            students.push_back(student);
        }

        file.close();

        return true;
    }
};

// ============================================================
// STUDENT MANAGER
// ============================================================

class StudentManager {

private:

    vector<Student> students;

    int nextId = 1;

    StorageService storage;

    Teacher teacher;

public:

    // ========================================================
    // LOGIN / TEACHER
    // ========================================================

    bool loadData() {

        return storage.load(
            teacher,
            students
        );
    }

    void setTeacherName(const string& name) {

        teacher.name = name;

        saveData();
    }

    string getTeacherName() const {

        return teacher.name;
    }

    bool hasTeacher() const {

        return !teacher.name.empty();
    }

    // ========================================================
    // STORAGE
    // ========================================================

    void saveData() {

        storage.save(
            teacher,
            students
        );
    }

    // ========================================================
    // ADD STUDENT
    // ========================================================

    Student addStudent(const string& name) {

        Student student;

        student.id = nextId++;
        student.name = name;
        student.points = 0;

        students.push_back(student);

        saveData();

        return student;
    }

    // ========================================================
    // DELETE STUDENT
    // ========================================================

    bool deleteStudent(int id) {

        auto it = find_if(
            students.begin(),
            students.end(),

            [id](const Student& student) {
                return student.id == id;
            }
        );

        if (it == students.end())
            return false;

        students.erase(it);

        saveData();

        return true;
    }

    // ========================================================
    // GET STUDENT
    // ========================================================

    Student* getStudent(int id) {

        for (auto& student : students) {

            if (student.id == id)
                return &student;
        }

        return nullptr;
    }

    // ========================================================
    // ATTENDANCE
    // ========================================================

    bool recordAttendance(int id) {

        Student* student = getStudent(id);

        if (!student)
            return false;

        // حضور +10
        student->points += 10;

        saveData();

        return true;
    }

    // ========================================================
    // INTERACTION
    // ========================================================

    bool addInteraction(int id) {

        Student* student = getStudent(id);

        if (!student)
            return false;

        // تفاعل +5
        student->points += 5;

        saveData();

        return true;
    }

    // ========================================================
    // LATE
    // ========================================================

    bool recordLate(int id) {

        Student* student = getStudent(id);

        if (!student)
            return false;

        // تأخير -5
        student->points -= 5;

        if (student->points < 0)
            student->points = 0;

        saveData();

        return true;
    }

    // ========================================================
    // ABSENCE
    // ========================================================

    bool recordAbsence(int id) {

        Student* student = getStudent(id);

        if (!student)
            return false;

        // غياب -10
        student->points -= 10;

        if (student->points < 0)
            student->points = 0;

        saveData();

        return true;
    }

    // ========================================================
    // MANUAL POINTS
    // ========================================================

    bool changePoints(
        int id,
        int amount
    ) {

        Student* student = getStudent(id);

        if (!student)
            return false;

        student->points += amount;

        if (student->points < 0)
            student->points = 0;

        saveData();

        return true;
    }

    // ========================================================
    // GET ALL STUDENTS
    // ========================================================

    vector<Student> getStudents() const {

        return students;
    }

    // ========================================================
    // SEARCH
    // ========================================================

    vector<Student> searchStudents(
        const string& query
    ) const {

        vector<Student> result;

        for (const auto& student : students) {

            if (
                student.name.find(query)
                != string::npos
            ) {

                result.push_back(student);
            }
        }

        return result;
    }

    // ========================================================
    // SORT
    // ========================================================

    vector<Student> getSortedStudents() const {

        vector<Student> sorted = students;

        sort(
            sorted.begin(),
            sorted.end(),

            [](const Student& a, const Student& b) {

                return a.points > b.points;
            }
        );

        return sorted;
    }

    // ========================================================
    // STATISTICS
    // ========================================================

    int getStudentCount() const {

        return static_cast<int>(
            students.size()
        );
    }

    int getTotalPoints() const {

        int total = 0;

        for (const auto& student : students)
            total += student.points;

        return total;
    }

    int getGoldCount() const {

        int count = 0;

        for (const auto& student : students) {

            if (
                getMedal(student.points)
                == "gold"
            ) {

                count++;
            }
        }

        return count;
    }

    int getSilverCount() const {

        int count = 0;

        for (const auto& student : students) {

            if (
                getMedal(student.points)
                == "silver"
            ) {

                count++;
            }
        }

        return count;
    }

    // ========================================================
    // RESET ALL DATA
    // ========================================================

    void resetData() {

        teacher.name = "";

        students.clear();

        nextId = 1;

        saveData();
    }
};

// ============================================================
// MAIN - TEST
// ============================================================

int main() {

    StudentManager manager;

    // محاولة تحميل البيانات القديمة
    manager.loadData();

    // ========================================================
    // TEACHER LOGIN
    // ========================================================

    if (!manager.hasTeacher()) {

        string teacherName;

        cout << "====================================\n";
        cout << "       TEACHER ADMIN SYSTEM\n";
        cout << "====================================\n\n";

        cout << "Enter teacher name: ";

        getline(cin, teacherName);

        if (teacherName.empty()) {

            cout << "Teacher name cannot be empty.\n";

            return 0;
        }

        manager.setTeacherName(teacherName);
    }

    // ========================================================
    // TEST DATA
    // ========================================================

    if (manager.getStudentCount() == 0) {

        manager.addStudent("Ahmed");
        manager.addStudent("Mohamed");
        manager.addStudent("Omar");
    }

    // Ahmed
    manager.recordAttendance(1);
    manager.addInteraction(1);

    // Mohamed
    manager.recordAttendance(2);

    // Omar
    manager.recordAbsence(3);
    manager.recordLate(3);

    // Ahmed manual bonus
    manager.changePoints(1, 100);

    // ========================================================
    // DASHBOARD
    // ========================================================

    cout << "\n====================================\n";
    cout << "          TEACHER DASHBOARD\n";
    cout << "====================================\n";

    cout << "Teacher: "
         << manager.getTeacherName()
         << "\n\n";

    cout << "Students: "
         << manager.getStudentCount()
         << "\n";

    cout << "Total Points: "
         << manager.getTotalPoints()
         << "\n";

    cout << "Gold Medals: "
         << manager.getGoldCount()
         << "\n";

    cout << "Silver Medals: "
         << manager.getSilverCount()
         << "\n\n";

    // ========================================================
    // STUDENT RANKING
    // ========================================================

    cout << "====================================\n";
    cout << "          STUDENT RANKING\n";
    cout << "====================================\n";

    auto sortedStudents =
        manager.getSortedStudents();

    int rank = 1;

    for (const auto& student : sortedStudents) {

        cout
            << rank++
            << ". "
            << student.name
            << " | Points: "
            << student.points
            << " | Medal: "
            << getMedal(student.points)
            << "\n";
    }

    cout << "\nData saved locally.\n";

    return 0;
}
