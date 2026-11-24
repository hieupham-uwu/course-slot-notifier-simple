# Simple — chỉ Observer pattern, 3 lớp, tách file rõ ràng

Bản tối giản của demo “thông báo khi môn học có slot trống”, dành cho người mới
học pattern. Ở đây **chỉ có Observer**, không có Strategy, không `shared_ptr`,
không `try/catch`:

- `Course` (Subject) giữ `vector<IObserver*>` — con trỏ thô.
- `Student` (Concrete Observer) giữ danh sách kênh là `vector<string>`.
- Khi lớp chuyển từ `0` slot sang còn slot, `Course` gọi
  `onSlotAvailable(courseName, slots)` cho từng observer.

Repo này chứa bản `simple` độc lập. Bản đầy đủ (thêm Strategy cho kênh,
`shared_ptr`, `try/catch`, unit test) nằm trong thư mục `full/` của project gốc.

## 1. Cấu trúc

```
.
├── include/
│   ├── IObserver.h        # interface Observer (hàm thuần ảo)
│   ├── Course.h           # Subject: waitlist + attach/detach/notify
│   └── Student.h          # Concrete Observer: nhận tin, gửi qua kênh
├── src/
│   ├── Course.cpp         # cài đặt Subject
│   ├── Student.cpp        # cài đặt Concrete Observer
│   └── main.cpp           # menu tương tác + kịch bản 1.000 sinh viên
├── class-diagram-simple.mmd   # sơ đồ lớp bản rút gọn (Mermaid)
├── Makefile
├── run.bat                    # double-click: build + chạy + dừng chờ Enter
├── .gitignore                 # bỏ qua demo.exe và file build
└── README.md
```

Mỗi lớp một cặp `.h`/`.cpp`; `main.cpp` chỉ dựng menu và kịch bản, không chứa
logic pattern.

## 2. Luồng chạy

```
main: course.enroll(60)                  -> lop day, 0 slot
main: course.attach(sv) x 1000           -> waitlist = 1000
main: course.drop()                      -> 0 -> 1 slot
        Course::drop()                   -> notifyStudents()
        Course::notifyStudents()         -> sv->onSlotAvailable(...)
        Student::onSlotAvailable()       -> ++receivedCount
                                            ++sentMessageCount cho tung kenh
main: course.detach(sv)                  -> waitlist = 999
main: course.enroll(...) + course.drop() -> thông báo lần hai
```

Điểm cốt lõi chỉ nằm trong `Course::drop()`:

```cpp
const bool wasFull = (availableSlots() == 0);
--enrolledCount;
if (wasFull && availableSlots() > 0) {
    notifyStudents();  // chi bao khi 0 -> con cho
}
```

và `Course::notifyStudents()`:

```cpp
for (size_t i = 0; i < waitlist.size(); ++i) {
    waitlist[i]->onSlotAvailable(courseName, availableSlots());
}
```

`Course` không biết `Student` là ai, cũng không biết tin được gửi qua Outlook
hay SMS. Thêm kênh mới chỉ là `sv->addChannel("Zalo")` — `Course` không đổi.

## 3. Build và chạy

Yêu cầu: compiler hỗ trợ C++14 (đã kiểm tra với MinGW.org GCC 6.3 trên Windows).
Chạy các lệnh **trong thư mục gốc repo**:

```bash
mingw32-make        # build demo.exe
mingw32-make run    # chạy demo
mingw32-make clean  # xoá demo.exe
```

Trên Windows có thể double-click `run.bat`: file tự build rồi chạy demo và dừng
lại chờ Enter, nên đọc được kết quả. Double-click thẳng `demo.exe` cũng xem
được: khi chạy một mình trong cửa sổ console riêng (không có terminal), chương
trình in thêm `Press Enter to exit...` và giữ cửa sổ cho tới khi bấm Enter.
Chạy từ cmd/PowerShell/make thì không có dòng này và không bị dừng.

Không dùng make:

