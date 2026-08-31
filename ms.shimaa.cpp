import 'package:flutter/material.dart';

void main() {
  runApp(const StudentPointsApp());
}

class StudentPointsApp extends StatelessWidget {
  const StudentPointsApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'تطبيق متابعة الطلاب',
      theme: ThemeData(
        primarySwatch: Colors.teal,
        fontFamily: 'Arial',
      ),
      home: const LoginPage(),
    );
  }
}

// ================= 1. شاشة تسجيل الدخول =================
class LoginPage extends StatefulWidget {
  const LoginPage({super.key});

  @override
  State<LoginPage> createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  final TextEditingController nameController = TextEditingController();

  @override
  void dispose() {
    // تنظيف الـ controller لما الشاشة تتقفل عشان نتجنب تسريب الذاكرة
    nameController.dispose();
    super.dispose();
  }

  void _login() {
    final name = nameController.text.trim();

    if (name.isEmpty) {
      // فيدباك للمستخدم لو حاول يدخل من غير اسم
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('من فضلك اكتب اسم الطالب أولاً')),
      );
      return;
    }

    Navigator.pushReplacement(
      context,
      MaterialPageRoute(
        builder: (context) => StudentDashboard(studentName: name),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Padding(
        padding: const EdgeInsets.all(25.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(Icons.school, size: 80, color: Colors.teal),
            const SizedBox(height: 20),
            const Text(
              'تسجيل دخول الطالب',
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 30),
            TextField(
              controller: nameController,
              textInputAction: TextInputAction.done,
              onSubmitted: (_) => _login(),
              decoration: const InputDecoration(
                labelText: 'اسم الطالب',
                border: OutlineInputBorder(),
                prefixIcon: Icon(Icons.person),
              ),
            ),
            const SizedBox(height: 20),
            SizedBox(
              width: double.infinity,
              height: 50,
              child: ElevatedButton(
                onPressed: _login,
                child: const Text('دخول', style: TextStyle(fontSize: 18)),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

// ================= 2. لوحة تحكم الطالب والنقاط =================
class StudentDashboard extends StatefulWidget {
  final String studentName;
  const StudentDashboard({super.key, required this.studentName});

  @override
  State<StudentDashboard> createState() => _StudentDashboardState();
}

class _StudentDashboardState extends State<StudentDashboard> {
  int points = 50; // نقاط تجريبية تبدأ بها

  // حدود المستويات في مكان واحد عشان يبقى التعديل عليها أسهل
  static const int silverThreshold = 80;
  static const int goldThreshold = 150;

  // دالة تحديد المستوى بناءً على النقاط
  String getLevel(int pts) {
    if (pts >= goldThreshold) return "ذهبي 🥇";
    if (pts >= silverThreshold) return "فضي 🥈";
    return "برونزي 🥉";
  }

  void _addPoints(int amount) {
    setState(() {
      points += amount;
      if (points < 0) points = 0; // منع النقاط من تبقى بالسالب
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('أهلاً ${widget.studentName}'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(20.0),
        child: Column(
          children: [
            // بطاقة عرض النقاط والمستوى
            Card(
              elevation: 4,
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(15)),
              child: Padding(
                padding: const EdgeInsets.all(20.0),
                child: Column(
                  children: [
                    const Text('مجموع نقاطك الحالية', style: TextStyle(fontSize: 18, color: Colors.grey)),
                    const SizedBox(height: 10),
                    Text('$points', style: const TextStyle(fontSize: 45, fontWeight: FontWeight.bold, color: Colors.teal)),
                    const Divider(height: 30),
                    Text('المستوى: ${getLevel(points)}', style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold)),
                  ],
                ),
              ),
            ),
            const SizedBox(height: 30),

            // أزرار تجريبية لإضافة النقاط
            Wrap(
              spacing: 12,
              runSpacing: 12,
              alignment: WrapAlignment.center,
              children: [
                ElevatedButton.icon(
                  onPressed: () => _addPoints(10),
                  icon: const Icon(Icons.check),
                  label: const Text('حضور (+10)'),
                ),
                ElevatedButton.icon(
                  onPressed: () => _addPoints(5),
                  icon: const Icon(Icons.star),
                  label: const Text('تفاعل (+5)'),
                ),
                ElevatedButton.icon(
                  style: ElevatedButton.styleFrom(backgroundColor: Colors.redAccent),
                  onPressed: () => _addPoints(-10),
                  icon: const Icon(Icons.close),
                  label: const Text('غياب (-10)'),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
