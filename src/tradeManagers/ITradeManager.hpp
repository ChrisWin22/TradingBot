#include <string>

class ITradeManager {
  public:
    virtual ~ITradeManager() {}
    virtual bool Buy(std::string symbol, int shares) = 0;
    virtual bool Sell(std::string symbol, int shares) = 0;
    std::string name;
    std::string getName() {return name;}
};
