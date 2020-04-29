//
// Created by karla on 17. 10. 2019..
//

#ifndef PROJEKT_FUNCTION_H
#define PROJEKT_FUNCTION_H

#include <vector>

template <typename T>
class Function {
    public:
    virtual ~Function() {}
        virtual double get_value( T &args ) = 0;
        virtual std::pair<double, double> get_value_NSGA( T &args ) = 0;
};

#endif //PROJEKT_FUNCTION_H
