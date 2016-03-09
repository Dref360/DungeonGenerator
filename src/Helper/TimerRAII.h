#include <chrono>
#include <iostream>
#include <string>

class TimerRAII
{
private:
    std::chrono::high_resolution_clock::time_point avant;
    std::ostream &os;
    std::string task;
    bool toCSV;
    
public:
    TimerRAII(std::string task,std::ostream& os,bool toCSV = false)
    : os{os},task{task},toCSV{toCSV},avant{std::chrono::high_resolution_clock::now()}
    {
        
    }
    ~TimerRAII()
    {
        auto apres = std::chrono::high_resolution_clock::now();
        if(toCSV)
        {
            os<< std::chrono::duration_cast<std::chrono::microseconds>(apres-avant).count() << ",";
        }
        else{
            os << "Temps ecoule pour " << task << " : "
              << std::chrono::duration_cast<std::chrono::microseconds>(apres-avant).count()
              << " us." << std::endl;
        }
        
    }
};