cc_library(
  name = "managers",
  srcs = ["alpacaTradeManager.cpp"],
  hdrs = [
    "ITradeManager.hpp",
    "alpacaTradeManager.hpp",
  ],
  visibility = [
    "//src:__pkg__",
    "//src/algos:__pkg__",
  ],
  deps = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
  ]
)
