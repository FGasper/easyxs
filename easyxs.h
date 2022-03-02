#ifndef EASYXS_H
#define EASYXS_H 1

#include "init.h"
#include "easyxs_perlcall.h"

#define _EASYXS_CROAK_STRINGIFY_REFERENCE(sv) \
    croak("%" SVf " given where string expected!", sv)

#define _EASYXS_CROAK_UNDEF(expected) \
    croak("undef given; " expected " expected")

inline char* _easyxs_sv_to_str (pTHX_ SV* sv, uint8_t is_utf8) {
    if (SvROK(sv)) _EASYXS_CROAK_STRINGIFY_REFERENCE(sv);

    char *str = is_utf8 ? SvPVutf8_nolen(sv) : SvPVbyte_nolen(sv);

    size_t len = strnlen(str, 1 + SvCUR(sv));
    if (len != SvCUR(sv)) {
        croak("Cannot convert scalar to C string (NUL byte detected, offset %zu)", len);
    }

    return str;
}

UV _easyxs_SvUV (pTHX_ SV* sv) {
    if (!SvOK(sv)) _EASYXS_CROAK_UNDEF("unsigned integer");

    if (SvROK(sv)) _EASYXS_CROAK_STRINGIFY_REFERENCE(sv);

    if (SvUOK(sv)) return SvUV(sv);

    if (SvIOK(sv)) {
        IV myiv = SvIV(sv);

        if (myiv >= 0) return myiv;
    }
    else {
        STRLEN pvlen;
        const char* pv = SvPVbyte(sv, pvlen);

        UV myuv;
        int grokked = grok_number(pv, pvlen, &myuv);

        if (grokked & (IS_NUMBER_IN_UV | !IS_NUMBER_NEG)) {
            const char* uvstr = form("%" UVuf, myuv);

            if (strlen(uvstr) == pvlen && strEQ(uvstr, pv)) return myuv;
        }
    }

    croak("`%" SVf "` given where unsigned integer expected!", sv);
}

/* ---------------------------------------------------------------------- */

#define exs_SvPVbyte_nolen(sv) _easyxs_sv_to_str(aTHX_ sv, 0);
#define exs_SvPVutf8_nolen(sv) _easyxs_sv_to_str(aTHX_ sv, 1);

#define exs_SvUV(sv) _easyxs_SvUV(aTHX_ sv);

#endif
