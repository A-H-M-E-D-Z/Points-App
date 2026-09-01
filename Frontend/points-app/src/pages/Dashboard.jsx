import { useEffect, useState } from "react";
import StudentsCard from "./StudentsCard";
import { useNavigate } from "react-router-dom";
function Dashboard() {
  const navigate = useNavigate();
  const today = new Date();
  const dayNumber = today.getDate();
  const dayName = today.toLocaleDateString("ar-EG", { weekday: "long" });
  const monthArabic = today.toLocaleDateString("ar-EG", { month: "long" });
  const trophy = `\uD83C\uDFC5 نيشان`;
  const goldMedal = `\uD83E\uDD47 ذهبية`;
  const silverMedal = `\uD83E\uDD48 فضية`;
  const bronzeMedal = `\uD83E\uDD49 برونزية`;
  const [students, setStudents] = useState(() => {
    const savedStudents = localStorage.getItem("students");

    return savedStudents ? JSON.parse(savedStudents) : [];
  });
  useEffect(() => {
    localStorage.setItem("students", JSON.stringify(students));
  }, [students]);
  const changePoints = (id, amount) => {
    setStudents(
      students.map((student) =>
        student.id === id
          ? {
              ...student,
              points: Math.min(1000, Math.max(0, student.points + amount)),
            }
          : student,
      ),
    );
  };
  const getMedal = (points) => {
    if (points >= 1000) {
      return trophy;
    }
    if (points >= 450) {
      return goldMedal;
    }
    if (points >= 100) {
      return silverMedal;
    }
    if (points >= 25) {
      return bronzeMedal;
    }

    return "لا توجد ميداليات";
  };
  const deleteStudent = (id) => {
    setStudents(students.filter((student) => student.id !== id));
  };

  const [sortOrder, setSortOrder] = useState("default");

  const sortedStudents = [...students].sort((a, b) => {
    if (sortOrder === "asc") {
      return b.points - a.points;
    }

    if (sortOrder === "desc") {
      return a.points - b.points;
    }

    return 0;
  });
  const [showForm, setShowForm] = useState(false);
  return (
    <section className="dashboard-page">
      <div className="dashboard-head">
        <h3 className="greeting-dashboard">
          مرحبا ,{localStorage.getItem("teacherName")} 👋🏻
        </h3>
        <p>
          <span className="head-card">عدد الطلاب : {students.length}</span>
        </p>
        <p>
          <span className="head-card">
            {dayNumber} {dayName}
          </span>
        </p>
        <p>
          <span className="head-card">{monthArabic}</span>
        </p>
      </div>
      <div className="dashboard-bar">
        <button className="add-st" onClick={() => setShowForm(true)}>
          اضافة طالب
        </button>
        <h3 className="st-num">{students.length}</h3>

        <label htmlFor="sortOrder">Sort by:</label>
        <select
          id="sortOrder"
          value={sortOrder}
          onChange={(e) => setSortOrder(e.target.value)}
        >
          <option value="default">Default (Unsorted)</option>
          <option value="asc">اعلي النقاط</option>
          <option value="desc">اقل النقاط</option>
        </select>
      </div>
      <div className="students-list">
        {sortedStudents.map((student) => (
          <div
            className="student-card"
            key={student.id}
            onClick={() => navigate(`/student/${student.id}`)}
          >
            <h3>{student.name}</h3>
            <p> النقاط : {student.points}</p>
            <p> الميدالية : {getMedal(student.points)}</p>
            <button
              onClick={(e) => {
                e.stopPropagation();
                changePoints(student.id, 5);
              }}
            >
              نقاط +5
            </button>

            <button
              onClick={(e) => {
                e.stopPropagation();
                changePoints(student.id, 10);
              }}
            >
              كويز / امتحان +10
            </button>

            <button
              onClick={(e) => {
                e.stopPropagation();
                changePoints(student.id, -5);
              }}
            >
              تأخير -5
            </button>

            <button
              onClick={(e) => {
                e.stopPropagation();
                changePoints(student.id, -15);
              }}
            >
              غياب -15
            </button>

            <button
              onClick={(e) => {
                e.stopPropagation();
                deleteStudent(student.id);
              }}
            >
              حذف 🗑️
            </button>
          </div>
        ))}
      </div>
      <StudentsCard
        students={students}
        setStudents={setStudents}
        showForm={showForm}
        setShowForm={setShowForm}
      />
    </section>
  );
}

export default Dashboard;
