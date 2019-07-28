#ifndef UICONFIGMACRO_H
#define UICONFIGMACRO_H
#include "UIComponentManager.h"

namespace
{

template <class T>
class hiden_static_var
{
    static T var;
};

}

// Add static component to Interface
#define UI_STATIC_COMPONENT(type, name, help_tip)\
    namespace\
    {\
        template <>\
        UI::UIComponentManager< type > hiden_static_var<UI::UIComponentManager< type >>\
        ::var(name, help_tip, false);\
    }\

// Add static command pack to Interface
#define UI_STATIC_CMD_PACK(type)\
    namespace\
    {\
        template <>\
        type hiden_static_var< type >\
        ::var();\
    }\

#endif // UICONFIGMACRO_H
