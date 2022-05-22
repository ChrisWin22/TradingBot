#include "alpacaTradeManager.hpp"
#include <memory>

AlpacaTradeManager::AlpacaTradeManager() {
  std::cout << "Initializing Alpaca Trade Manager" << std::endl;
  name = "Alpaca";

  auto env = alpaca::Environment();
  if(auto status = env.parse(); !status.ok()) {
    throw std::runtime_error("Couldn't parse environment: " + status.getMessage());
  }

  std::cout << "Parsed Env" << std::endl;

  client = std::make_unique<alpaca::Client>(alpaca::Client(env));
  std::cout << "Created client" << std::endl;
}

AlpacaTradeManager::AlpacaTradeManager(alpaca::Client &existingClient) {
  std::cout << "Initializing Alpaca Trade Manager" << std::endl;
  name = "Alpaca";

  client = std::make_unique<alpaca::Client>(existingClient);
}

bool AlpacaTradeManager::Buy(std::string symbol, int shares) {
  std::cout << "Buying " << shares << " shares of " << symbol << std::endl;
  auto buyResponse = client->submitOrder(symbol, shares, alpaca::OrderSide::Buy, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
  if(alpaca::Status status = buyResponse.first; !status.ok()) {
    std::cout << "Error buying " << symbol << ": " << status.getMessage() << std::endl;
    return false;
  }

  return true;
}

bool AlpacaTradeManager::Sell(std::string symbol, int shares) {
  std::cout << "Selling " << shares << " shares of " << symbol << std::endl;
  auto sellResponse = client->submitOrder(symbol, shares, alpaca::OrderSide::Sell, alpaca::OrderType::Market, alpaca::OrderTimeInForce::Day);
  if(alpaca::Status status = sellResponse.first; !status.ok()) {
    std::cout << "Error selling " << symbol << ": " << status.getMessage() << std::endl;
    return false;
  }

  return true;
}
