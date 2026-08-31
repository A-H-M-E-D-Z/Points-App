
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int points = 0;
};

// دالة لمساعدة الترتيب حسب النقاط من الأعلى للأقل
bool compareStudents(const Student& a, const Student& b) {
    return a.points > b.points;
}

int main() {
    int studentCount;
    cout << "أدخل عدد الطلاب: ";
    cin >> studentCount;

    vector<Student> students(studentCount);

    // إدخال أسماء الطلاب
    for (int i = 0; i < studentCount; ++i) {
        cout << "أدخل اسم الطالب رقم " << (i + 1) << ": ";
        cin >> students[i].name;
    }

    int sessions = 12; // عدد الحصص في الشهر
    for (int s = 1; s <= sessions; ++s) {
        cout << "\n--- تسجل الحصة رقم " << s << " ---\n";
        for (int i = 0; i < studentCount; ++i) {
            int status;
            cout << "الطالب (" << students[i].name << ") - أدخل (1 للحضور، 0 للغياب): ";
            cin >> status;

            if (status == 1) {
                int interaction;
                cout << "أدخل نقاط التفاعل للطالب (من 0 إلى 5): ";
                cin >> interaction;
                
                // 5 نقاط حضور + نقاط التفاعل
                students[i].points += (5 + interaction);
            } else {
                // خصم 15 نقطة للغياب
                students[i].points -= 15;
            }
        }
    }

    // ترتيب الطلاب حسب النقاط
    sort(students.begin(), students.end(), compareStudents);

    // عرض النتيجة النهائية
    cout << "\n================ ترتيب الطلاب النهائي ================\n";
    for (int i = 0; i < studentCount; ++i) {
        cout << (i + 1) << ". " << students[i].name << " - النقاط: " << students[i].points << "\n";
    }

    return 0;
}
