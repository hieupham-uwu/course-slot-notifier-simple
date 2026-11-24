#pragma once
#include <string>
using namespace std;

// ============================================================
// 1. INTERFACE OBSERVER
//    Course chi biet dung mot ham nay, khong biet do la sinh
//    vien nao hay gui bang kenh gi.
// ============================================================
class IObserver {
public:
    virtual ~IObserver() {}
    virtual void onSlotAvailable(const string& courseName, int slots) = 0;
};
