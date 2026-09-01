import 'package:flutter/material.dart';

void main() {
  runApp(const PointsApp());
}

// ---------------------------------------------------------
// Models (النماذج البرمجية)
// ---------------------------------------------------------
class StudentModel {
  final String id;
  final String name;
  int points;
  final String grade;

  StudentModel({
    required this.id,
    required this.name,
    required this.points,
    required this.grade,
  });
}

// ---------------------------------------------------------
// Main Application Setup
// ---------------------------------------------------------
class PointsApp extends StatelessWidget {
  const PointsApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Points App',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.indigo,
        scaffoldBackgroundColor: const Color(0xFFF5F7FA),
        useMaterial3: true,
      ),
      initialRoute: '/login',
      routes: {
        '/login': (context) => const LoginScreen(),
        '/dashboard': (context) => const DashboardScreen(),
      },
    );
  }
}

// ---------------------------------------------------------
// 1. Login Screen (شاشة تسجيل الدخول)
// ---------------------------------------------------------
class LoginScreen extends StatefulWidget {
  const LoginScreen({super.key});

  @override
  State<LoginScreen> createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final _usernameController = TextEditingController();
  final _passwordController = TextEditingController();

  void _handleLogin() {
    if (_usernameController.text.isNotEmpty && _passwordController.text.isNotEmpty) {
      Navigator.pushReplacementNamed(context, '/dashboard');
    } else {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('يرجى إدخال اسم المستخدم وكلمة المرور')),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: SingleChildScrollView(
          padding: const EdgeInsets.all(24.0),
          child: Card(
            elevation: 8,
            shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(16)),
            child: Padding(
              padding: const EdgeInsets.all(32.0),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                children: [
                  const Icon(Icons.stars, size: 64, color: Colors.indigo),
                  const SizedBox(height: 16),
                  const Text(
                    'تسجيل الدخول',
                    style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
                  ),
                  const SizedBox(height: 24),
                  TextField(
                    controller: _usernameController,
                    decoration: const InputDecoration(
                      labelText: 'اسم المستخدم',
                      prefixIcon: Icon(Icons.person),
                      border: OutlineInputBorder(),
                    ),
                  ),
                  const SizedBox(height: 16),
                  TextField(
                    controller: _passwordController,
                    obscureText: true,
                    decoration: const InputDecoration(
                      labelText: 'كلمة المرور',
                      prefixIcon: Icon(Icons.lock),
                      border: OutlineInputBorder(),
                    ),
                  ),
                  const SizedBox(height: 24),
                  SizedBox(
                    width: double.infinity,
                    height: 48,
                    child: ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.indigo,
                        foregroundColor: Colors.white,
                      ),
                      onPressed: _handleLogin,
                      child: const Text('دخول', style: TextStyle(fontSize: 16)),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}

// ---------------------------------------------------------
// 2. Dashboard Screen (لوحة التحكم الرئيسية)
// ---------------------------------------------------------
class DashboardScreen extends StatefulWidget {
  const DashboardScreen({super.key});

  @override
  State<DashboardScreen> createState() => _DashboardScreenState();
}

class _DashboardScreenState extends State<DashboardScreen> {
  // بيانات افتراضية للطلاب
  List<StudentModel> students = [
    StudentModel(id: '1', name: 'أحمد محمود', points: 120, grade: 'الصف الأول'),
    StudentModel(id: '2', name: 'سارة علي', points: 95, grade: 'الصف الثاني'),
    StudentModel(id: '3', name: 'عمر خالد', points: 150, grade: 'الصف الأول'),
    StudentModel(id: '4', name: 'مريم محمد', points: 80, grade: 'الصف الثالث'),
  ];

  void _addPoints(StudentModel student, int amount) {
    setState(() {
      student.points += amount;
    });
  }

  void _deductPoints(StudentModel student, int amount) {
    setState(() {
      if (student.points >= amount) {
        student.points -= amount;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    int totalPoints = students.fold(0, (sum, item) => sum + item.points);

    return Scaffold(
      appBar: AppBar(
        title: const Text('لوحة التحكم - نظام النقاط'),
        backgroundColor: Colors.indigo,
        foregroundColor: Colors.white,
        actions: [
          IconButton(
            icon: const Icon(Icons.logout),
            onPressed: () => Navigator.pushReplacementNamed(context, '/login'),
          )
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            // بطاقات الإحصائيات
            Row(
              children: [
                _buildStatCard('إجمالي الطلاب', '${students.length}', Colors.blue),
                const SizedBox(width: 12),
                _buildStatCard('مجموع النقاط', '$totalPoints', Colors.green),
              ],
            ),
            const SizedBox(height: 24),
            const Text(
              'قائمة الطلاب',
              style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 12),
            // عرض قائمة بطاقات الطلاب (StudentsCard / Student View)
            Expanded(
              child: GridView.builder(
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2,
                  childAspectRatio: 0.85,
                  crossAxisSpacing: 12,
                  mainAxisSpacing: 12,
                ),
                itemCount: students.length,
                itemBuilder: (context, index) {
                  final student = students[index];
                  return StudentCardWidget(
                    student: student,
                    onAdd: () => _addPoints(student, 10),
                    onDeduct: () => _deductPoints(student, 10),
                  );
                },
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildStatCard(String title, String value, Color color) {
    return Expanded(
      child: Card(
        color: color.withOpacity(0.1),
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              Text(title, style: TextStyle(color: color, fontSize: 14)),
              const SizedBox(height: 8),
              Text(
                value,
                style: TextStyle(color: color, fontSize: 22, fontWeight: FontWeight.bold),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

// ---------------------------------------------------------
// 3. Student Card Component (مكون بطاقة الطالب)
// ---------------------------------------------------------
class StudentCardWidget extends StatelessWidget {
  final StudentModel student;
  final VoidCallback onAdd;
  final VoidCallback onDeduct;

  const StudentCardWidget({
    super.key,
    required this.student,
    required this.onAdd,
    required this.onDeduct,
  });

  @override
  Widget build(BuildContext context) {
    return Card(
      elevation: 4,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
      child: Padding(
        padding: const EdgeInsets.all(12.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            CircleAvatar(
              backgroundColor: Colors.indigo.shade100,
              child: Text(student.name[0]),
            ),
            Text(
              student.name,
              style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 16),
              textAlign: TextAlign.center,
            ),
            Text(student.grade, style: const TextStyle(color: Colors.grey, fontSize: 12)),
            Container(
              padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 4),
              decoration: BoxDecoration(
                color: Colors.amber.shade100,
                borderRadius: BorderRadius.circular(20),
              ),
              child: Text(
                '${student.points} نقطة',
                style: const TextStyle(fontWeight: FontWeight.bold, color: Colors.amberAccent),
              ),
            ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                IconButton(
                  icon: const Icon(Icons.add_circle, color: Colors.green),
                  onPressed: onAdd,
                ),
                IconButton(
                  icon: const Icon(Icons.remove_circle, color: Colors.red),
                  onPressed: onDeduct,
                ),
              ],
            )
          ],
        ),
      ),
    );
  }
}
