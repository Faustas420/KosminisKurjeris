#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

// ================== STRUCT: ROUTE ==================
struct Route {
    string to;
    int fuelCost;
    int riskPercent;
    int bonusFuel;
    Route(string t, int f, int r, int bonus = 0)
        : to(t), fuelCost(f), riskPercent(r), bonusFuel(bonus) {}
};

// ================== CLASS: PLANET ==================
class Planet {
private:
    string name;
    bool station;
    vector<Route> routes;
public:
    Planet(string n, bool s = false) : name(n), station(s) {}
    const string& getName() const { return name; }
    bool hasStation() const { return station; }
    vector<Route>& getRoutes() { return routes; }
    void addRoute(const string& dest, int f, int r, int bonus = 0) {
        routes.push_back(Route(dest, f, r, bonus));
    }
};

// ================== CLASS: PLAYER ==================
class Player {
private:
    int fuel;
    bool cargo;
    bool insured;
    string pos;
public:
    Player(int f, string p) : fuel(f), cargo(true), insured(false), pos(p) {}
    int getFuel() const { return fuel; }
    void consumeFuel(int x) { fuel = max(0, fuel - x); }
    bool hasCargo() const { return cargo; }
    void loseCargo() { cargo = false; }
    bool isInsured() const { return insured; }
    void insureCargo() { insured = true; }
    void useInsurance() { insured = false; }
    const string& getPosition() const { return pos; }
    void moveTo(const string& p) { pos = p; }
    void refuel(int amount) { fuel += amount; }
};

// ================== CLASS: EVENTS ==================
class Event {
public:
    virtual void trigger(Player& p) = 0;
    virtual ~Event() {}
};

class PiratesEvent : public Event {
public:
    void trigger(Player& p) override {
        cout << "\n[PIRATES] Your cargo was attacked!\n";
        if (p.isInsured()) {
            cout << "Insurance activated - cargo is safe.\n";
            p.useInsurance();
        }
        else {
            cout << "Cargo stolen!\n";
            p.loseCargo();
        }
    }
};

class StormEvent : public Event {
public:
    void trigger(Player& p) override {
        cout << "\n[STORM] You lost 90 fuel.\n";
        p.consumeFuel(90);
    }
};

class LeakEvent : public Event {
public:
    void trigger(Player& p) override {
        cout << "\n[FUEL LEAK] You lost 70 fuel.\n";
        p.consumeFuel(70);
    }
};

class NavigationErrorEvent : public Event {
public:
    void trigger(Player& p) override {
        cout << "\n[NAVIGATION ERROR]\n";
        int outcome = rand() % 3;
        if (outcome == 0) {
            cout << "You drifted back to Earth. Lost 50 fuel.\n";
            p.consumeFuel(50);
            p.moveTo("Earth");
        }
        else if (outcome == 1) {
            cout << "You got lost in space. Lost 120 fuel.\n";
            p.consumeFuel(120);
        }
        else {
            cout << "You hit asteroids. Lost 80 fuel.\n";
            p.consumeFuel(80);
        }
    }
};

// ================== CLASS: MAP ==================
class Map {
private:
    vector<Planet> planets;
    string goal;
public:
    Map(int difficulty) {
        if (difficulty == 1) easyMap();
        else if (difficulty == 2) mediumMap();
        else hardMap();
    }

    vector<Planet>& getPlanets() { return planets; }
    const string& getGoal() const { return goal; }

    Planet* getPlanet(const string& name) {
        for (auto& p : planets)
            if (p.getName() == name) return &p;
        return nullptr;
    }

