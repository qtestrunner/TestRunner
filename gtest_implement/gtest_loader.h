#ifndef GTEST_LOADER_H
#define GTEST_LOADER_H

#include <interfaces/itestloader.h>
#include <utils/utils.h>
#include <utils/log.h>

class GTest_Loader: public ITestLoader{
public:
    ~GTest_Loader();

    Result loadFile(const QString &file_name, IFilePtr &file, const QStringList &environment);
};

#endif // GTEST_LOADER_H
