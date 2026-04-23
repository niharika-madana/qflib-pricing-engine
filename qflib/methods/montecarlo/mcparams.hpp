<<<<<<< HEAD
/**
@file  mcparams.hpp
@brief Monte Carlo parameters
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)


/** Monte Carlo parameters
*/
struct McParams
{
  /** The known URNG types */
  enum class UrngType
  {
    MINSTDRAND,
    MT19937,
    RANLUX3,
    RANLUX4
  };

  /** The known path generator types */
  enum class PathGenType
  {
    EULER
  };
  
  /** Control variate types */
  enum class ControlVarType
  {
    NONE,
    ANTITHETIC
  };


  /** Default ctor */
  McParams(UrngType u = UrngType::MT19937, PathGenType p = PathGenType::EULER, 
    ControlVarType c = ControlVarType::NONE);

  // state
  UrngType urngType;
  PathGenType pathGenType;
  ControlVarType controlVarType;
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
McParams::McParams(UrngType u, PathGenType p, ControlVarType c)
: urngType(u), pathGenType(p), controlVarType(c)
{}

END_NAMESPACE(qf)
=======
/**
@file  mcparams.hpp
@brief Monte Carlo parameters
*/

#pragma once

#include <qflib/defines.hpp>
#include <qflib/exception.hpp>

BEGIN_NAMESPACE(qf)


/** Monte Carlo parameters
*/
struct McParams
{
  /** The known URNG types */
  enum class UrngType
  {
    MINSTDRAND,
    MT19937,
    RANLUX3,
    RANLUX4
  };

  /** The known path generator types */
  enum class PathGenType
  {
    EULER
  };
  
  /** Control variate types */
  enum class ControlVarType
  {
    NONE,
    ANTITHETIC
  };


  /** Default ctor */
  McParams(UrngType u = UrngType::MT19937, PathGenType p = PathGenType::EULER, 
    ControlVarType c = ControlVarType::NONE);

  // state
  UrngType urngType;
  PathGenType pathGenType;
  ControlVarType controlVarType;
};

///////////////////////////////////////////////////////////////////////////////
// Inline definitions

inline
McParams::McParams(UrngType u, PathGenType p, ControlVarType c)
: urngType(u), pathGenType(p), controlVarType(c)
{}

END_NAMESPACE(qf)
>>>>>>> origin/yuyang-branch
