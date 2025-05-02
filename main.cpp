#include <iostream>
#include <string>
#include <map>
#include <memory> // 💡 smart pointer için şart
#include <limits>
#include <vector>
#include <algorithm>

enum class Oncelik { Dusuk, Orta, Yuksek };

class Task {
private:
    std::string name;
    int id;
    bool is_completed;
    Oncelik onem;

public:
    Task() {
        id = 0;
        name = "";
        is_completed = false;
    }

    Task(int id_, std::string name_, Oncelik onem_) {
        name = name_;
        id = id_;
        is_completed = false;
        onem = onem_;
    }

    void complete() {
        is_completed = true;
    }

    bool isCompleted() const {
        return is_completed;
    }

    std::string getName() const {
        return name;
    }

    void display() const {
        std::cout << "id: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "is completed?: " << (is_completed ? "tamamlandi" : "tamamlanmadi") << std::endl;
        std::cout << "Oncelik: ";
        switch (onem) {
            case Oncelik::Dusuk: std::cout << "Dusuk"; break;
            case Oncelik::Orta: std::cout << "Orta"; break;
            case Oncelik::Yuksek: std::cout << "Yuksek"; break;
        }
        std::cout << std::endl;
    }
};

void findTaskByName(const std::map<int, std::shared_ptr<Task>>& gorevler, const std::string& arananisim) {
    bool bulundu = false;
    for (const auto& eleman : gorevler) {
        const auto& gorev = eleman.second;
        if (gorev->getName() == arananisim) {
            gorev->display();
            bulundu = true;
        }
    }
    if (!bulundu) {
        std::cout << "Bu isimde bir gorev bulunamadi." << std::endl;
    }
}

int sayCompletedTasks(const std::map<int, std::shared_ptr<Task>>& gorevler) {
    return std::count_if(gorevler.begin(), gorevler.end(), [](const auto& eleman) {
        return eleman.second->isCompleted();
    });
}

void listeleIsmeGore(const std::map<int, std::shared_ptr<Task>>& gorevler) {
    std::vector<std::shared_ptr<Task>> kopya;
    for (const auto& eleman : gorevler) {
        kopya.push_back(eleman.second);
    }

    std::sort(kopya.begin(), kopya.end(), [](const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) {
        return a->getName() < b->getName();
    });

    std::cout << "--- İsme Göre Sıralı Görevler ---" << std::endl;
    for (const auto& g : kopya) {
        g->display();
    }
}

int main() {
    std::map<int, std::shared_ptr<Task>> mapim;
    int counter = 1;
    int secim;

    do {
        std::cout << "\n1: Gorev Ekle\n2: Listele\n3: Cikis\n4: Gorev Tamamla\n5: Gorev Sil\n6: Isimle Ara\n7: İsme Gore Sirala\n8: Tamamlanan Sayisi\nSeciminiz: ";
        std::cin >> secim;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Gecerli bir sayi giriniz!" << std::endl;
            continue;
        }

        if (secim == 1) {
            std::string name_;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Gorev adi giriniz: ";
            std::getline(std::cin, name_);

            int oncelikSecim;
            std::cout << "Oncelik secin (0: Dusuk, 1: Orta, 2: Yuksek): ";
            std::cin >> oncelikSecim;

            Oncelik oncelik;
            if (oncelikSecim == 0) oncelik = Oncelik::Dusuk;
            else if (oncelikSecim == 1) oncelik = Oncelik::Orta;
            else oncelik = Oncelik::Yuksek;

            auto gorev = std::make_shared<Task>(counter, name_, oncelik);
            mapim[counter] = gorev;
            counter++;
        }

        else if (secim == 2) {
            for (auto& index : mapim) {
                index.second->display();
            }
        }

        else if (secim == 3) {
            std::cout << "Programdan cikiliyor." << std::endl;
            break;
        }

        else if (secim == 4) {
            int id;
            std::cout << "Tamamlanacak gorevin ID'si: ";
            std::cin >> id;
            if (mapim.find(id) != mapim.end()) {
                mapim[id]->complete();
                std::cout << "Gorev tamamlandi!" << std::endl;
            } else {
                std::cout << "Bu ID'ye sahip bir gorev bulunamadi!" << std::endl;
            }
        }

        else if (secim == 5) {
            int id;
            std::cout << "Silinecek gorevin ID'si: ";
            std::cin >> id;
            if (mapim.erase(id)) {
                std::cout << "Gorev silindi!" << std::endl;
            } else {
                std::cout << "Bu ID'ye sahip bir gorev bulunamadi!" << std::endl;
            }
        }

        else if (secim == 6) {
            std::string isim;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Gorev adi giriniz: ";
            std::getline(std::cin, isim);
            findTaskByName(mapim, isim);
        }

        else if (secim == 7) {
            listeleIsmeGore(mapim);
        }

        else if (secim == 8) {
            int adet = sayCompletedTasks(mapim);
            std::cout << "Tamamlanan gorev sayisi: " << adet << std::endl;
        }

        else {
            std::cout << "Gecerli bir secim yapmadiniz." << std::endl;
        }

    } while (true);

    return 0;
}
