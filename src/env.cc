#include "dict.h"
#include "env.h"

using namespace puck;

Env::Env() {
    this->outer = nullptr;
}

Env::Env(Env &outer) {
    this->outer = &outer;
}

void Env::Set(object::Object &key, object::Object &value) {
    store[&key] = &value;
}

object::Object *Env::Get(object::Object &key) {
    auto iter = store.find(&key);
    if (iter == store.end()) {
        auto outer = GetOuter();
        if (outer != nullptr) {
            return outer->Get(key);
        } else {
            return nullptr;
        }
    }
    return iter->second;
}

rv_env* rv_env_new(rv_env* outer) {
    rv_env* env = (rv_env*)malloc(sizeof(rv_env));
    env->dict = rv_dict_new();
    env->outer = outer;
    return env;
}

void rv_env_set(rv_env* env, rv_obj* key, rv_obj* value) {
    rv_dict_set(env->dict, key, value);
}

rv_obj* rv_env_get(rv_env* env, rv_obj* key) {
    if (env == NULL) {
        return NULL;
    }

    rv_obj* value;

    while (true) {
        value = rv_dict_get(env->dict, key);
        if (value != NULL) {
            return value;
        } else {
            return rv_env_get(env->outer, key);
        }
    }
    return NULL;
}
