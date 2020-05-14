#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

using func_t = double(*)(double, double);

func_t parse(const std::string &s);

#endif