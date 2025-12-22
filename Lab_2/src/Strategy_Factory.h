#include <map>
#include <memory>
#include "Strategy.h"

#ifndef LAB_2_STRATEGY_FACTORY_H
#define LAB_2_STRATEGY_FACTORY_H


template<typename Strategy_T, typename ID_T, typename Creator_T>
class Factory {
public:
    static Factory* getInstance() {
        static Factory f;
        return &f;
    }

    std::unique_ptr<Strategy_T> create_strategy(const ID_T& name) {
        auto st =  create_func.find(name);
        if (st == create_func.end()) {
            return nullptr;
        }
        return std::unique_ptr<Strategy_T>(st->second());
    }

    bool register_strategy(const ID_T& type, Creator_T creator) {
        create_func[type] = creator;
        return true;
    }


private:
    std::map<ID_T, Creator_T> create_func;
};
using FactoryStrategy = Factory<Strategy, std::string, Strategy* (*)()>;

#endif //LAB_2_STRATEGY_FACTORY_H