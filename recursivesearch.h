#ifndef RECURSIVESEARCH_H
#define RECURSIVESEARCH_H

#include <functional>
#include <io.h>

enum enumflags {
    ENUM_FILE = 1,
    ENUM_DIR,
    ENUM_BOTH
};

bool enumsubfiles(

    const std::wstring &dir_with_back_slant,
    const std::wstring &filename,
    unsigned int maxdepth,                 //0 means not searching subdirectories, 1 means maximum depth of subdirectories is 1,
                                           //    pass -1 to search all the subdirectories.
    enumflags flags,                       //search files, directories, or both.
    std::function<bool(const std::wstring &dir_with_back_slant, _wfinddata_t &attrib)> callback
);

#endif // RECURSIVESEARCH_H
