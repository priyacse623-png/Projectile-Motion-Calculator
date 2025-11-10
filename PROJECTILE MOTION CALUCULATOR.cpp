#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Projectile {
private:
    double velocity;      // Initial velocity (m/s)
    double angle;         // Launch angle (degrees)
    double gravity;       // Acceleration due to gravity (m/s²)
    
    // Convert degrees to radians
    double toRadians(double deg) const {
        return deg * M_PI / 180.0;
    }

public:
    // Constructor
    Projectile(double v = 0, double a = 0, double g = 9.8) 
        : velocity(v), angle(a), gravity(g) {}
    
    // Setters
    void setVelocity(double v) { velocity = v; }
    void setAngle(double a) { angle = a; }
    void setGravity(double g) { gravity = g; }
    
    // Getters
    double getVelocity() const { return velocity; }
    double getAngle() const { return angle; }
    double getGravity() const { return gravity; }
    
    // Calculate range: R = (v² * sin(2?)) / g
    double calculateRange() const {
        double angleRad = toRadians(angle);
        return (velocity * velocity * sin(2 * angleRad)) / gravity;
    }
    
    // Calculate time of flight: T = (2 * v * sin(?)) / g
    double calculateTimeOfFlight() const {
        double angleRad = toRadians(angle);
        return (2 * velocity * sin(angleRad)) / gravity;
    }
    
    // Calculate max height: H = (v² * sin²(?)) / (2g)
    double calculateMaxHeight() const {
        double angleRad = toRadians(angle);
        double sinTheta = sin(angleRad);
        return (velocity * velocity * sinTheta * sinTheta) / (2 * gravity);
    }
    
    // Display all results
    void displayResults() const {
        cout << "\n" << string(50, '=') << endl;
        cout << "        PROJECTILE MOTION RESULTS" << endl;
        cout << string(50, '=') << endl;
        
        cout << fixed << setprecision(2);
        cout << "\nInput Parameters:" << endl;
        cout << "  Initial Velocity: " << velocity << " m/s" << endl;
        cout << "  Launch Angle:     " << angle << " degrees" << endl;
        cout << "  Gravity:          " << gravity << " m/s²" << endl;
        
        cout << "\nCalculated Values:" << endl;
        cout << "  Range:            " << calculateRange() << " m" << endl;
        cout << "  Time of Flight:   " << calculateTimeOfFlight() << " s" << endl;
        cout << "  Maximum Height:   " << calculateMaxHeight() << " m" << endl;
        cout << string(50, '=') << endl;
    }
};

class Calculator {
private:
    Projectile projectile;
    
    void displayMenu() const {
        cout << "\n" << string(50, '=') << endl;
        cout << "      PROJECTILE MOTION CALCULATOR" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Enter new values and calculate" << endl;
        cout << "2. Display current results" << endl;
        cout << "3. Change gravity (default: 9.8 m/s²)" << endl;
        cout << "4. Exit" << endl;
        cout << string(50, '=') << endl;
        cout << "Choose an option: ";
    }
    
    void inputValues() {
        double v, a;
        
        cout << "\nEnter initial velocity (m/s): ";
        cin >> v;
        
        cout << "Enter launch angle (degrees, 0-90): ";
        cin >> a;
        
        // Input validation
        if (v < 0) {
            cout << "Velocity cannot be negative! Using absolute value." << endl;
            v = abs(v);
        }
        
        if (a < 0 || a > 90) {
            cout << "Angle should be between 0 and 90 degrees!" << endl;
            a = max(0.0, min(90.0, a));
            cout << "Adjusted to: " << a << " degrees" << endl;
        }
        
        projectile.setVelocity(v);
        projectile.setAngle(a);
        
        projectile.displayResults();
    }
    
    void changeGravity() {
        double g;
        cout << "\nEnter gravity value (m/s²): ";
        cin >> g;
        
        if (g <= 0) {
            cout << "Gravity must be positive! Using default 9.8 m/s²" << endl;
            g = 9.8;
        }
        
        projectile.setGravity(g);
        cout << "Gravity updated to: " << g << " m/s²" << endl;
    }

public:
    Calculator() : projectile(0, 0, 9.8) {}
    
    void run() {
        int choice;
        
        cout << "\n*** Welcome to Projectile Motion Calculator ***\n";
        
        do {
            displayMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nInvalid input! Please enter a number." << endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                    inputValues();
                    break;
                case 2:
                    if (projectile.getVelocity() == 0 && projectile.getAngle() == 0) {
                        cout << "\nNo values entered yet! Please use option 1 first." << endl;
                    } else {
                        projectile.displayResults();
                    }
                    break;
                case 3:
                    changeGravity();
                    break;
                case 4:
                    cout << "\nThank you for using Projectile Motion Calculator!" << endl;
                    break;
                default:
                    cout << "\nInvalid option! Please choose 1-4." << endl;
            }
            
        } while (choice != 4);
    }
};

int main() {
    Calculator calc;
    calc.run();
    
    return 0;
}
