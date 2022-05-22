#include <string>

#include "IAlgorithm.hpp"
#include "src/dataRetrievers/alpacaDataRetriever.hpp"
#include "src/tradeManagers/alpacaTradeManager.hpp"

class MovingAverage: public IAlgorithm {
  public:
    IDataRetriever *dataRetriever;
    ITradeManager *tradeManager;

    MovingAverage(); 
    MovingAverage(IDataRetriever *dataRetriever, ITradeManager *tradeManager);

    void Trade();

    std::string getDataRetrieverName();
};
