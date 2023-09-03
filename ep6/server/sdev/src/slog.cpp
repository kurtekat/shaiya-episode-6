#include <shaiya/include/SLog.h>

using namespace shaiya;

constexpr Address LogFunctionAddr = 0x4ED0E0;

typedef void(LogFunction)(FILE*, const char*);

LogFunction s_log = (LogFunction) LogFunctionAddr;

void SLog::log(const std::string& text)
{
    s_log(get_log_file(), text.c_str());
}

FILE* SLog::get_log_file()
{
    return (FILE*) (*g_GameLog + 224);
}
