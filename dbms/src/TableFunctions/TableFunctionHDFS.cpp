#include <Common/config.h>
#include "registerTableFunctions.h"

#if USE_HDFS
#include <Storages/StorageHDFS.h>
#include <Storages/ColumnsDescription.h>
#include <Access/AccessType.h>
#include <TableFunctions/TableFunctionFactory.h>
#include <TableFunctions/TableFunctionHDFS.h>

namespace DB
{
StoragePtr TableFunctionHDFS::getStorage(
    const String & source, const String & format, const ColumnsDescription & columns, Context & global_context, const std::string & table_name, const String & compression_method) const
{
    return StorageHDFS::create(source,
        StorageID(getDatabaseName(), table_name),
        format,
        columns,
        ConstraintsDescription{},
        global_context,
        compression_method);
}

AccessType TableFunctionHDFS::getRequiredAccessType() const
{
    return AccessType::hdfs;
}

#if USE_HDFS
void registerTableFunctionHDFS(TableFunctionFactory & factory)
{
    factory.registerFunction<TableFunctionHDFS>();
}
#endif
}
#endif
