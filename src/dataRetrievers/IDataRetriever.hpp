#include <string>
#include <vector>
#include <map>
#include "commonutils/Asset.hpp"
#include "alpaca/bars.h"

class IDataRetriever {
  public:
    virtual ~IDataRetriever() {}
    virtual void getData() = 0;
    virtual std::vector<Asset> getAssets() = 0;
    virtual std::map<std::string, std::vector<alpaca::Bar>> getBars(std::vector<std::string> symbols, std::string start, std::string end, std::string timeframe, uint limit) = 0;
    virtual std::vector<alpaca::Bar> getBars(std::string symbol, std::string start, std::string end, std::string timeframe, uint limit) = 0;
    std::string name;
    std::string getName() {return name;}
};
