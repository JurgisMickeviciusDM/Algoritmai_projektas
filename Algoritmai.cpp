/*
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set> 

int i = 0;
std::vector<int> num, lowpt, tevas, visited; //lowpt yra mažiausia reikšmė 
std::set<int> articulationPoints; // Set to store articulation points
std::stack<std::pair<int, int>> S;
std::vector<std::vector<std::pair<int, int>>> dvigubai_jungios_komponentes;
std::vector<std::vector<int>> adjList;

void PridetiBriauna(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u); // For undirected graph
}

void DvigubaiJungikomponente(int v, int u) {
    int j = i++;
    num[v] = lowpt[v] = j;
    visited[v] = 1; // Mark as visited
    int children = 0; // Count of children in DFS Tree

    for (int w : adjList[v]) {
        if (!visited[w]) {
            children++;
            S.push({ v, w });
            tevas[w] = v;
            DvigubaiJungikomponente(w, v);
            lowpt[v] = std::min(lowpt[v], lowpt[w]);

            // Check if the current vertex is an articulation point
            if ((u != -1 && lowpt[w] >= num[v]) || (u == -1 && children > 1)) {
                articulationPoints.insert(v);
            }

            // If v is not root and lowpt value of one of its child is more
            // than discovery value of v.
            if (lowpt[w] >= num[v]) {
                std::vector<std::pair<int, int>> komponente;
                std::pair<int, int> briauna;
                do {
                    briauna = S.top();
                    S.pop();
                    komponente.push_back(briauna);
                } while (briauna != std::make_pair(v, w));
                dvigubai_jungios_komponentes.push_back(komponente);
            }
        }
        else if (w != u && num[w] < num[v]) {
            S.push({ v, w });
            lowpt[v] = std::min(lowpt[v], num[w]);
        }
    }
}

int main() {
    const int n = 10; // Number of vertices
    adjList.resize(n);
    num.assign(n, 0);
    lowpt.assign(n, 0);
    tevas.assign(n, -1);
    visited.assign(n, 0);

    // Add edges to the graph PridetiBriauna(2, 4);
    PridetiBriauna(2, 5);
    PridetiBriauna(4, 6);
    PridetiBriauna(5, 6);
    PridetiBriauna(9,7);
    PridetiBriauna(9, 8);
    PridetiBriauna(8, 7);
    PridetiBriauna(7,1);
    PridetiBriauna(1, 0);
    PridetiBriauna(1, 3);
    PridetiBriauna(0,2);
    PridetiBriauna(3,2);
   
    
    /*
    PridetiBriauna(6,8);
    PridetiBriauna(6,1);
    PridetiBriauna(1,8);
    PridetiBriauna(1,2);
    PridetiBriauna(1,4);
    PridetiBriauna(4,2);
    PridetiBriauna(4,5);
    PridetiBriauna(5,9);
    PridetiBriauna(9,3);
    PridetiBriauna(5,7);
    PridetiBriauna(3,5);
    PridetiBriauna(3,0);
    PridetiBriauna(0,5);
    PridetiBriauna(0,7);*/
    
