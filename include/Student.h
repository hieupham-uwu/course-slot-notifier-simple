#pragma once
#include <string>
#include <vector>
#include "IObserver.h"
using namespace std;

// ============================================================
// 3. CONCRETE OBSERVER: Student
//    Nhan tin, roi tu gui qua cac kenh ma minh da chon.
// ============================================================
class Student : public IObserver {
private:
    string studentId;
    string fullName;
    vector<string> channelList;
    bool printSample;
    int receivedCount;
    int sentMessageCount;

public:
    Student(string id, string name, vector<string> channels,
            bool shouldPrintSample);

    void onSlotAvailable(const string& courseName, int slots) override;

    void addChannel(const string& channel);
    int received() const;
    int sentMessages() const;
};
