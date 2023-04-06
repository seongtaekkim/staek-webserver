#ifndef RELEASERESOURCE_HPP
#define RELEASERESOURCE_HPP

class ReleaseResource {
private:
	ReleaseResource(void);
	ReleaseResource(const ReleaseResource* other);
	ReleaseResource& operator=(const ReleaseResource& other);
public:
	~ReleaseResource(void);
public:
	template<typename T>
	static void pointer(T const *&ptr) {
		if (ptr)
			delete ptr;
		ptr = NULL;
	}
};

#endif