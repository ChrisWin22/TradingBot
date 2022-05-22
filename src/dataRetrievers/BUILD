cc_library(
  name = "retrievers",
  srcs = [
    "alpacaDataRetriever.cpp",
  ],
  hdrs = [
    "alpacaDataRetriever.hpp",
    "IDataRetriever.hpp",
  ],
  visibility = [
    "//src:__pkg__",
    "//src/algos:__pkg__",
  ],
  deps = [
    "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    "//commonutils:commonutils",
  ]
)
