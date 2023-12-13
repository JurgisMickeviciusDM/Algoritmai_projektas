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
#include <fstream>


int i = 0;
std::vector<int> numeris, low_taskas, tevas, aplankyta;
std::set<int> NutrukimoTaskas;
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
    int j = i++; //eiles numeris
    numeris[v] = low_taskas[v] = j; //numeris paieškos gilyn
    aplankyta[v] = 1; //aplankymas žymimas
    int vaikas = 0;

    for (int w : adjList[v]) {//eis per visas virsunes
        if (!aplankyta[w]) { 
            vaikas++;
            S.push({ v, w });//pridedame į steką pora
            tevas[w] = v;  //nustatome teva, kaip virsune
            DvigubaiJungikomponente(w, v); // v nustatomas kaip w tėvas
            low_taskas[v] = std::min(low_taskas[v], low_taskas[w]);//nustatome mažiausią reikšmę

            if ((u != -1 && low_taskas[w] >= numeris[v]) || (u == -1 && vaikas > 1)) {
                NutrukimoTaskas.insert(v);//nutrūkimo taško tikrinimas, jei u=-1..., ar v DFS šaknis ir ar yra vaikas daugiau negu 1

            }

            if (low_taskas[w] >= numeris[v]) {
                std::vector<std::pair<int, int>> komponente;
                std::pair<int, int> briauna;
                do {// iš steko visos briaunos,kurios dvigubai jungios, kol prieiname (v,w)
                    briauna = S.top();
                    S.pop();// iš steko šaliname briaunas
                    komponente.push_back(briauna);
                } while (briauna != std::make_pair(v, w));
                dvigubai_jungios_komponentes.push_back(komponente);// pridedame prie komponente
            }
        }
        else if (w != u && numeris[w] < numeris[v]) {
            S.push({ v, w }); // jei w yra galinė briauna ne tėvas v, tai  į steką įdedame
            low_taskas[v] = std::min(low_taskas[v], numeris[w]);// atnaujiname lowpt reikšmę
        }
    }
}

int komponenciuskaicius = 0;

int main() {
    int n, m, pasirinkimas;
    std::unordered_set<std::string> egzistuojanciosBriaunos;
    std::chrono::duration<double, std::milli> autolaikas, rankalaikas, failoskaitymotrukme;


    while (true) {


        while (true) {
            std::cout << "Pasirinkite: 1 - automatinis grafo generavimas, 2 - rankinis briaunu ivedimas ranka, 3 - is failo: ";
            if (!(std::cin >> pasirinkimas)) {
                std::cout << "Neteisinga ivestis. Prasome ivesti skaiciu." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (pasirinkimas < 1 || pasirinkimas > 3) {
                std::cout << "Neteisingas pasirinkimas." << std::endl;
                continue;
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
                auto startas1 = std::chrono::high_resolution_clock::now();


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
                auto pabaiga1 = std::chrono::high_resolution_clock::now();
                autolaikas = pabaiga1 - startas1;
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

                auto startas2 = std::chrono::high_resolution_clock::now();

                std::istringstream iss(briaunuEilute);
                int u, v;
                while (iss >> u >> v) {
                    PridetiBriauna(u, v, egzistuojanciosBriaunos);
                }
                auto pabaiga2 = std::chrono::high_resolution_clock::now();
                rankalaikas = pabaiga2 - startas2;
            }

            else if (pasirinkimas == 3) {
                std::ifstream file("grafas.txt");
                if (!file) {
                    std::cerr << "Nepavyko atidaryti failo." << std::endl;
                    continue;
                }

                std::cout << "Iveskite virsuniu skaiciu: ";
                if (!(std::cin >> n)) {
                    std::cout << "Netinkama ivestis. Prasome ivesti skaiciu: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                adjList.resize(n);
                egzistuojanciosBriaunos.clear();

                std::string line;
                auto startas3 = std::chrono::high_resolution_clock::now();
                while (std::getline(file, line)) {
                    std::istringstream iss(line);
                    int u, v;
                    while (iss >> u >> v) {
                        PridetiBriauna(u, v, egzistuojanciosBriaunos);
                    }
                }
                auto pabaiga3 = std::chrono::high_resolution_clock::now();
                failoskaitymotrukme = pabaiga3 - startas3;
                file.close();
            }


            else {
                std::cout << "Neteisingas pasirinkimas." << std::endl;
                return 1;
            }

            auto Pradzia = std::chrono::high_resolution_clock::now();
            numeris.assign(n, 0);
            low_taskas.assign(n, 0);
            tevas.assign(n, -1);
            aplankyta.assign(n, 0);
            NutrukimoTaskas.clear();
            dvigubai_jungios_komponentes.clear();

            for (int v = 0; v < n; ++v) {
                if (!aplankyta[v]) {
                    DvigubaiJungikomponente(v, -1);
                }
            }
            auto Pabaiga = std::chrono::high_resolution_clock::now(); // Baigti matuoti laiką
            std::chrono::duration<double, std::milli> Laikas = Pabaiga - Pradzia;

            


           std::cout << "Pasirinkite: 1 - isvesti grafo duomenis raidemis, 2 - isvesti grafo duomenis skaiciais: ";
            int isvestiesPasirinkimas;
            std::cin >> isvestiesPasirinkimas;
           
            if (isvestiesPasirinkimas == 1) {
                std::cout << "Nutrukimo taskai:\n";
                std::cout << "Gavome " << NutrukimoTaskas.size() << " taskus: ";
                for (int ap : NutrukimoTaskas) {
                    std::cout << char('A' + ap) << " ";
                }
                std::cout << '\n';

                std::cout << "Dvigubai jungios komponentes " << dvigubai_jungios_komponentes.size() << ":\n";
                int komponenciuskaicius = 0;
                for (const auto& komponente : dvigubai_jungios_komponentes) {
                    komponenciuskaicius++;
                    std::cout << komponenciuskaicius << ": ";
                    for (const auto& briauna : komponente) {
                        std::cout << "(" << char('A' + briauna.first) << ", " << char('A' + briauna.second) << ") ";
                    }
                    std::cout << '\n';
                }
            }
            else if (isvestiesPasirinkimas == 2) {
                std::cout << "Nutrukimo taskai:\n";
                std::cout << "Gavome " << NutrukimoTaskas.size() << " taskus: ";
                for (int ap : NutrukimoTaskas) {
                    std::cout << ap << " ";
                }
                std::cout << '\n';

                std::cout << "Dvigubai jungios komponentes " << dvigubai_jungios_komponentes.size() << ":\n";
                int komponenciuskaicius = 0;
                for (const auto& komponente : dvigubai_jungios_komponentes) {
                    komponenciuskaicius++;
                    std::cout << komponenciuskaicius << ": ";
                    for (const auto& briauna : komponente) {
                        std::cout << "(" << briauna.first << ", " << briauna.second << ") ";
                    }
                    std::cout << '\n';
                    
                }
            }
            std::cout << "Laikas: " << Laikas.count() << " sekundziu\n";
            
            

            return 0;
        }
    }
}