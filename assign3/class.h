#include <string>
#include <sstream>

class StanfordID {
    private:
        std::string name;
        std::string sunet;
        int idNumber;

        std::string getInitialName(std::string name);
    
    public:
        StanfordID(std::string name, std::string sunet, int idNumber);
        StanfordID();

        const std::string getName();
        const std::string getSunet();
        const int getIdNumber();

        void setName(std::string name);
};