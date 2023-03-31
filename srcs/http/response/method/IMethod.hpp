#ifndef IMETHOD_HPP
#define IMETHOD_HPP

class IMethod {
protected:
	bool _hasBody;

public:
	IMethod(void);
	IMethod(const IMethod& other);
	IMethod& operator=(const IMethod& other);
	virtual ~IMethod(void);
	virtual void doMethod(void) = 0;
	virtual void setHasBody(bool hasbody) = 0;
	virtual bool getHasBody(void) = 0;
};

#endif