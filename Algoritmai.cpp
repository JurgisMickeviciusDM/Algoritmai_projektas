#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <sstream>
#include <random>
#include <unordered_set>
#include <cctype>
#include <chrono>


int i = 0;
std::vector<int> num, lowpt, tevas, aplankyta;
std::set<int> arrtikuliacinisTaskas;
std::stack<std::pair<int, int>> S;
std::vector<std::vector<std::pair<int, int>>> dvigubai_jungios_komponentes;
std::vector<std::vector<int>> adjList;

bool ArSkaiciai(const std::string& eilute);
void PridetiBriauna(int u, int v, std::unordered_set<std::string>& egzistuojanciosBriaunos);
void DvigubaiJungikomponente(int v, int u);
bool ArRaidemis(const std::string& str);

bool ArSkaiciai(const std::string& eilute) {
    for (char simbolis : eilute) {
        if (!std::isdigit(simbolis) && !std::isspace(simbolis) && simbolis != '+' && simbolis != '-' && simbolis != '*' && simbolis != '/') {
            return false;
        }
    }
    return true;
}

bool ArRaidemis(const std::string& str) {
    std::istringstream iss(str);
    std::string edge;
    while (iss >> edge) {
        // Check if the edge is exactly one character and it's a letter
        if (edge.length() != 1 || !std::isalpha(edge[0])) {
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
    aplankyta[v] = 1;
    int vaikas = 0;

    for (int w : adjList[v]) {
        if (!aplankyta[w]) {
            vaikas++;
            S.push({ v, w });
            tevas[w] = v;
            DvigubaiJungikomponente(w, v);
            lowpt[v] = std::min(lowpt[v], lowpt[w]);

            if ((u != -1 && lowpt[w] >= num[v]) || (u == -1 && vaikas > 1)) {
                arrtikuliacinisTaskas.insert(v);
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
    std::chrono::duration<double, std::milli> autoDuration, manualDuration;


    while (true) {
        

        std::cout << "Pasirinkite: 1 - automatinis grafo generavimas, 2 - rankinis briaunu ivedimas ranka, 3-is failo: ";
        if (!(std::cin >> pasirinkimas)) {
            std::cout << "Neteisinga ivestis. Prasome ivesti skaiciu." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;  // Grįžtame į ciklo pradžią
        }

        if (pasirinkimas != 1 && pasirinkimas != 2) {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            continue;  // Grįžtame į ciklo pradžią, jei pasirinkimas yra neteisingas
        }

        if (pasirinkimas == 1) {
            std::cout << "Iveskite virsuniu skaiciu: ";
            while (!(std::cin >> n) || std::cin.get() != '\n') {
                std::cout << "Netinkama ivestis. Prasome ivesti skaiciu: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            bool inputIsValid = false;
            while (!inputIsValid) {
                std::cout << "Iveskite briaunu skaiciu: ";
                std::string m_input;
                std::cin >> m_input;

                if (ArSkaiciai(m_input)) {
                    m = std::stoi(m_input);
                    if (m < n - 1) {
                        std::cout << "Per mazai briaunu sukurti susijusiam grafui. Prasome ivesti didesni skaiciu.\n";
                    }
                    else if (m > n * (n - 1) / 2) {
                        std::cout << "Ivestas per didelis briaunu skaicius. Prasome ivesti mazesni skaiciu.\n";
                    }
                    else {
                        inputIsValid = true;
                    }
                }
                else {
                    std::cout << "Netinkama ivestis. Prasome ivesti skaiciu.\n";
                }
            }

            std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, n - 1);
            auto start = std::chrono::high_resolution_clock::now();


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
            auto end = std::chrono::high_resolution_clock::now();
            autoDuration = end - start;
        }

        else if (pasirinkimas == 2) {

            while (true) {
                std::cout << "Iveskite virsuniu skaiciu: ";
                if (!(std::cin >> n)) {
                    std::cout << "Netinkama ivestis. Prasome ivesti skaiciu: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    break; 
                }
            }

            adjList.resize(n);
            std::cin.ignore();

            adjList.resize(n);
            std::string briaunuEilute;
            bool validEdgeInput = false;
            int briaunuIvestis;

            while (!validEdgeInput) {
                std::cout << "Pasirinkite: 1 - ivesti briaunas raidemis, 2 - ivesti briaunas skaiciais: ";
                if (!(std::cin >> briaunuIvestis)) {
                    std::cout << "Netinkama ivestis. Prasome ivesti skaiciu: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (briaunuIvestis == 1) {
                    while (!validEdgeInput) {
                        std::cout << "Iveskite visas briaunas raidemis vienoje eiluteje (pvz: A B C D): ";
                        std::getline(std::cin >> std::ws, briaunuEilute); 

                        if (ArRaidemis(briaunuEilute)) {
                            validEdgeInput = true;
                        }
                        else {
                            std::cout << "Netinkama ivestis .\n";
                        }
                    }
                }
                else if (briaunuIvestis == 2) {
                    while (!validEdgeInput) {
                        std::cout << "Iveskite visas briaunas skaiciais vienoje eiluteje (pvz: 0 1 0 3 3 1): ";
                        std::getline(std::cin >> std::ws, briaunuEilute); 
                        if (ArSkaiciai(briaunuEilute)) {
                            validEdgeInput = true;
                        }
                        else {
                            std::cout << "Netinkama ivestis.\n";
                        }
                    }
                }
                else {
                    std::cout << "Neteisingas pasirinkimas. Prasome pasirinkti iš naujo." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            auto start = std::chrono::high_resolution_clock::now(); 

            std::istringstream iss(briaunuEilute);
            int u, v;
            while (iss >> u >> v) {
                PridetiBriauna(u, v, egzistuojanciosBriaunos);
            }
            auto end = std::chrono::high_resolution_clock::now(); 
            manualDuration = end - start;
        }
        else {
            std::cout << "Neteisingas pasirinkimas." << std::endl;
            return 1;
        }

        num.assign(n, 0);
        lowpt.assign(n, 0);
        tevas.assign(n, -1);
        aplankyta.assign(n, 0);
        arrtikuliacinisTaskas.clear();
        dvigubai_jungios_komponentes.clear();

        for (int v = 0; v < n; ++v) {
            if (!aplankyta[v]) {
                DvigubaiJungikomponente(v, -1);
            }
        }

        std::cout << "Pasirinkite: 1 - isvesti grafo duomenis raidemis, 2 - isvesti grafo duomenis skaiciais: ";
        int isvestiesPasirinkimas;
        std::cin >> isvestiesPasirinkimas;

        if (isvestiesPasirinkimas == 1) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : arrtikuliacinisTaskas) {
                std::cout << char('A' + ap) << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungios komponentes:\n";
            for (const auto& komponente : dvigubai_jungios_komponentes) {
                for (const auto& briauna : komponente) {
                    std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
                }
                std::cout << '\n';
            }
        }
        else if (isvestiesPasirinkimas == 2) {
            std::cout << "Artikuliaciniai taskai:\n";
            for (int ap : arrtikuliacinisTaskas) {
                std::cout << ap << " ";
            }
            std::cout << '\n';

            std::cout << "Dvigubai jungios komponentes:\n";
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
        if (pasirinkimas == 1) {
            std::cout << "Laikas: " << autoDuration.count() << " s\n";
        }
        else if (pasirinkimas == 2) {
            std::cout << "Laikas: " << manualDuration.count() << " s\n";
        }
        return 0;
    }
}