/*
    // dvigubai jungios radimas
    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            DvigubaiJungikomponente(v, -1);
        }
    }

    // artikulaicinis taskas
    std::cout << "Taškas, kuriame atskyriamas grafas:\n";
    for (int ap : articulationPoints) {
        std::cout << char('A' + ap) << " ";
    }
    std::cout << '\n';

    // printas
    std::cout << "Atskirtų grafų kraštinės?????:\n";
    for (const auto& komponente : dvigubai_jungios_komponentes) {
        for (const auto& briauna : komponente) {
            std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
        }
        std::cout << '\n';
    }

    return 0;
}*/
/*
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <sstream>

int i = 0;
std::vector<int> num, lowpt, tevas, visited;
std::set<int> articulationPoints;
std::stack<std::pair<int, int>> S;
std::vector<std::vector<std::pair<int, int>>> dvigubai_jungios_komponentes;
std::vector<std::vector<int>> adjList;

void PridetiBriauna(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void DvigubaiJungikomponente(int v, int u) {
    int j = i++;
    num[v] = lowpt[v] = j;
    visited[v] = 1;
    int children = 0;

    for (int w : adjList[v]) {
        if (!visited[w]) {
            children++;
            S.push({ v, w });
            tevas[w] = v;
            DvigubaiJungikomponente(w, v);
            lowpt[v] = std::min(lowpt[v], lowpt[w]);

            if ((u != -1 && lowpt[w] >= num[v]) || (u == -1 && children > 1)) {
                articulationPoints.insert(v);
            }

            if (lowpt[w] >= num[v]) {
                std::vector<std::pair<int, int>> komponente;
                std::pair<int, int> briauna;
                do {
                    briauna = S.top();
                    S.pop();
                    komponente.push_back(briauna);
                } while (briauna != std::make_pair(v, w));
                dvigubai_jungios_komponentes.push_back(komponente);
            }
        }
        else if (w != u && num[w] < num[v]) {
            S.push({ v, w });
            lowpt[v] = std::min(lowpt[v], num[w]);
        }
    }
}
/*
int main() {
    int n, m, pasirinkimas;
    std::cout << "Pasirinkite: 1 - automatinis grafo generavimas, 2 - rankinis briaunų įvedimas: ";
    std::cin >> pasirinkimas;

    if (pasirinkimas == 1) {
        std::cout << "Įveskite viršūnių skaičių: ";
        std::cin >> n;
        std::cout << "Įveskite briaunų skaičių: ";
        std::cin >> m;
        adjList.resize(n);

        std::mt19937 rng(std::random_device{}()); // Atsitiktinių skaičių generatorius
        std::uniform_int_distribution<int> dist(0, n - 1); // Skirstymas tarp 0 ir n-1

        for (int i = 0; i < m; ++i) {
            int u = dist(rng);
            int v = dist(rng);
            PridetiBriauna(u, v);
            std::cout << "Pridėta briauna: " << u << " - " << v << std::endl;
        }
    }

    else if (pasirinkimas == 2) {
        std::cout << "Iveskite unikaliu virsuniu(SKAICIU), tarkime yra briaunos (a,b) (b,c) (c,a), tai reikia rasyti 3: ";
        std::cin >> n;
        adjList.resize(n);
        std::cin.ignore(); // Ignoruojamas paskutinis "Enter" iš ankstesnės įvesties

        std::string briaunuEilute;
        std::cout << "Įveskite visas briaunas vienoje eilutėje, atskirtas tarpais (pvz.: 6 8 6 9 9 8): ";
        std::getline(std::cin, briaunuEilute);

        std::istringstream iss(briaunuEilute);
        int u, v;
        while (iss >> u >> v) {
            PridetiBriauna(u, v);
        }
    }
    else {
        std::cout << "Neteisingas pasirinkimas." << std::endl;
        return 1;
    }

    num.assign(n, 0);
    lowpt.assign(n, 0);
    tevas.assign(n, -1);
    visited.assign(n, 0);

    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            DvigubaiJungikomponente(v, -1);
        }
    }

    std::cout << "Artikuliaciniai taškai:\n";
    for (int ap : articulationPoints) {
        std::cout << char('A' + ap) << " ";
    }
    std::cout << '\n';

    std::cout << "Dvigubai jungių komponentės:\n";
    for (const auto& komponente : dvigubai_jungios_komponentes) {
        for (const auto& briauna : komponente) {
            std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
        }
        std::cout << '\n';
    }

    return 0;
}*/



/// testiname su auto rezimu 

//geras kodas


