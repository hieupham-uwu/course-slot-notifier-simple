#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "IObserver.h"
using namespace std;

// ============================================================
// 2. SUBJECT: Course
//    Giu danh sach nguoi dang ky nhan tin (waitlist).
// ============================================================
class Course {
private:
    // Day la toan bo Observer pattern: di tung observer va goi
    // ham chung. Course khong biet ben trong observer lam gi.
    void notifyStudents();

    string courseName;
    int seatCapacity;
    int enrolledCount;
    vector<IObserver*> waitlist;

public:
    Course(string name, int capacity);

    int availableSlots() const;

    // Sinh vien dang ky / huy theo doi bat ky luc nao.
    void attach(IObserver* observer);
    void detach(IObserver* observer);

    void enroll(int count);

    // Giam 1 cho; chi bao tin khi lop vua tu "het cho" sang "con cho".
    void drop();

    size_t waitlistSize() const;
};
