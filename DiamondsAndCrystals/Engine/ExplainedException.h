#pragma once
#include <exception>
#include <string>

class ExplainedException : std::exception
{
public:
	ExplainedException(const char* whatHappened) : m_message(whatHappened)	{	}
	ExplainedException(const char* whatHappened, const char* details) { m_message = whatHappened; m_message += details;	}
	virtual ~ExplainedException() {}
	virtual const char* what() const { return m_message.c_str(); }
private:
	std::string m_message;
};

