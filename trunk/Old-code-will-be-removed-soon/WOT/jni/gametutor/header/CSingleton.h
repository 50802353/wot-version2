#ifndef __CSingleton_h__
#define __CSingleton_h__

template <class Singleton>
class CSingleton
{
public:
	static Singleton* GetInstance()
	{
		if (!s_pSingletonInstance)
		{
			s_pSingletonInstance = new Singleton();
		}
		return s_pSingletonInstance;
	}
	~CSingleton()
	{
		s_pSingletonInstance = 0;
	}
protected:
	static Singleton* s_pSingletonInstance;
};

template<class Singleton> Singleton* CSingleton<Singleton>::s_pSingletonInstance = 0;


template <class AbsSingleton>
class CAbsSingleton
{
public:
	static AbsSingleton* GetInstance()
	{
		return s_pSingletonInstance;
	}
protected:
	static AbsSingleton* s_pSingletonInstance;
	void SetInstance(AbsSingleton* val) 
	{
		if (!s_pSingletonInstance) 
		{
			s_pSingletonInstance = val;
		}
		else
		{
			Log("[WARNING] [CAbsSingleton] Singleton instance has been set before.");
		}
	}
};

template<typename AbsSingleton> AbsSingleton* CAbsSingleton<AbsSingleton>::s_pSingletonInstance = 0;


#endif