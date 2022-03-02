#ifndef EASYXS_PERLCALL_H
#define EASYXS_PERLCALL_H 1

#include "init.h"

static inline void _EASYXS_SET_ARGS (pTHX_ SV* object, SV** args) {
    unsigned argscount = 0;

    if (args) {
        while (args[argscount] != NULL) argscount++;
    }

    ENTER;
    SAVETMPS;

    PUSHMARK(SP);

    if (object || argscount) {
        EXTEND(SP, (object ? 1 : 0) + argscount);

        if (object) PUSHs( sv_mortalcopy(object) );

        unsigned a=0;
        while (a < argscount) mPUSHs( args[a++] );

        PUTBACK;
    }
}

#define exs_call_method_void(object, methname, args) STMT_START { \
    dSP;                                            \
                                                    \
    _EASYXS_SET_ARGS(object, args);                 \
                                                    \
    call_method( methname, G_DISCARD | G_VOID );    \
                                                    \
    FREETMPS;                                       \
    LEAVE;                                          \
} STMT_END

#endif
