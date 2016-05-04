/**
 * Filename: callbackfunctor.h
 * Author: //TO DO: Teamname
 * Date: 27 April 2016
 * Description: This class enables callback functions using the NetworkController
 */

#ifndef CALLBACKFUNCTOR_H
#define CALLBACKFUNCTOR_H

#include "networkcontroller.h"
#include "typetypecontroller.h"

/**
 * The template type should be the type of the class containing the callback
 */
template <class T>
class CallbackFunctor {
    /*
public:
    CallbackFunctor(void(T::*callback)(NetworkState*), T *parent);
    CallbackFunctor(const CallbackFunctor&);
    void operator()(NetworkState*);
    */
protected:
    void(T::*callback)(NetworkState*);
    T *parent;

public:
CallbackFunctor(void(T::*callback)(NetworkState*),
    T *parent) : parent(parent), callback(callback) {

}

CallbackFunctor(const CallbackFunctor& toCopy) :
    parent(toCopy.parent), callback(toCopy.callback) {

}

void operator()(NetworkState* state) {
    (parent->*callback)(state);
}
};

#endif // CALLBACKFUNCTOR_H
