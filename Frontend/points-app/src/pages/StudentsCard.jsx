import { useState } from "react";

function StudentsCard({ students, setStudents, showForm, setShowForm }) {
  const [studentName, setStudentName] = useState("");
  const [grade, setGrade] = useState("");
  const [group, setGroup] = useState("");
  const [gender, setGender] = useState("");

  const addStudent = (e) => {
    e.preventDefault();

    const newStudent = {
      id: Date.now(),
      name: studentName,
      grade: grade,
      group: group,
      gender: gender,
      points: 0,
    };

    const updatedStudents = [...students, newStudent];

    setStudents(updatedStudents);

    setStudentName("");
    setGrade("");
    setGroup("");
    setGender("");
    setShowForm(false);
  };

  return (
    <>
      <div className="add-st-form">
        {showForm && (
          <form onSubmit={addStudent}>
            <label>
              اسم الطالب :
              <input
                type="text"
                placeholder="اسم الطالب..."
                maxLength={60}
                value={studentName}
                onChange={(e) => setStudentName(e.target.value)}
                required
              />
            </label>

            <br />

            <label>
              الصف الدراسي:
              <select value={grade} onChange={(e) => setGrade(e.target.value)}>
                <option value="">اختر الصف</option>
                <option value="الصف الثاني (بكالوريا)">
                  الصف الثاني (بكالوريا)
                </option>
                <option value="الصف الثاني (ثانوي عام)">
                  الصف الثاني (ثانوي عام)
                </option>
                <option value="الصف الاول الثانوي">الصف الاول الثانوي</option>
              </select>
            </label>

            <br />

            <label>
              المجموعة :
              <input
                type="text"
                placeholder="المجموعة..."
                maxLength={60}
                value={group}
                onChange={(e) => setGroup(e.target.value)}
                required
              />
            </label>

            <br />

            <label>
              <input
                type="radio"
                name="gender"
                value="طالب"
                checked={gender === "طالب"}
                onChange={(e) => setGender(e.target.value)}
              />
              طالب
              <input
                type="radio"
                name="gender"
                value="طالبة"
                checked={gender === "طالبة"}
                onChange={(e) => setGender(e.target.value)}
              />
              طالبة
            </label>

            <button className="save" type="submit">
              حفظ
            </button>

            <button
              className="delete"
              type="button"
              onClick={() => setShowForm(false)}
            >
              الغاء ×
            </button>
          </form>
        )}
      </div>
    </>
  );
}

export default StudentsCard;
