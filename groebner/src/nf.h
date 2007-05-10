/*
 *  nf.h
 *  PolyBoRi
 *
 *  Created by Michael Brickenstein on 25.04.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <algorithm>
#include <vector>
#include <queue>
#include "groebner_alg.h"
#ifndef PBORI_GB_NF_H
#define PBORI_GB_NF_H
BEGIN_NAMESPACE_PBORIGB

int select1(const GroebnerStrategy& strat, const Polynomial& p);
int select1(const GroebnerStrategy& strat, const Monomial& m);

int select_no_deg_growth(const GroebnerStrategy& strat, const Monomial& m);

static int select_short(const GroebnerStrategy& strat, const Polynomial& p);
static int select_short(const GroebnerStrategy& strat, const Monomial& m);

Polynomial nf1(GroebnerStrategy& strat, Polynomial p);

Polynomial nf2(GroebnerStrategy& strat, Polynomial p);
Polynomial nf2_short(GroebnerStrategy& strat, Polynomial p);

Polynomial nf_delaying(GroebnerStrategy& strat, Polynomial p);
Polynomial nf_delaying_exchanging(GroebnerStrategy& strat, Polynomial p);

class LMLessCompare{
public:
  bool operator() (const Polynomial& p1, const Polynomial& p2){
    return p1.lead()<p2.lead();
  }
};

const int SLIMGB_SIMPLEST=0;
template<int variant> class SlimgbReduction{
private:
  GroebnerStrategy* strat;
  std::priority_queue<Polynomial, std::vector<Polynomial>, LMLessCompare> to_reduce;
  public:
  std::vector<Polynomial> result;

  SlimgbReduction(GroebnerStrategy& strat){
    this->strat=&strat;
  }
  SlimgbReduction(){}
  void addPolynomial(const Polynomial& p);
  void reduce();
  //return zero at the end
  Polynomial nextResult();
};
template <int variant> void SlimgbReduction<variant>::addPolynomial(const Polynomial& p){
  if (!(p.isZero())){
    to_reduce.push(p);
  }
}
template <int variant> Polynomial SlimgbReduction<variant>::nextResult(){
  if (result.size()==0) return Polynomial();
  Polynomial res=result.back();
  result.pop_back();
  return res;
}
typedef SlimgbReduction<SLIMGB_SIMPLEST> slimgb_reduction_type;
std::vector<Polynomial> parallel_reduce(std::vector<Polynomial> inp, GroebnerStrategy& strat, int average_steps, double delay_f);
Polynomial red_tail(const GroebnerStrategy& strat, Polynomial p);
Polynomial red_tail_short(const GroebnerStrategy& strat, Polynomial p);
Polynomial nf3(const GroebnerStrategy& strat, Polynomial p, Monomial rest_lead);
Polynomial nf3_short(const GroebnerStrategy& strat, Polynomial p);
Polynomial red_tail_self_tuning(const GroebnerStrategy& strat, Polynomial p);
Polynomial ll_red_nf(const Polynomial& p,const BooleSet& reductors);
MonomialSet mod_mon_set(const MonomialSet& as, const MonomialSet &vs);
END_NAMESPACE_PBORIGB
#endif
