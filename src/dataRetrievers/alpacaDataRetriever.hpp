#include <string>
#include <string>
#include <iostream>
#include <stdexcept>
#include <stddef.h>
#include <cstddef>
#include <memory>

#include "IDataRetriever.hpp"
#include "alpaca/alpaca.h"
#include "alpaca/client.h"
#include "alpaca/config.h"

class AlpacaDataRetriever: public IDataRetriever {
  public: 
    AlpacaDataRetriever();
    AlpacaDataRetriever(alpaca::Client &existingClient);
    void getData();
    std::vector<Asset> getAssets();
    std::unique_ptr<alpaca::Client> client;
    std::map<std::string, std::vector<alpaca::Bar>> getBars(std::vector<std::string> symbols, std::string start, std::string end, std::string timeframe, uint limit);
    std::vector<alpaca::Bar> getBars(std::string symbol, std::string start, std::string end, std::string timeframe, uint limit);
  private:
    Asset createAsset(alpaca::Asset);
};
