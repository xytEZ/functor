#ifndef FUNCTOR_HPP_
# define FUNCTOR_HPP_

# include <stdexcept>
# include <utility>

template <typename TRET>
class Functor;

# define Functor(COMMA, TNPARAMS, TPARAMS, TVPARAMS, PARAMS)		\
  									\
  template <typename TRET COMMA TNPARAMS>				\
  class Functor<TRET (TPARAMS)>						\
  {									\
  private :								\
    class ICallable							\
    {									\
    public :								\
      virtual ~ICallable() { }						\
      virtual TRET operator()(TPARAMS) = 0;			      	\
    };									\
    									\
    template <typename T>						\
      class CallableObj : public ICallable				\
    {									\
    private :								\
      T _callableObj;							\
      									\
    public :								\
      CallableObj(const T& callableObj) : _callableObj(callableObj) { }	\
									\
      CallableObj(T&& callableObj) :					\
	_callableObj(std::move(callableObj))				\
      { }								\
									\
      ~CallableObj() { }						\
									\
      virtual TRET operator()(TVPARAMS)					\
      {									\
	return _callableObj(PARAMS);					\
      }									\
    };									\
									\
    class FunctionPtr : public ICallable				\
    {									\
    private :								\
      TRET (*_funcPtr)(TPARAMS);					\
									\
    public :								\
      FunctionPtr(TRET (*funcPtr)(TPARAMS)) : _funcPtr(funcPtr) { }	\
      ~FunctionPtr() { }						\
									\
      virtual TRET operator()(TVPARAMS)				       	\
      {									\
	return (*_funcPtr)(PARAMS);					\
      }									\
    };									\
									\
  private :								\
    ICallable *_callable;						\
    									\
  public :								\
    template <typename T>						\
      Functor(const T& callableObj) :				        \
      _callable(new CallableObj<T>(callableObj))			\
    { }									\
									\
    template <typename T>						\
      Functor(T&& callableObj) :					\
      _callable(new CallableObj<T>(std::forward<T>(callableObj)))	\
    { }									\
    									\
    Functor(TRET (*funcPtr)(TVPARAMS)) :				\
      _callable(new FunctionPtr(funcPtr))				\
    { }									\
									\
    ~Functor() { delete _callable; }					\
									\
    virtual TRET operator()(TVPARAMS)					\
    {									\
      return (*_callable)(PARAMS);					\
    }									\
  };									\
  
# define CONCAT(a, b) a##b 

# define ENUM_1(a) CONCAT(a, 1)
# define ENUM_2(a) ENUM_1(a), CONCAT(a, 2)
# define ENUM_3(a) ENUM_2(a), CONCAT(a, 3)
# define ENUM_4(a) ENUM_3(a), CONCAT(a, 4)
# define ENUM_5(a) ENUM_4(a), CONCAT(a, 5)
# define ENUM_6(a) ENUM_5(a), CONCAT(a, 6)
# define ENUM_7(a) ENUM_6(a), CONCAT(a, 7)
# define ENUM_8(a) ENUM_7(a), CONCAT(a, 8)
# define ENUM_9(a) ENUM_8(a), CONCAT(a, 9)

# define TVPARAM_1(a, b) CONCAT(a, 1) CONCAT(b, 1)
# define TVPARAM_2(a, b) TVPARAM_1(a, b), CONCAT(a, 2) CONCAT(b, 2)
# define TVPARAM_3(a, b) TVPARAM_2(a, b), CONCAT(a, 3) CONCAT(b, 3)
# define TVPARAM_4(a, b) TVPARAM_3(a, b), CONCAT(a, 4) CONCAT(b, 4)
# define TVPARAM_5(a, b) TVPARAM_4(a, b), CONCAT(a, 5) CONCAT(b, 5)
# define TVPARAM_6(a, b) TVPARAM_5(a, b), CONCAT(a, 6) CONCAT(b, 6)
# define TVPARAM_7(a, b) TVPARAM_6(a, b), CONCAT(a, 7) CONCAT(b, 7)
# define TVPARAM_8(a, b) TVPARAM_7(a, b), CONCAT(a, 8) CONCAT(b, 8)
# define TVPARAM_9(a, b) TVPARAM_8(a, b), CONCAT(a, 9) CONCAT(b, 9)

# define COMMA ,

Functor(,,,,)
Functor(COMMA, ENUM_1(typename TPARAM), ENUM_1(TPARAM),
	TVPARAM_1(TPARAM, PARAM), ENUM_1(PARAM))
Functor(COMMA, ENUM_2(typename TPARAM), ENUM_2(TPARAM),
	TVPARAM_2(TPARAM, PARAM), ENUM_2(PARAM))
Functor(COMMA, ENUM_3(typename TPARAM), ENUM_3(TPARAM),
	TVPARAM_3(TPARAM, PARAM), ENUM_3(PARAM))
Functor(COMMA, ENUM_4(typename TPARAM), ENUM_4(TPARAM),
	TVPARAM_4(TPARAM, PARAM), ENUM_4(PARAM))
Functor(COMMA, ENUM_5(typename TPARAM), ENUM_5(TPARAM),
	TVPARAM_5(TPARAM, PARAM), ENUM_5(PARAM))
Functor(COMMA, ENUM_6(typename TPARAM), ENUM_6(TPARAM),
	TVPARAM_6(TPARAM, PARAM), ENUM_6(PARAM))
Functor(COMMA, ENUM_7(typename TPARAM), ENUM_7(TPARAM),
	TVPARAM_7(TPARAM, PARAM), ENUM_7(PARAM))
Functor(COMMA, ENUM_8(typename TPARAM), ENUM_8(TPARAM),
	TVPARAM_8(TPARAM, PARAM), ENUM_8(PARAM))
Functor(COMMA, ENUM_9(typename TPARAM), ENUM_9(TPARAM),
	TVPARAM_9(TPARAM, PARAM), ENUM_9(PARAM))
  
#endif /* !FUNCTOR_HPP_ */
