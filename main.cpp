#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <vector>
#include <algorithm>

class Task{

private:

std::string name;
int id;
bool is_completed;


public:

// PARAMETRESİZ CONSTRUCTOR (ekledik)
Task() {
    id = 0;
    name = "";
    is_completed = false;
}

Task(int id_, std::string name_){

name=name_;
id=id_;
is_completed= false;

}

void complete(){

    is_completed= true;
}

bool isCompleted() const {
    return is_completed;
}


void  display() const{

std::cout<<"id:"<<id<<std::endl;
std::cout<<"name:"<<name<<std::endl;
std::cout<<"is completed?:"<<(is_completed ? "tamamlandi" : "tamamlanmadi")<<std::endl;

}

std::string  getName() const{

    return name;
}};

void findTaskByName( const std::map<int, Task>& gorevler, const std::string& arananisim ){

bool bulundu=false;

for(const auto& eleman: gorevler){
    const Task& gorev = eleman.second; 

    if(gorev.getName()== arananisim){
        
        gorev.display();
        bulundu=true;

    }

    if(!bulundu){

        std::cout << "Bu isimde bir gorev bulunamadi." << std::endl;
    }


}


}

int sayCompletedTasks(const std::map<int, Task>& gorevler) {
    return std::count_if(gorevler.begin(), gorevler.end(), [](const auto& eleman) {
        const Task& g = eleman.second;
        return g.isCompleted(); // is_completed kontrolü için getter lazım!
    });
}


void listeleIsmeGore(const std::map<int, Task>& gorevler){


    std::vector<Task> kopya;

    for (const auto& eleman : gorevler) {
        kopya.push_back(eleman.second);
    }

    std::sort(kopya.begin(), kopya.end(), [](const Task& a, const Task& b) {
        return a.getName() < b.getName();
    });

    std::cout << "--- İsme Göre Sıralı Görevler ---" << std::endl;
    for (const auto& g : kopya) {
        g.display();
    }


}




int main(){

    std::map<int, Task> mapim;
    int counter=1;
    int secim;
    

    do {

        std::cout<<"Gorev eklemek icin 1'e, gorev listelemek icin 2'ye cikis yapmak icin 3'e, gorev tamamlamak icin 4'e, silmek icin 5'e, gorev aramak icin 6'ya, gorevleri isime gore siralamak icin 7'ye, tamamlanan gorev sayisi icin 8'e    basiniz."<<std::endl;

        std::cin>> secim;

        if(std::cin.fail()){

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
            std::cout<< "gecerli bir sayi giriniz!"<< std::endl;
            continue;}

        else if(secim==1){

            std::string name_;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            

            std::cout<< "gorev adi giriniz."<< std::endl;

            std::getline(std::cin, name_);

            Task gorev(counter, name_);


            mapim[counter]= gorev;

            counter++;

        }

        else if(secim==2){

            for(auto& index: mapim){

                index.second.display();

            }
        }

        else if(secim==3){

            std::cout<< "programdan cikiliyor."<< std::endl;

            break;

        }else if(secim==4){
            int idmm;

            std::cout<< "Tamamlanacak gorevin idsini giriniz."<< std::endl;
            std::cin>>idmm;

            if(mapim.find(idmm) != mapim.end()){

                mapim[idmm].complete();
                std::cout << "Gorev tamamlandi!" << std::endl;
            }else{

                std::cout << "Bu ID'ye sahip bir gorev bulunamadi!" << std::endl;
            }}

            else if(secim==5){
                int idmmm;
    
                std::cout<< "Siliencek gorevin idsini giriniz."<< std::endl;
                std::cin>>idmmm;
    
                if(mapim.find(idmmm) != mapim.end()){
    
                    mapim.erase(idmmm);
                    std::cout << "Gorev silindi!" << std::endl;
                }else{
    
                    std::cout << "Bu ID'ye sahip bir gorev bulunamadi!" << std::endl;
                }}

        else if(secim==6){

            std::string isim;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize> :: max(), '\n');
            std::cout<< "Gorev adi giriniz."<< std::endl;
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
    else if (secim == 8) {
        int adet = sayCompletedTasks(mapim);
        std::cout << "Tamamlanan gorev sayisi: " << adet << std::endl;
    }
    

            

        else {
            std::cout << "Gecerli bir secim yapmadiniz." << std::endl;
        }



        }while(true);

   

    return 0;
}