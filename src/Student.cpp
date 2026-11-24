#include "Student.h"
#include <iostream>
#include <utility>
using namespace std;

Student::Student(string id, string name, vector<string> channels,
                 bool shouldPrintSample)
    : studentId(move(id)),
      fullName(move(name)),
      channelList(move(channels)),
      printSample(shouldPrintSample),
      receivedCount(0),
      sentMessageCount(0) {}

void Student::onSlotAvailable(const string& courseName, int slots) {
    ++receivedCount;
    for (size_t i = 0; i < channelList.size(); ++i) {
        ++sentMessageCount;

        // Chi in vai mau cho de doc; thuc te la goi API Outlook/SMS/...
        if (printSample) {
            cout << "  [" << channelList[i] << " -> " << studentId << "] "
                 << fullName << ": course " << courseName << " has " << slots
                 << " open slot(s), register now!\n";
        }
    }
}

void Student::addChannel(const string& channel) {
    channelList.push_back(channel);
}

int Student::received() const {
    return receivedCount;
}

int Student::sentMessages() const {
    return sentMessageCount;
}
