#pragma once
#include <functional>
#include <memory>

typedef std::tuple<std::string, int, std::shared_ptr<void>, void*> B_TUPLE_PARAM;
typedef std::function<void(std::string, B_TUPLE_PARAM)> BDelegate;