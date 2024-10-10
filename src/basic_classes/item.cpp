#include "item.hpp"
namespace game{
    Item::Item(string name, unsigned int weight, bool is_thrown, Point pos = Point()) : name_(name), weight_(weight), is_thrown_(is_thrown), position_(pos){}
    Item::~Item() {}

    string Item::get_name() {
        return name_;
    }

    unsigned int Item::get_weight() {
        return weight_;
    }

    void Item::execute() {}
    void Item::put_item(){
        is_thrown_ = false;
    }
    void Item::throw_item(Point pos){
        is_thrown_ = true;
        position_ = pos;
    }
    Point & Item::get_position(){
        // TODO: вернуть ошибку, если предмет не на земле
        return position_;
    }
    bool Item::get_is_trown(){
        return is_thrown_;
    }
}