# std::conditional

## VS 2015 정의

```cpp
	// TEMPLATE CLASS conditional
template<bool _Test,
	class _Ty1,
	class _Ty2>
	struct conditional
	{	// type is _Ty2 for assumed !_Test
	typedef _Ty2 type;
	};

template<class _Ty1,
	class _Ty2>
	struct conditional<true, _Ty1, _Ty2>
	{	// type is _Ty1 for _Test
	typedef _Ty1 type;
	};
```

템플릿에 bool _Test로 타입이 아닌 매개변수가 들어가 있다.

이것을 Non-Type template Parameter이라 한다.

위 코드를 보면 Non-Type template Parameter에 대해 값으로 struct conditional<true, _Ty1, _Ty2>로 부분 특수화가 되어 있다.

따라서 _Test의 값으로 true가 전달될 경우 부분 특수화에 의해 struct conditional<true, _Ty1, _Ty2>이 선택되고, type은 _Ty1 타입으로 지정된다.

_Test가 false일 경우 기본 템플릿을 선택하여 type이 _Ty2 타입으로 지정된다. 

## 추가 정보

VS 2017에서는 using 키워드를 이용한다.

```cpp
  using type = FalseType;
```

현재 VS 2015를 사용 중이기 때문에 using에 대해서는 다음에 알아보자.