    void printMap(const string& playerPos) {
        cout << "\n--------------------------------------------\n";
        cout << "SPACE MAP\n";
        cout << "--------------------------------------------\n\n";

        if (planets.size() == 6) { // EASY
            cout << "Earth - Venus - Mars - Asteroids - Jupiter - Neptune (Goal)\n";
            cout << "Extra routes: Earth–Jupiter, Asteroids–Neptune (+300 fuel)\n";
        }
        else if (goal == "Pluto") { // MEDIUM
            cout << "Earth - Moon - Mars - Phobos - Jupiter - Europa - Saturn - Titan - Pluto (Goal)\n";
            cout << "Extra routes: Moon–Europa, Jupiter–Titan (+250 fuel)\n";
        }
        else { // HARD
            cout << "Sun - Mercury - Venus - Earth - Mars - Centaurs - Uranus - Neptune - Kuiper Belt (Goal)\n";
            cout << "Extra routes: Earth–Uranus, Centaurs–Kuiper Belt (+400 fuel)\n";
        }

        cout << "\n--------------------------------------------\n\n";
    }

private:
    int findIdx(const string& name) {
        for (int i = 0; i < planets.size(); i++)
            if (planets[i].getName() == name) return i;
        return -1;
    }

    void addRoute(const string& a, const string& b, int fuel, int risk, int bonus = 0) {
        planets[findIdx(a)].addRoute(b, fuel, risk, bonus);
        planets[findIdx(b)].addRoute(a, fuel, risk, bonus);
    }

    void easyMap() {
        planets = { {"Earth", true}, {"Venus"}, {"Mars"}, {"Asteroids"}, {"Jupiter", true}, {"Neptune"} };
        goal = "Neptune";
        addRoute("Earth", "Venus", 40, 10);
        addRoute("Venus", "Mars", 50, 15);
        addRoute("Mars", "Asteroids", 60, 20);
        addRoute("Asteroids", "Jupiter", 100, 25);
        addRoute("Jupiter", "Neptune", 120, 20);
        addRoute("Earth", "Jupiter", 180, 30);
        addRoute("Asteroids", "Neptune", 200, 50, 300);
    }

    void mediumMap() {
        planets = { {"Earth", true},{"Moon"},{"Mars"},{"Phobos"},{"Jupiter"},{"Europa"},{"Saturn"},{"Titan"},{"Pluto"} };
        goal = "Pluto";
        addRoute("Earth", "Moon", 30, 5);
        addRoute("Moon", "Mars", 80, 15);
        addRoute("Mars", "Phobos", 40, 20);
        addRoute("Phobos", "Jupiter", 120, 30);
        addRoute("Jupiter", "Europa", 70, 25);
        addRoute("Europa", "Saturn", 140, 35);
        addRoute("Saturn", "Titan", 90, 30);
        addRoute("Titan", "Pluto", 200, 50);
        addRoute("Moon", "Europa", 180, 40);
        addRoute("Jupiter", "Titan", 160, 35, 250);
    }

    void hardMap() {
        planets = { {"Sun", true},{"Mercury"},{"Venus",true},{"Earth"},{"Mars"},{"Centaurs"},{"Uranus",true},{"Neptune"},{"Kuiper Belt"} };
        goal = "Kuiper Belt";
        addRoute("Sun", "Mercury", 40, 15);
        addRoute("Mercury", "Venus", 60, 20);
        addRoute("Venus", "Earth", 80, 25);
        addRoute("Earth", "Mars", 100, 30);
        addRoute("Mars", "Centaurs", 160, 40);
        addRoute("Centaurs", "Uranus", 180, 45);
        addRoute("Uranus", "Neptune", 150, 50);
        addRoute("Neptune", "Kuiper Belt", 220, 60);
        addRoute("Earth", "Uranus", 320, 55);
        addRoute("Centaurs", "Kuiper Belt", 300, 70, 400);
    }
};

// ================== CLASS: GAME ==================
class Game {
private:
    Player player{ 0, "" };
    Map map;
    vector<unique_ptr<Event>> events;
    int moves = 0;
public:
    Game(int difficulty) : map(difficulty) {
        if (difficulty == 1) player = Player(700, "Earth");
        else if (difficulty == 2) player = Player(600, "Earth");
        else player = Player(600, "Sun");

        events.push_back(make_unique<PiratesEvent>());
        events.push_back(make_unique<StormEvent>());
        events.push_back(make_unique<LeakEvent>());
        events.push_back(make_unique<NavigationErrorEvent>());
    }

