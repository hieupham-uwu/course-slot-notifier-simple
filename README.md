# Observer Pattern Demo - Course Waitlist Notification System

Dự án mô phỏng hệ thống đăng ký danh sách chờ môn học áp dụng mẫu thiết kế **Observer Pattern** trong C++.

---

## 📌 Mô tả dự án (Description)

Khi một môn học đã hết chỗ, các sinh viên có thể đăng ký vào danh sách chờ (Waitlist) để nhận thông báo khi có vị trí trống.

- **Interface `IObserver`**: Giao diện chung định nghĩa hành vi nhận thông báo (`onSlotAvailable`).
- **Subject (`Course`)**: Quản lý danh sách các Observer (`waitlist`), phát sự kiện thông báo đồng loạt khi có sinh viên hủy môn (`drop`) làm xuất hiện chỗ trống.
- **Concrete Observer (`Student`)**: Kế thừa `IObserver`, tiếp nhận sự kiện và tự động xử lý gửi thông báo qua danh sách kênh tùy chọn của từng sinh viên (Email, SMS, Outlook, App Push, Zalo,...).

---

## 📁 Cấu trúc dự án (Project Structure)

```text
.
├── include/
│   ├── Course.h       # Khai báo lớp Subject (Course)
│   ├── IObserver.h    # Khai báo Interface Observer (IObserver)
│   └── Student.h      # Khai báo lớp Concrete Observer (Student)
├── src/
│   ├── Course.cpp     # Cài đặt các phương thức của lớp Course
│   ├── Student.cpp    # Cài đặt các phương thức của lớp Student
│   └── main.cpp       # Kịch bản demo từng bước mô phỏng Pattern
├── Makefile           # File cấu hình biên dịch tự động
└── README.md          # Tài liệu hướng dẫn dự án
```

---

## 🛠️ Yêu cầu hệ thống (Prerequisites)

- **Hệ điều hành**: Windows (đã được tối ưu lệnh `del` trong Makefile).
- **Trình biên dịch**: `g++` hỗ trợ tiêu chuẩn **C++14** trở lên (thường đi kèm với MinGW / MSYS2).
- **Công cụ build**: `make` hoặc `mingw32-make`.

---

## 🚀 Hướng dẫn biên dịch và sử dụng (Usage & Makefile Commands)

Mở terminal (CMD, PowerShell, hoặc Git Bash) tại thư mục gốc của dự án và chạy các lệnh tương ứng bên dưới:

### 1. Biên dịch dự án (Build)

Biên dịch các tệp nguồn trong `src/` và thư viện trong `include/` thành file thực thi `demo.exe`:

```bash
make
# hoặc
make demo
```

### 2. Biên dịch và chạy chương trình (Build & Run)

Tự động biên dịch (nếu có thay đổi mã nguồn) và thực thi file `demo.exe`:

```bash
make run
```

### 3. Dọn dẹp dự án (Clean)

Xóa file thực thi `demo.exe` đã tạo:

```bash
make clean
```

---
