#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>

void logSDLError(const std::string& msg);

#ifdef DEBUG
void logDebug(const std::string& msg);
#else
#define logDebug(x)
#endif // DEBUG

#endif // LOGGING_H_
