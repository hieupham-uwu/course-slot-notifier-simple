#include <iostream>
#include <string>
#include <vector>

#include "Course.h"
#include "Student.h"

using namespace std;

// Tam dung de nguoi thuyet trinh giai thich, nhan Enter de qua buoc tiep theo
void pauseStep(const string& title) {
    cout << "\n============================================================\n";
    cout << title << "\n";
    cout << "============================================================\n";
    cout << ">> Nhan Enter de thuc hien...";
    cin.get();
    cout << "\n";
}

int main() {
    cout << "=== DEMO OBSERVER PATTERN: THONG BAO SLOT MON HOC ===\n";

    // ------------------------------------------------------------
    // BUOC 1: Khoi tao Subject (Course) trong trang thai day cho
    // ------------------------------------------------------------
    pauseStep("BUOC 1: Tao mon hoc (Subject) da day cho (60/60)");

    Course dsa("Data Structures & Algorithms", 60);
    dsa.enroll(60);

    cout << "Mon hoc: Data Structures & Algorithms\n";
    cout << "So cho trong hien tai: " << dsa.availableSlots() << "\n";

    // ------------------------------------------------------------
    // BUOC 2: Cac Observer (Student) dang ky theo doi (attach)
    // ------------------------------------------------------------
    pauseStep("BUOC 2: 3 sinh vien (Observers) bam 'Nhan thong bao' (attach)");

    Student an("SV01", "Nguyen Van An", {"Email", "SMS"}, true);
    Student binh("SV02", "Tran Thi Binh", {"App Push"}, true);
    Student chi("SV03", "Le Hoang Chi", {"Outlook", "Telegram"}, true);

    dsa.attach(&an);
    dsa.attach(&binh);
    dsa.attach(&chi);

    cout << "Da dang ky thanh cong!\n";
    cout << "  - An   (SV01): Email, SMS\n";
    cout << "  - Binh (SV02): App Push\n";
    cout << "  - Chi  (SV03): Outlook, Telegram\n";
    cout << "Tong so nguoi trong waitlist: " << dsa.waitlistSize() << "\n";

    // ------------------------------------------------------------
    // BUOC 3: Su kien xay ra -> Subject tu dong thong bao (notify)
    // ------------------------------------------------------------
    pauseStep("BUOC 3: Mot sinh vien huy mon (drop) -> Tu dong notify");

    cout << "[Su kien] Co 1 sinh vien vua rut khoi lop (slot: 0 -> 1):\n\n";
    dsa.drop();

    // ------------------------------------------------------------
    // BUOC 4: Huy dang ky (detach) & Chung minh tinh linh hoat
    // ------------------------------------------------------------
    pauseStep("BUOC 4: An huy theo doi (detach), Binh them kenh Zalo");

    dsa.detach(&an);
    binh.addChannel("Zalo");  // Mo rong Observer ma khong can sua code Course

    cout << "  - An (SV01) da huy theo doi (detach).\n";
    cout << "  - Binh (SV02) vua bat them kenh 'Zalo'.\n";
    cout << "Tong so nguoi con lai trong waitlist: " << dsa.waitlistSize()
         << "\n";

    // Lap day lai cho trong de kich hoat lai su kien 0 -> 1
    dsa.enroll(1);

    // ------------------------------------------------------------
    // BUOC 5: Su kien lap lai -> Chi nguoi con dang ky moi nhan tin
    // ------------------------------------------------------------
    pauseStep("BUOC 5: Lop day lai, sau do co nguoi huy mon lan 2");

    cout << "[Su kien] Co 1 sinh vien khac huy mon (slot: 0 -> 1):\n\n";
    dsa.drop();

    // ------------------------------------------------------------
    // TONG KET
    // ------------------------------------------------------------
    cout << "\n============================================================\n";
    cout << "TONG KET SO LAN NHAN THONG BAO:\n";
    cout << "  - An   (SV01): " << an.received() << " lan ("
         << an.sentMessages() << " tin nhan)\n";
    cout << "  - Binh (SV02): " << binh.received() << " lan ("
         << binh.sentMessages() << " tin nhan)\n";
    cout << "  - Chi  (SV03): " << chi.received() << " lan ("
         << chi.sentMessages() << " tin nhan)\n";
    cout << "============================================================\n";
    cin.get();

    return 0;
}