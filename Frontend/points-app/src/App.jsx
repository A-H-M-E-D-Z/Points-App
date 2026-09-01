import { useState } from "react";
import {
  BrowserRouter,
  Routes,
  Route,
  Navigate,
} from "react-router-dom";

import Login from "./pages/Login.jsx";
import Dashboard from "./pages/Dashboard.jsx";
import Student from "./pages/Student.jsx";

function App() {
  const [loggedIn, setLoggedIn] = useState(
    localStorage.getItem("teacherName") !== null
  );

  return (
    <BrowserRouter>
      {loggedIn ? (
        <Routes>
          <Route path="/dashboard" element={<Dashboard />} />

          <Route path="/student/:id" element={<Student />} />

          <Route
            path="*"
            element={<Navigate to="/dashboard" replace />}
          />
        </Routes>
      ) : (
        <Login onLogin={() => setLoggedIn(true)} />
      )}
    </BrowserRouter>
  );
}

export default App;