```bash
g++ -std=c++14 -Wall -Wextra -pedantic -O2 -Iinclude \
    src/Course.cpp src/Student.cpp src/main.cpp -o demo.exe -static

demo.exe
```

`-static` để `.exe` chạy độc lập, không cần DLL của MinGW trong `PATH`.

Sau khi build, `demo.exe` mở **menu tương tác** (lớp khởi tạo đã đầy, nên hủy
một chỗ là thấy Observer được gọi ngay):

```
1. Show course status
2. Add a student to the waitlist
3. Unsubscribe a student (detach)
4. A student drops the course (free 1 seat)
5. Enroll seats (fill free seats)
6. Run scripted demo (1,000 students)
0. Exit
```

Khi khởi động, nhập tên lớp và sức chứa (Enter để lấy mặc định 60). Chọn `6`
để chạy kịch bản tự động ở mục 4; các mục `1`–`5` để tự thử thêm/hủy sinh
viên, drop ghế và xem tin nhắn in ra.

## 4. Kết quả

Kết quả dưới đây là output khi chọn mục `6` (kịch bản 1.000 sinh viên):

```
=== SIMPLE: OBSERVER PATTERN ONLY ===
Course is full, 0 seats available.

Students on the waitlist: 1000

[1] SV9999 drops the course, 1 seat left:
  [Outlook -> SV0001] Student 0001: course Data Structures and Algorithms has 1 open slot(s), register now!
  [Email -> SV0001] Student 0001: course Data Structures and Algorithms has 1 open slot(s), register now!
  [SMS -> SV0001] Student 0001: course Data Structures and Algorithms has 1 open slot(s), register now!
  [App Push -> SV0001] Student 0001: course Data Structures and Algorithms has 1 open slot(s), register now!
  [Outlook -> SV0002] Student 0002: course Data Structures and Algorithms has 1 open slot(s), register now!
  ...
    Students notified: 1000
    Total messages: 4050

[2] SV0001 unsubscribes, 999 students remain.
[3] SV8888 drops the course, sends 4046 more messages.
    SV0001 received 1 time(s), SV0002 received 2 time(s).
```

- 1.000 sinh viên, mỗi người 4 kênh → 4.000 tin.
- 50 sinh viên (chỉ số chia hết cho 20) có thêm Telegram → +50 tin.
- Tổng 4.050 tin ở lần thông báo đầu; sau khi SV0001 detach còn 4.046.
- Trong kịch bản tự động, chỉ 2 sinh viên đầu in tin mẫu ra console để output
  dễ đọc; sinh viên thêm qua menu luôn in tin để dễ quan sát.

## 5. Bản simple cố tình thiếu gì?

| Thiếu | Hậu quả | Bản full giải quyết |
|---|---|---|
| Interface kênh (Strategy) | Kênh là chuỗi, không đa hình | `INotificationChannel` + 5 class kênh |
| `shared_ptr` | Observer phải sống lâu hơn `Course` | `shared_ptr` giữ vòng đời |
| `try/catch` | Một kênh lỗi làm hỏng cả vòng notify | Cô lập lỗi từng kênh/observer |
| Bản sao danh sách khi notify | Observer tự detach trong callback sẽ hỏng vòng lặp | Snapshot trước khi notify |
| Unit test | Chỉ kiểm tra bằng mắt | 7 test tự động |

## 6. Bài tập mở rộng

- Thêm kênh `Zalo` bằng `addChannel("Zalo")` — không sửa `Course`.
- Cho `drop()` trả `bool` (có notify hay không) và in kết quả trong `main`.
- Chỉ notify một lần rồi `detach` ngay trong callback (cần snapshot danh sách).
- So sánh với bản full để thấy Strategy và `shared_ptr` giải quyết vấn đề gì.

Sơ đồ lớp: [`class-diagram-simple.mmd`](class-diagram-simple.mmd) (dán vào
<https://mermaid.live> hoặc dùng extension Mermaid trong VS Code).