/*
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <sstream>
#include <random>
#include <unordered_set>
#include <cctype>

int i = 0;
std::vector<int> num, lowpt, tevas, visited;
std::set<int> articulationPoints;
std::stack<std::pair<int, int>> S;
std::vector<std::vector<std::pair<int, int>>> dvigubai_jungios_komponentes;
std::vector<std::vector<int>> adjList;

bool ArSkaiciai(const std::string& eilute) {
    for (char simbolis : eilute) {
        if (!std::isdigit(simbolis) && !std::isspace(simbolis) && simbolis != '+' && simbolis != '-' && simbolis != '*' && simbolis != '/') {
            return false;
        }
    }
    return true;
}

void PridetiBriauna(int u, int v, std::unordered_set<std::string>& egzistuojanciosBriaunos) {
    std::string briauna = std::to_string(std::min(u, v)) + "-" + std::to_string(std::max(u, v));
    if (u != v && egzistuojanciosBriaunos.find(briauna) == egzistuojanciosBriaunos.end()) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        egzistuojanciosBriaunos.insert(briauna);
    }
}

void DvigubaiJungikomponente(int v, int u) {
    int j = i++;
    num[v] = lowpt[v] = j;
    visited[v] = 1;
    int children = 0;

    for (int w : adjList[v]) {
        if (!visited[w]) {
            children++;
            S.push({ v, w });
            tevas[w] = v;
            DvigubaiJungikomponente(w, v);
            lowpt[v] = std::min(lowpt[v], lowpt[w]);

            if ((u != -1 && lowpt[w] >= num[v]) || (u == -1 && children > 1)) {
                articulationPoints.insert(v);
            }

            if (lowpt[w] >= num[v]) {
                std::vector<std::pair<int, int>> komponente;
                std::pair<int, int> briauna;
                do {
                    briauna = S.top();
                    S.pop();
                    komponente.push_back(briauna);
                } while (briauna != std::make_pair(v, w));
                dvigubai_jungios_komponentes.push_back(komponente);
            }
        }
        else if (w != u && num[w] < num[v]) {
            S.push({ v, w });
            lowpt[v] = std::min(lowpt[v], num[w]);
        }
    }
}

*//*
int main() {
    int n, m, pasirinkimas;
    std::unordered_set<std::string> egzistuojanciosBriaunos;

    while (true) {
        std::cout << "Pasirinkite: 1 - automatinis grafo generavimas, 2 - rankinis briaunų įvedimas ranka: ";
        if (!(std::cin >> pasirinkimas)) {
            std::cout << "Neteisinga įvestis. Prašome įvesti skaičių." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;  // Grįžtame į ciklo pradžią
        }

        if (pasirinkimas != 1 && pasirinkimas != 2) {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            continue;  // Grįžtame į ciklo pradžią, jei pasirinkimas yra neteisingas
        }

        if (pasirinkimas == 1) {
            std::cout << "Įveskite viršūnių skaičių: ";
            while (!(std::cin >> n) || std::cin.get() != '\n') {
                std::cout << "Netinkama įvestis. Prašome įvesti skaičių: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            bool inputIsValid = false;
            while (!inputIsValid) {
                std::cout << "Įveskite briaunų skaičių: ";
                std::string m_input;
                std::cin >> m_input;

                if (ArSkaiciai(m_input)) {
                    m = std::stoi(m_input);
                    if (m < n - 1) {
                        std::cout << "Per mažai briaunų sukurti susijusiam grafui. Prašome įvesti didesnį skaičių.\n";
                    }
                    else if (m > n * (n - 1) / 2) {
                        std::cout << "Įvestas per didelis briaunų skaičius. Prašome įvesti mažesnį skaičių.\n";
                    }
                    else {
                        inputIsValid = true;
                    }
                }
                else {
                    std::cout << "Netinkama įvestis. Prašome įvesti skaičių.\n";
                }
            }

            std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, n - 1);

            adjList.resize(n);
            egzistuojanciosBriaunos.clear();

            for (int i = 0; i < m; ++i) {
                int u, v;
                do {
                    u = dist(rng);
                    v = dist(rng);
                } while (u == v || egzistuojanciosBriaunos.count(std::to_string(std::min(u, v)) + "-" + std::to_string(std::max(u, v))));

                PridetiBriauna(u, v, egzistuojanciosBriaunos);
            }
        }

        else if (pasirinkimas == 2) {
            std::cout << "Įveskite viršūnių skaičių: ";
            while (!(std::cin >> n) || std::cin.fail()) {
                std::cout << "Netinkama įvestis. Prašome įvesti skaičių: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore();

            std::string briaunuEilute;
            std::cout << "Pasirinkite: 1 - įvesti briaunas raidėmis, 2 - įvesti briaunas skaičiais: ";
            int briaunuIvestis;
            std::cin >> briaunuIvestis;

            if (briaunuIvestis == 1) {
                std::cout << "Įveskite visas briaunas raidėmis vienoje eilutėje, atskirtas tarpais (pvz.: A B C D): ";
                std::cin.ignore();
                std::getline(std::cin, briaunuEilute);
            }
            else if (briaunuIvestis == 2) {
                std::cout << "Įveskite visas briaunas skaičiais vienoje eilutėje, atskirtas tarpais (pvz.: 0 1 2 3 4): ";
                std::cin.ignore();
                std::getline(std::cin, briaunuEilute);

                if (!ArSkaiciai(briaunuEilute)) {
                    std::cout << "Netinkama įvestis. Prašome įvesti skaičius.\n";
                    return 1;
                }
            }
            else {
                std::cout << "Neteisingas pasirinkimas." << std::endl;
                return 1;
            }

            std::istringstream iss(briaunuEilute);
            int u, v;
            while (iss >> u >> v) {
                PridetiBriauna(u, v, egzistuojanciosBriaunos);
            }
        }
        else {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            return 1;
        }

        num.assign(n, 0);
        lowpt.assign(n, 0);
        tevas.assign(n, -1);
        visited.assign(n, 0);

        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                DvigubaiJungikomponente(v, -1);
            }
        }

        std::cout << "Pasirinkite: 1 - isvesti grafo duomenis raidemis, 2 - isvesti grafo duomenis skaiciais: ";
        int isvestiesPasirinkimas;

        while (!(std::cin >> isvestiesPasirinkimas) || std::cin.fail() || (isvestiesPasirinkimas != 1 && isvestiesPasirinkimas != 2)) {
            std::cout << "Neteisinga įvestis. Prašome įvesti 1 arba 2: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (isvestiesPasirinkimas == 1) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : articulationPoints) {
                std::cout << char('A' + ap) << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungių komponentes:\n";
            for (const auto& komponente : dvigubai_jungios_komponentes) {
                for (const auto& briauna : komponente) {
                    std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
                }
                std::cout << '\n';
            }
        }
        else if (isvestiesPasirinkimas == 2) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : articulationPoints) {
                std::cout << ap << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungių komponentes:\n";
            for (const auto& komponente : dvigubai_jungios_komponentes) {
                for (const auto& briauna : komponente) {
                    std::cout << "(" << briauna.first << ", " << briauna.second << ") ";
                }
                std::cout << '\n';
            }
        }
        else {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            return 1;
        }

        return 0;
    }
}

*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <sstream>
#include <random>
#include <unordered_set>
#include <cctype>

int i = 0;
std::vector<int> num, lowpt, tevas, visited;
std::set<int> articulationPoints;
std::stack<std::pair<int, int>> S;
std::vector<std::vector<std::pair<int, int>>> dvigubai_jungios_komponentes;
std::vector<std::vector<int>> adjList;

bool ArSkaiciai(const std::string& eilute) {
    for (char simbolis : eilute) {
        if (!std::isdigit(simbolis) && !std::isspace(simbolis) && simbolis != '+' && simbolis != '-' && simbolis != '*' && simbolis != '/') {
            return false;
        }
    }
    return true;
}

void PridetiBriauna(int u, int v, std::unordered_set<std::string>& egzistuojanciosBriaunos) {
    std::string briauna = std::to_string(std::min(u, v)) + "-" + std::to_string(std::max(u, v));
    if (u != v && egzistuojanciosBriaunos.find(briauna) == egzistuojanciosBriaunos.end()) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        egzistuojanciosBriaunos.insert(briauna);
    }
}

void DvigubaiJungikomponente(int v, int u) {
    int j = i++;
    num[v] = lowpt[v] = j;
    visited[v] = 1;
    int children = 0;

    for (int w : adjList[v]) {
        if (!visited[w]) {
            children++;
            S.push({ v, w });
            tevas[w] = v;
            DvigubaiJungikomponente(w, v);
            lowpt[v] = std::min(lowpt[v], lowpt[w]);

            if ((u != -1 && lowpt[w] >= num[v]) || (u == -1 && children > 1)) {
                articulationPoints.insert(v);
            }

            if (lowpt[w] >= num[v]) {
                std::vector<std::pair<int, int>> komponente;
                std::pair<int, int> briauna;
                do {
                    briauna = S.top();
                    S.pop();
                    komponente.push_back(briauna);
                } while (briauna != std::make_pair(v, w));
                dvigubai_jungios_komponentes.push_back(komponente);
            }
        }
        else if (w != u && num[w] < num[v]) {
            S.push({ v, w });
            lowpt[v] = std::min(lowpt[v], num[w]);
        }
    }
}

int main() {
    int n, m, pasirinkimas;
    std::unordered_set<std::string> egzistuojanciosBriaunos;

    while (true) {
        std::cout << "Pasirinkite: 1 - automatinis grafo generavimas, 2 - rankinis briaunų įvedimas ranka: ";
        if (!(std::cin >> pasirinkimas)) {
            std::cout << "Neteisinga įvestis. Prašome įvesti skaičių." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;  // Grįžtame į ciklo pradžią
        }

        if (pasirinkimas != 1 && pasirinkimas != 2) {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            continue;  // Grįžtame į ciklo pradžią, jei pasirinkimas yra neteisingas
        }

        if (pasirinkimas == 1) {
            std::cout << "Įveskite viršūnių skaičių: ";
            while (!(std::cin >> n) || std::cin.get() != '\n') {
                std::cout << "Netinkama įvestis. Prašome įvesti skaičių: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            bool inputIsValid = false;
            while (!inputIsValid) {
                std::cout << "Įveskite briaunų skaičių: ";
                std::string m_input;
                std::cin >> m_input;

                if (ArSkaiciai(m_input)) {
                    m = std::stoi(m_input);
                    if (m < n - 1) {
                        std::cout << "Per mažai briaunų sukurti susijusiam grafui. Prašome įvesti didesnį skaičių.\n";
                    }
                    else if (m > n * (n - 1) / 2) {
                        std::cout << "Įvestas per didelis briaunų skaičius. Prašome įvesti mažesnį skaičių.\n";
                    }
                    else {
                        inputIsValid = true;
                    }
                }
                else {
                    std::cout << "Netinkama įvestis. Prašome įvesti skaičių.\n";
                }
            }

            std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, n - 1);


            adjList.resize(n);
            egzistuojanciosBriaunos.clear();

            for (int i = 0; i < m; ++i) {
                int u, v;
                do {
                    u = dist(rng);
                    v = dist(rng);
                } while (u == v || egzistuojanciosBriaunos.count(std::to_string(std::min(u, v)) + "-" + std::to_string(std::max(u, v))));

                PridetiBriauna(u, v, egzistuojanciosBriaunos);
            }
        }

        else if (pasirinkimas == 2) {
            std::cout << "Įveskite viršūnių skaičių: ";
            std::cin >> n;
            adjList.resize(n);
            std::cin.ignore();

            std::string briaunuEilute;
            std::cout << "Pasirinkite: 1 - įvesti briaunas raidėmis, 2 - įvesti briaunas skaičiais: ";
            int briaunuIvestis;
            std::cin >> briaunuIvestis;

            if (briaunuIvestis == 1) {
                std::cout << "Įveskite visas briaunas raidėmis vienoje eilutėje, atskirtas tarpais (pvz.: A B C D): ";
                std::cin.ignore();
                std::getline(std::cin, briaunuEilute);
            }
            else if (briaunuIvestis == 2) {
                std::cout << "Įveskite visas briaunas skaičiais vienoje eilutėje, atskirtas tarpais (pvz.: 0 1 2 3 4): ";
                std::cin.ignore();
                std::getline(std::cin, briaunuEilute);

                if (!ArSkaiciai(briaunuEilute)) {
                    std::cout << "Netinkama įvestis. Prašome įvesti skaičius.\n";
                    return 1;
                }
            }
            else {
                std::cout << "Neteisingas pasirinkimas." << std::endl;
                return 1;
            }

            std::istringstream iss(briaunuEilute);
            int u, v;
            while (iss >> u >> v) {
                PridetiBriauna(u, v, egzistuojanciosBriaunos);
            }
        }
        else {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            return 1;
        }

        num.assign(n, 0);
        lowpt.assign(n, 0);
        tevas.assign(n, -1);
        visited.assign(n, 0);

        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                DvigubaiJungikomponente(v, -1);
            }
        }

        std::cout << "Pasirinkite: 1 - isvesti grafo duomenis raidemis, 2 - isvesti grafo duomenis skaiciais: ";
        int isvestiesPasirinkimas;
        std::cin >> isvestiesPasirinkimas;

        if (isvestiesPasirinkimas == 1) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : articulationPoints) {
                std::cout << char('A' + ap) << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungių komponentes:\n";
            for (const auto& komponente : dvigubai_jungios_komponentes) {
                for (const auto& briauna : komponente) {
                    std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
                }
                std::cout << '\n';
            }
        }
        else if (isvestiesPasirinkimas == 2) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : articulationPoints) {
                std::cout << ap << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungių komponentes:\n";
            for (const auto& komponente : dvigubai_jungios_komponentes) {
                for (const auto& briauna : komponente) {
                    std::cout << "(" << briauna.first << ", " << briauna.second << ") ";
                }
                std::cout << '\n';
            }
        }
        else {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            return 1;
        }

        return 0;
    }
}