#include "ITradeManager.hpp"
#include "alpaca/alpaca.h"
#include "alpaca/client.h"
#include "alpaca/config.h"

#include <memory>
#include <iostream>


class AlpacaTradeManager: public ITradeManager {
  public:
    AlpacaTradeManager();
    AlpacaTradeManager(alpaca::Client &existingClient);
    virtual bool Buy(std::string symbol, int shares);
    virtual bool Sell(std::string symbol, int shares);
    std::unique_ptr<alpaca::Client> client;
};
