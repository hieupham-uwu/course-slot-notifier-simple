#include "Course.h"

#include <utility>
using namespace std;

Course::Course(string name, int capacity)
    : courseName(move(name)), seatCapacity(capacity), enrolledCount(0) {}

int Course::availableSlots() const { return seatCapacity - enrolledCount; }

void Course::attach(IObserver* observer) { waitlist.push_back(observer); }

void Course::detach(IObserver* observer) {
    for (size_t i = 0; i < waitlist.size(); ++i) {
        if (waitlist[i] == observer) {
            waitlist.erase(waitlist.begin() + static_cast<long>(i));
            return;
        }
    }
}

void Course::enroll(int count) {
    enrolledCount += count;
    if (enrolledCount > seatCapacity) {
        enrolledCount = seatCapacity;
    }
}

void Course::drop() {
    if (enrolledCount == 0) {
        return;
    }

    const bool wasFull = (availableSlots() == 0);
    --enrolledCount;

    // Chi thong bao khi lop vua tu "het cho" thanh "con cho".
    if (wasFull && availableSlots() > 0) {
        notifyStudents();
    }
}

size_t Course::waitlistSize() const { return waitlist.size(); }

void Course::notifyStudents() {
    for (size_t i = 0; i < waitlist.size(); ++i) {
        waitlist[i]->onSlotAvailable(courseName, availableSlots());
    }
}
