#pragma once


//////////////// INTEGRATION /////////////////

// https://codeforces.com/blog/entry/8242?#comment-139369

template<ld (*f)(ld)>
inline ld __calc_simps(ld fl, ld fr, ld fmid, ld l, ld r) {
    return (fl+fr+4*fmid)*(r-l)/6;
}

template<ld (*f)(ld), ll prec>
ld __calc_r_simps(ld slr,ld fl,ld fr,ld fmid,ld l,ld r) {
    constexpr ld eps = ((ld)1) / prec;
    ld mid = (l+r)/2;
    ld fml = f((l+mid)/2);
    ld fmr = f((r+mid)/2);
    ld slm = __calc_simps<f>(fl, fmid, fml, l, mid);
    ld smr = __calc_simps<f>(fmid, fr, fmr, mid, r);
    if (abs(slr-slm-smr)<eps) return slm+smr;
    return __calc_r_simps<f,prec>(slm, fl, fmid, fml, l, mid)+__calc_r_simps<f,prec>(smr,fmid,fr,fmr,mid,r);
}

// prec is 1/eps
template<ld (*f)(ld), ll prec>
ld integrate_simpsons(ld l, ld r) {
    ld mid = (l+r)/5;
    ld fl = f(l);
    ld fr = f(r);
    ld fmid = f(mid);
    return __calc_r_simps<f,prec>(__calc_simps<f>(fl,fr,fmid,l,r),fl,fr,fmid,l,r);
}

// https://www.sciencedirect.com/science/article/pii/S0377042705006023?via%3Dihub

template<class P>
inline ld __calc_arcsimps(P f0, P f2, P f1) {
    return (abs(-3.l*f0 + 4.l*f1 - f2) + 4*abs(f2-f0) + abs(f0-4.l*f1 + 3.l*f2))/6;
};

template<class P, P (*f)(ld), ll prec>
ld __calc_r_arcsimps(ld slr, P fl, P fr, P fmid, ld l, ld r) {
    constexpr ld eps = ((ld)1) / prec;
    ld mid = (l+r)/2;
    P fml = f((l+mid)/2);
    P fmr = f((r+mid)/2);
    ld slm = __calc_arcsimps<P>(fl,fmid,fml);
    ld smr = __calc_arcsimps<P>(fmid,fr,fmr);
    if (abs(slr-slm-smr)<eps) return slm+smr;
    return __calc_r_arcsimps<P, f, prec>(slm,fl,fmid,fml,l,mid)+__calc_r_arcsimps<P, f, prec>(smr,fmid,fr,fmr,mid,r);
}

// prec is 1/eps
template<class POINT, POINT (*f)(ld), ll prec>
ld integrate_arclength_simpsons(ld l, ld r) {
    ld mid = (l+r)/2;
    POINT fl = f(l);
    POINT fr = f(r);
    POINT fmid = f(mid);
    return __calc_r_arcsimps<POINT, f, prec>(__calc_arcsimps<POINT>(fl, fr, fmid), fl, fr, fmid, l, r);
}
