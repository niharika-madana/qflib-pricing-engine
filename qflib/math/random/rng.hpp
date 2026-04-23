<<<<<<< HEAD
<<<<<<< HEAD
/** 
@file  rng.hpp
@brief Type definitions for common random number generators
*/

#pragma once

#include <qflib/math/random/normalrng.hpp>

BEGIN_NAMESPACE(qf)

/** Linear congruential */
using NormalRngMinStdRand = NormalRng<std::minstd_rand>;

/** Mersenne Twister */
using NormalRngMt19937 = NormalRng<std::mt19937>;

/** RanLux level 3 */
using NormalRngRanLux3 = NormalRng<std::ranlux24>;

/** RanLux level 4 */
using NormalRngRanLux4 = NormalRng<std::ranlux48>;

END_NAMESPACE(qf)
=======
/** 
@file  rng.hpp
@brief Type definitions for common random number generators
*/

#pragma once

#include <qflib/math/random/normalrng.hpp>

BEGIN_NAMESPACE(qf)

/** Linear congruential */
using NormalRngMinStdRand = NormalRng<std::minstd_rand>;

/** Mersenne Twister */
using NormalRngMt19937 = NormalRng<std::mt19937>;

/** RanLux level 3 */
using NormalRngRanLux3 = NormalRng<std::ranlux24>;

/** RanLux level 4 */
using NormalRngRanLux4 = NormalRng<std::ranlux48>;

END_NAMESPACE(qf)
>>>>>>> origin/yuyang-branch
=======
/** 
@file  rng.hpp
@brief Type definitions for common random number generators
*/

#pragma once

#include <qflib/math/random/normalrng.hpp>

BEGIN_NAMESPACE(qf)

/** Linear congruential */
using NormalRngMinStdRand = NormalRng<std::minstd_rand>;

/** Mersenne Twister */
using NormalRngMt19937 = NormalRng<std::mt19937>;

/** RanLux level 3 */
using NormalRngRanLux3 = NormalRng<std::ranlux24>;

/** RanLux level 4 */
using NormalRngRanLux4 = NormalRng<std::ranlux48>;

END_NAMESPACE(qf)
>>>>>>> origin/fangyi-branch
