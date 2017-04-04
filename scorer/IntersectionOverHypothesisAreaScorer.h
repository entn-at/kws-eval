#ifndef SCORER_INTERSECTIONOVERHYPOTHESISAREA_H_
#define SCORER_INTERSECTIONOVERHYPOTHESISAREA_H_

#include "scorer/Scorer.h"

namespace kws {
namespace scorer {

template <class RE, class HE>
class IntersectionOverHypothesisAreaScorer : public Scorer<RE, HE> {
 public:
  typedef RE RefEvent;
  typedef HE HypEvent;
  typedef typename Scorer<RE, HE>::Result Result;

  IntersectionOverHypothesisAreaScorer(float threshold) :
      threshold_(threshold) {}

  ~IntersectionOverHypothesisAreaScorer() override {}

  Result operator()(const RefEvent& ref, const HypEvent& hyp) override {
    if (hyp.Area() > 0) {
      const float val = IntersectionArea(ref, hyp) / (1.0f * hyp.Area());
      if (val >= threshold_) return Result{1.0f, 0.0f, 0.0f};
    }
    return Result{0.0f, 1.0f, 1.0f};
  }

  inline const float& Threshold() const { return threshold_; }

 private:
  const float threshold_;
};

}  // namespace scorer
}  // namespace kws

#endif  // SCORER_INTERSECTIONOVERHYPOTHESISAREA_H_
