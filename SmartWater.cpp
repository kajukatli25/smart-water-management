#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual double read() const = 0;
    virtual std::string label() const = 0;
};

class FlowSensor : public Sensor {
private:
    double litresPerMinute;

public:
    explicit FlowSensor(double flow) : litresPerMinute(flow) {
        if (!(flow >= 0.0)) {
            throw std::invalid_argument("Flow must be non-negative.");
        }
    }
    double read() const override { return litresPerMinute; }
    std::string label() const override { return "Flow (L/min)"; }
};

class TankLevelSensor : public Sensor {
private:
    double percentage;

public:
    explicit TankLevelSensor(double level) : percentage(level) {
        if (!(level >= 0.0 && level <= 100.0)) {
            throw std::invalid_argument("Tank level must be 0 to 100%.");
        }
    }
    double read() const override { return percentage; }
    std::string label() const override { return "Tank level (%)"; }
};

class WaterMonitor {
private:
    static void showReading(const Sensor& sensor) {
        std::cout << sensor.label() << ": " << sensor.read() << '\n';
    }

public:
    void inspect(const FlowSensor& flow, const TankLevelSensor& tank,
                 bool quietHours, int minutes) const {
        showReading(flow);
        showReading(tank);
        bool alert = false;

        if (quietHours && minutes >= 30 && flow.read() >= 0.5) {
            std::cout << "Alert: Possible leak. Inspect the pipe.\n";
            std::cout << "Estimated volume (L): "
                      << flow.read() * minutes << '\n';
            alert = true;
        }
        if (tank.read() <= 20.0) {
            std::cout << "Alert: Tank level is low.\n";
            alert = true;
        } else if (tank.read() >= 95.0) {
            std::cout << "Alert: Tank level is high.\n";
            alert = true;
        }
        if (!alert) {
            std::cout << "Status: Normal\n";
        }
    }
};

int main() {
    const WaterMonitor monitor;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Smart Water Management | SDG 6\n";

    std::cout << "\nCase 1: Normal daytime use\n";
    monitor.inspect(FlowSensor(2.0), TankLevelSensor(60.0), false, 30);

    std::cout << "\nCase 2: Continuous flow during quiet hours\n";
    monitor.inspect(FlowSensor(0.5), TankLevelSensor(45.0), true, 30);

    std::cout << "\nCase 3: Low tank level\n";
    monitor.inspect(FlowSensor(0.0), TankLevelSensor(15.0), true, 30);

    std::cout << "\nCase 4: High tank level\n";
    monitor.inspect(FlowSensor(0.0), TankLevelSensor(96.0), true, 30);
}
