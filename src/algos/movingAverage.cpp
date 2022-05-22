#include <iostream>
#include <time.h>
#include <ctime>

#include "movingAverage.hpp"

MovingAverage::MovingAverage() {
  dataRetriever = new AlpacaDataRetriever();
  AlpacaDataRetriever* dr = dynamic_cast<AlpacaDataRetriever*>(dataRetriever);
  tradeManager = new AlpacaTradeManager(*(dr->client));
}

MovingAverage::MovingAverage(IDataRetriever *dataRetriever, ITradeManager *tradeManager) {
  this->dataRetriever = dataRetriever;
  this->tradeManager = tradeManager;
}

double getBarAverage(std::vector<alpaca::Bar> bars) {
  double totalPrice = 0;
  for(alpaca::Bar &bar : bars) {
    totalPrice += bar.close_price;
  }

  return totalPrice / bars.size();
}

void MovingAverage::Trade() {
  const uint secondsInDay = 60*60*24;
  const uint dayRange = 10;
  const uint secondRange = secondsInDay * dayRange;
  char buf[sizeof "2011-10-08T07:07:09Z"];

  time_t currentTime;
  time(&currentTime);
  tm* currentTM = gmtime(&currentTime);
  strftime(buf, sizeof buf, "%FT%TZ", currentTM);
  std::string currentTimeString = buf;

  currentTM->tm_sec -= secondRange;
  const time_t prevTime = std::mktime(currentTM);
  tm* prevTM = gmtime(&prevTime);
  strftime(buf, sizeof buf, "%FT%TZ", prevTM);
  std::string prevTimeString = buf;
  
  std::cout << "Current Time: " << currentTimeString << std::endl;
  std::cout << "Start Time: " << prevTimeString << std::endl;

  auto bars = dataRetriever->getBars("AAPL", prevTimeString, currentTimeString, "15Min", 1000);
  double lastClosePrice = bars.back().close_price;                            
  double average = getBarAverage(bars);

  std::cout << "Last close: " << lastClosePrice << std::endl;
  std::cout << "Running average: " << average << std::endl;

  if(lastClosePrice < average) {
    tradeManager->Buy("AAPL", 1);
  }
  else if(lastClosePrice > average) {
    tradeManager->Sell("AAPL", 1);
  }
}

std::string MovingAverage::getDataRetrieverName() {
  return dataRetriever->name;
}


