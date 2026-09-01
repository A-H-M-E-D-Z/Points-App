import { useEffect, useState } from "react";
import { useNavigate, useParams } from "react-router-dom";

function Student() {
  const { id } = useParams();
  const navigate = useNavigate();

  const [student, setStudent] = useState(null);

  useEffect(() => {
    const savedStudents = localStorage.getItem("students");

    if (savedStudents) {
      const students = JSON.parse(savedStudents);

      const foundStudent = students.find(
        (student) => student.id === Number(id)
      );

      setStudent(foundStudent);
    }
  }, [id]);

  const changePoints = (amount) => {
    const savedStudents = localStorage.getItem("students");

    if (!savedStudents) return;

    const students = JSON.parse(savedStudents);

    const updatedStudents = students.map((student) =>
      student.id === Number(id)
        ? {
            ...student,
            points: Math.min(1000, Math.max(0, student.points + amount)),
          }
        : student
    );

    localStorage.setItem("students", JSON.stringify(updatedStudents));

    const updatedStudent = updatedStudents.find(
      (student) => student.id === Number(id)
    );

    setStudent(updatedStudent);
  };

  const deleteStudent = () => {
    const savedStudents = localStorage.getItem("students");

    if (!savedStudents) return;

    const students = JSON.parse(savedStudents);

    const updatedStudents = students.filter(
      (student) => student.id !== Number(id)
    );

    localStorage.setItem("students", JSON.stringify(updatedStudents));

    navigate("/dashboard");
  };

  const getMedal = (points) => {
    if (points >= 1000) {
      return "🏆 نيشان";
    }

    if (points >= 450) {
      return "🥇 ذهبية";
    }

    if (points >= 100) {
      return "🥈 فضية";
    }

    if (points >= 25) {
      return "🥉 برونزية";
    }

    return "لا توجد ميداليات";
  };

  const getProgressColor = (points) => {
    if (points >= 450) {
      return "lime";
    }

    if (points >= 100) {
      return "pistage";
    }

    if (points >= 25) {
      return "orange";
    }

    return "red";
  };

  if (!student) {
    return <h2>الطالب غير موجود</h2>;
  }

  const progress = Math.min(student.points / 1000, 1) * 100;

  return (
    <section className="student-page">

      <button
        className="back-dashboard"
        onClick={() => navigate("/dashboard")}
      >
        ← العودة
      </button>

      <div className="student-info">

        <h1>{student.name}</h1>

        <p>المجموعة: {student.group}</p>

        <p>الصف: {student.grade}</p>

        <p>الميدالية: {getMedal(student.points)}</p>

        <p>النقاط: {student.points}</p>

      </div>

      <div className="student-progress">

        <div className="progress-bar">

          <div
            className={`progress-fill ${getProgressColor(student.points)}`}
            style={{ width: `${progress}%` }}
          />

        </div>

        <p>{student.points} / 1000</p>

      </div>

      <div className="student-actions">

        <button onClick={() => changePoints(5)}>
          نقاط +5
        </button>

        <button onClick={() => changePoints(10)}>
          كويز / امتحان +10
        </button>

        <button onClick={() => changePoints(-5)}>
          تأخير -5
        </button>

        <button onClick={() => changePoints(-15)}>
          غياب -15
        </button>

        <button onClick={deleteStudent}>
          حذف 🗑️
        </button>

      </div>

    </section>
  );
}

export default Student;