#ifndef Factoryhub.h

#include <map>
#include <memory>
#include "Object.h"

class ObjectHub;
class Factoryhub {
public:
	Factoryhub();
	~Factoryhub();
	
	Factoryhub(const Factoryhub& src) noexcept;
	Factoryhub(Factoryhub& src) noexcept;

	Factoryhub& operator=(const Factoryhub& src) noexcept;
	Factoryhub& operator=(Factoryhub& src) noexcept;
	std::map<Object::Type, std::shared_ptr<ObjectHub>> library;
};






#endif // !Factoryhub.h
