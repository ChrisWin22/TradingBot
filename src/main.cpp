#include <cctype>
#include <functional>
#include <iostream>
#include <string>

#include "alpaca/streaming.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "src/algos/movingAverage.hpp"

int main(int argc, char* argv[]) {

  MovingAverage *algo = new MovingAverage();
  algo->Trade();

  return 0;
}
