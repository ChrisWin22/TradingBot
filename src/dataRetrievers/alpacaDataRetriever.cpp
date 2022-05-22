#include "alpacaDataRetriever.hpp"
#include <exception>
#include <stdexcept>
#include <utility>

AlpacaDataRetriever::AlpacaDataRetriever() {
  std::cout << "Initializing Alpaca Data Retriever" << std::endl;
  name = "Alpaca";

  auto env = alpaca::Environment();
  if(auto status = env.parse(); !status.ok()) {
    throw std::runtime_error("Couldn't parse environment: " + status.getMessage());
  }

  std::cout << "Parsed Env" << std::endl;

  client = std::make_unique<alpaca::Client>(alpaca::Client(env));                                    
  std::cout << "Created client" << std::endl;
}

AlpacaDataRetriever::AlpacaDataRetriever(alpaca::Client &existingClient) {
  std::cout << "Initializing Alpaca Trade Manager" << std::endl;
  name = "Alpaca";

  client = std::make_unique<alpaca::Client>(existingClient);
}

void AlpacaDataRetriever::getData() {

}                                   

// Bars are sorted from front -> back, oldest -> newest
std::vector<alpaca::Bar> AlpacaDataRetriever::getBars(std::string symbol,std::string start, std::string end, std::string timeframe, uint limit) {
  std::vector<std::string> mySymbol {symbol};
  auto bars = getBars(mySymbol, start, end, timeframe, limit);
  return bars.at(symbol);
}

// Bars are sorted from front -> back, oldest -> newest
std::map<std::string, std::vector<alpaca::Bar>> AlpacaDataRetriever::getBars(std::vector<std::string> symbols,std::string start, std::string end, std::string timeframe, uint limit) {
  auto barsResponse = client->getBars(symbols, start, end, "", "", timeframe, limit);
  if(alpaca::Status status = barsResponse.first; !status.ok()) {
    throw std::runtime_error("Couldn't retrieve bar data: " + status.getMessage());
  }
  alpaca::Bars bars = barsResponse.second;
  return bars.bars;
}

std::vector<Asset> AlpacaDataRetriever::getAssets() {
  auto accountResponse = client->getAccount();
  if(auto status = accountResponse.first; !status.ok()) {
    throw std::runtime_error("Couldn't get account: " + status.getMessage());
  }
  auto account = accountResponse.second;
  std::cout << account.account_number << std::endl;

  std::vector<Asset> newAssets;

  auto assetsResponse = client->getAssets();
  if(auto status = assetsResponse.first; !status.ok()) {
    throw std::runtime_error("Couldn't get assets: " + status.getMessage());
  }
  auto assets = assetsResponse.second;

  for(alpaca::Asset &asset : assets) {
    newAssets.push_back(createAsset(asset));
  }

  return newAssets;
}

Asset AlpacaDataRetriever::createAsset(alpaca::Asset alpacaAsset) {
  Asset *newAsset = new Asset();
  newAsset->asset_class = alpacaAsset.asset_class;
  newAsset->easy_to_borrow = alpacaAsset.easy_to_borrow;
  newAsset->exchange = alpacaAsset.exchange;
  newAsset->id = alpacaAsset.id;
  newAsset->marginable = alpacaAsset.marginable;
  newAsset->shortable = alpacaAsset.shortable;
  newAsset->status = alpacaAsset.status;
  newAsset->symbol = alpacaAsset.symbol;
  newAsset->tradable = alpacaAsset.tradable;

  return *newAsset;
}
