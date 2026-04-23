/**
@file  worstofdigitalcallput.hpp
@brief The payoff of a Worst-of Digital Call/Put option on a basket of assets
*/

#pragma once

#include <qflib/products/product.hpp>
#include <algorithm>
#include <functional>

BEGIN_NAMESPACE(qf)

/** The Worst-of digital call/put class
*/
class WorstOfDigitalCallPut : public Product
{

public:
  /** Initializing ctor */
  WorstOfDigitalCallPut(int payoffType,
                        double strike,
                        double fixingTime,
                        double expiryTime,
                        size_t nAssets);

  /** The number of assets this product depends on */
  virtual size_t nAssets() const override;

  /** Evaluates the product given the passed-in path
      The "pricePath" matrix must have as many rows as
      the number of fixing times
      */
  virtual void eval(Matrix const & pricePath) override;

  /** Evaluates the product at fixing time index idx
  */
  virtual void eval(size_t idx, Vector const& spots, double contValue) override;

private:
  int payoffType_;          // 1: call; -1 put
  double strike_;
  size_t nAssets_;          // number of assets
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
WorstOfDigitalCallPut::WorstOfDigitalCallPut(int payoffType,
                                             double strike,
                                             double fixingTime,
                                             double expiryTime,
                                             size_t nAssets)
: payoffType_(payoffType), strike_(strike), nAssets_(nAssets)
{
  QF_ASSERT(payoffType == 1 || payoffType == -1, "WorstOfDigitalCallPut: the payoff type must be 1 (call) or -1 (put)!");
  QF_ASSERT(strike >= 0.0, "WorstOfDigitalCallPut: the strike must be non-negative!");
  QF_ASSERT(fixingTime >= 0.0,
    "WorstOfDigitalCallPut: the fixing time must be non-negative!");
  QF_ASSERT(expiryTime >= fixingTime,
    "WorstOfDigitalCallPut: the expiry time must be greater the fixing time!");

  // set the fixing times
  fixTimes_.resize(2);
  fixTimes_[0] = fixingTime;
  fixTimes_[1] = expiryTime;
  // assume that it will settle (pay) at expiration
  // TODO allow payment time later than expiration
  payTimes_.resize(1);
  payTimes_[0] = expiryTime;

  // this product generates only one payment
  payAmounts_.resize(1);
}

inline
size_t WorstOfDigitalCallPut::nAssets() const
{
  return nAssets_;
}

inline void WorstOfDigitalCallPut::eval(Matrix const & pricePath)
{
  size_t nfixings = pricePath.n_rows;
  QF_ASSERT(fixTimes_.size() == nfixings,
    "WorstOfDigitalCallPut: number of fixings mismatch in price path!");
  size_t nassets = pricePath.n_cols;
  QF_ASSERT(nAssets_ == nassets,
    "WorstOfDigitalCallPut: number of assets mismatch in price path!");

  double worst = 1.0e16;  // huge
  for (size_t j = 0; j < nassets; ++j) {
    double assetReturn = pricePath(1, j) / pricePath(0, j);
    worst = assetReturn < worst ? assetReturn : worst;
  }

  if (payoffType_ == 1)
    payAmounts_[0] = worst >= strike_ ? 1.0 : 0.0;
  else
    payAmounts_[0] = worst >= strike_ ? 0.0 : 1.0;
}

// Not implemented
inline void WorstOfDigitalCallPut::eval(size_t idx, Vector const& spots, double contValue)
{
  QF_ASSERT(0, "not implemented!");
}

END_NAMESPACE(qf)
