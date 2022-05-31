#include "Movie.h"

template <typename Type>
class Comparator {

public:
	virtual bool operator()(const Type &e1, const Type &e2) = 0;

};

template <typename Type>
class CompareByTitle : public Comparator<Type>
{
public:
	bool operator()(const Type &e1, const Type &e2) override;
};

template <typename Type>
bool CompareByTitle<Type>::operator()(const Type &e1, const Type &e2) 
{
	return e1.getTitle() < e2.getTitle();
}

template <typename Type>
class CompareByYear :public Comparator<Type>
{
public:
	bool operator()(const Type &e1, const Type &e2);
};

template <typename Type>
bool CompareByYear<Type>::operator()(const Type &e1, const Type &e2)
{
	return e1.getYearOfRelease() < e2.getYearOfRelease();
}