import { useState } from "react";
function Login({ onLogin }) {
  const [teacherName, setTeacherName] = useState("");

  const handleSubmit = (event) => {
    event.preventDefault();

    localStorage.setItem("teacherName", teacherName);

    onLogin();
  };

  return (
    <section className="login-page">
      <h1 className="greeting">مرحبا بك 👋</h1>
      <h4 className="enter-name-techer">أدخل اسم المعلم :</h4>
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          placeholder="Enter Your name ...."
          maxLength={25}
          className="teacher-name-input"
          value={teacherName}
          onChange={(event) => setTeacherName(event.target.value)}
        ></input>
        <br />
        <button type="submit" className="t-btn">
          تأكيد
        </button>
      </form>
    </section>
  );
}

export default Login;