    void run() {
        cout << "\n=== CARGO DELIVERY ===\n";
        cout << "Goal: Reach the final planet in as few moves as possible.\n";
        cout << "Controls: Enter route number.\n";
        cout << "0 = Map | 9 = Quit\n";

        while (true) {
            map.printMap(player.getPosition());
            showStatus();

            if (!player.hasCargo()) { cout << "\nCargo lost - Game Over!\n"; break; }
            if (player.getFuel() <= 0) { cout << "\nFuel depleted - Game Over!\n"; break; }
            if (player.getPosition() == map.getGoal()) {
                cout << "\nGoal reached in " << moves << " moves!\n";
                break;
            }

            Planet* cur = map.getPlanet(player.getPosition());
            showRoutes(*cur);

            int choice;
            cout << "Choose: ";
            cin >> choice;

            if (choice == 0) { map.printMap(player.getPosition()); continue; }
            if (choice == 9) { cout << "Exiting game.\n"; break; }
            if (choice < 1 || choice >(int)cur->getRoutes().size()) {
                cout << "Invalid choice!\n"; continue;
            }

            Route& r = cur->getRoutes()[choice - 1];
            if (player.getFuel() < r.fuelCost) {
                cout << "Not enough fuel!\n"; continue;
            }

            // FLIGHT
            player.consumeFuel(r.fuelCost);
            moves++;
            cout << "\nFlying to " << r.to << " (risk: " << r.riskPercent << "%)\n";

            if (rand() % 100 < r.riskPercent) {
                cout << "A dangerous event occurred!\n";
                int idx = rand() % events.size();
                events[idx]->trigger(player);
            }
            else {
                cout << "Flight successful.\n";
            }

            player.moveTo(r.to);

            // STATION
            Planet* newCur = map.getPlanet(player.getPosition());
            if (newCur && newCur->hasStation()) {
                cout << "\nYou landed at a space station. +200 fuel.\n";
                player.refuel(200);

                if (player.getFuel() >= 100 && !player.isInsured()) {
                    cout << "Do you want to insure your cargo for 100 fuel? (1 = yes, 0 = no): ";
                    int a; cin >> a;
                    if (a == 1 && player.getFuel() >= 100) {
                        player.consumeFuel(100);
                        player.insureCargo();
                        cout << "Cargo insured.\n";
                    }
                }
            }

            if (r.bonusFuel > 0) {
                cout << "Bonus fuel: +" << r.bonusFuel << "\n";
                player.refuel(r.bonusFuel);
            }
            cout << endl;
        }

        cout << "\nGame over. Thanks, Captain!\n";
    }

private:
    void showStatus() {
        cout << "\nSTATUS:\n";
        cout << "Planet: " << player.getPosition() << "\n";
        cout << "Fuel: " << player.getFuel()
            << " | Cargo: " << (player.hasCargo() ? "Yes" : "No")
            << " | Insurance: " << (player.isInsured() ? "Yes" : "No")
            << " | Moves: " << moves << "\n\n";
    }

    void showRoutes(Planet& p) {
        cout << "Available routes:\n";
        int i = 1;
        for (auto& r : p.getRoutes()) {
            cout << i++ << ". " << r.to
                << " -> Fuel: " << r.fuelCost
                << " | Risk: " << r.riskPercent << "%";
            if (r.bonusFuel > 0) cout << " | Bonus: +" << r.bonusFuel;
            if (player.getFuel() < r.fuelCost) cout << " (Not enough fuel)";
            cout << "\n";
        }
        cout << "\n0. Map | 9. Quit\n\n";
    }
};

// ================== MAIN ==================
int main() {
    srand((unsigned)time(nullptr));

    int diff;
    cout << "Select difficulty:\n";
    cout << "1 = Easy | 2 = Medium | 3 = Hard\n";
    cout << "-> ";
    cin >> diff;
    if (diff < 1 || diff > 3) diff = 1;

    Game game(diff);
    game.run();

    return 0;
}
