#include <iostream>
#include <string>

class SmartDevice {
public:
    enum class Mode {
        LOW_POWER,
        PERFORMANCE,
        OVERHEAT
    };

private:
    double temp;
    Mode mode;
    unsigned int overheatHits;
    bool isFrozen;

    // ================= PERSONALIZATION =================
    /*
     * Personalization Rule (X = last digit of student ID):
     *
     * X ∈ {0,1,2,3} → LOW_POWER threshold = 30°C
     * X ∈ {4,5,6}   → LOW_POWER threshold = 45°C
     * X ∈ {7,8,9}   → LOW_POWER threshold = 20°C
     */
    static double lowPowerLimit() {
        return 45.0; // CHANGE according to your ID
    }

    static double overheatLimit() {
        return 80.0;
    }

    static const char* unlockKey() {
        return "HAMMAD";
    }

    // Decide mode purely from temperature
    Mode evaluateMode() {
        if (temp >= overheatLimit())
            return Mode::OVERHEAT;

        if (temp >= lowPowerLimit())
            return Mode::PERFORMANCE;

        return Mode::LOW_POWER;
    }

    // Handle overheat side effects
    void registerOverheat() {
        overheatHits++;
        if (overheatHits > 2) {
            isFrozen = true;
            std::cout << "System frozen: excessive overheating.\n";
        }
    }

public:
    SmartDevice() {
        temp = 0.0;
        mode = Mode::LOW_POWER;
        overheatHits = 0;
        isFrozen = false;
    }

    void feedSensor(double value) {
        temp = value;
    }

    void updateMode() {
        if (isFrozen) {
            std::cout << "Mode update blocked: device locked.\n";
            return;
        }

        Mode next = evaluateMode();
        mode = next;

        if (next == Mode::OVERHEAT)
            registerOverheat();
    }

    void reset(const std::string& key) {
        if (key != unlockKey()) {
            std::cout << "Access denied: invalid reset key.\n";
            return;
        }

        isFrozen = false;
        overheatHits = 0;
        mode = Mode::LOW_POWER;
        std::cout << "System reset complete.\n";
    }

    Mode currentMode() {
        return mode;
    }

    bool locked() {
        return isFrozen;
    }
};


int main() {
    SmartDevice device;

    std::cout << "SmartDevice simulation started\n\n";

    // First overheat
    device.feedSensor(85);
    device.updateMode();

    // Second overheat
    device.feedSensor(90);
    device.updateMode();

    // Third overheat -> device locks
    device.feedSensor(95);
    device.updateMode();

    // Attempt mode change while locked
    device.feedSensor(30);
    device.updateMode();

    // Wrong reset password
    device.reset("Ateeq");

    // Correct reset
    device.reset("HAMMAD");

    // Normal operation after reset
    device.feedSensor(25);
    device.updateMode();

    std::cout << "\nSmartDevice simulation ended\n";
    return 0;
}
