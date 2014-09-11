#include <stdio.h>
#include <string.h>
#include "../src/object.h"

using namespace rv;

int TestInteger() {
    auto one = new rv::object::Integer(1);
    auto two = new rv::object::Integer(2);
    if (one->GetType() != rv::object::type::INTEGER) {
        return 1;
    }
    if (one->EqualTo(two)) {
        return 1;
    }
    if (!one->EqualTo( new rv::object::Integer(1) )) {
        return 1;
    }
    return 0;
}

int TestReal() {
    object::Object *obj = new object::Real(0.618);
    if (obj->GetType() != object::type::REAL) {
        return 1;
    }
    return 0;
}

int TestBool() {
    object::Object *True = new object::Bool(true);
    if (True->GetType() != object::type::BOOL) {
        return 1;
    }
    if (strcmp(True->ToString(), "#t") != 0) {
        return 1;
    }
    return 0;
}

int TestPair() {
    object::Object *nil = new object::Pair(nullptr, nullptr);
    if (nil->GetType() != object::type::PAIR) {
        return 1;
    }
    if (strcmp(nil->ToString(), "( . )") != 0) {
        return 1;
    }
    if (! nil->EqualTo(new object::Pair(nullptr, nullptr))) {
        return 1;
    }

    object::Object *one = new object::Integer(1);
    object::Object *two = new object::Integer(2);
    object::Object *tree = new object::Integer(3);

    object::Object *pair = new object::Pair(one, new object::Pair(two, new object::Pair(tree, nullptr)));
    if (strcmp(pair->ToString(), "(1 . (2 . (3 . )))") != 0) {
        return 1;
    }

    return 0;
}

int TestSymbol() {
    char *str = const_cast<char *>("foo");
    object::Object *obj = new object::Symbol(str);
    if (obj->GetType() != object::type::SYMBOL) {
        return 1;
    }
    if (strcmp(obj->ToString(), "'foo") != 0) {
        return 1;
    }
    return 0;
}

int TestString() {
    char *str = const_cast<char *>("hello world!");
    object::Object *obj = new object::String(str);
    if (obj->GetType() != object::type::STRING) {
        return 1;
    }
    if (strcmp(obj->ToString(), "\"hello world!\"") != 0) {
        return 1;
    }
    return 0;
}

int TestObject() {
    int r = 0;
    // r += TestInteger();
    // r += TestReal();
    // r += TestBool();
    r += TestPair();
    // r += TestSymbol();
    // r += TestString();
    return r;
}
