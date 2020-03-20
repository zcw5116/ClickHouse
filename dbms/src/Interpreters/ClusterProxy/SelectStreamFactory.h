#pragma once

#include <Core/QueryProcessingStage.h>
#include <Interpreters/ClusterProxy/IStreamFactory.h>
#include <Storages/IStorage_fwd.h>

namespace DB
{

namespace ClusterProxy
{

class SelectStreamFactory final : public IStreamFactory
{
public:
    /// Database in a query.
    SelectStreamFactory(
        Block header_,
        QueryProcessingStage::Enum processed_stage_,
        StorageID main_table_,
        Scalars scalars_,
        bool has_virtual_shard_num_column_,
        Tables external_tables);

    /// TableFunction in a query.
    SelectStreamFactory(
        Block header_,
        QueryProcessingStage::Enum processed_stage_,
        ASTPtr table_func_ptr_,
        Scalars scalars_,
        bool has_virtual_shard_num_column_,
        Tables external_tables_);

    void createForShard(
        const Cluster::ShardInfo & shard_info,
        const String & query, const ASTPtr & query_ast,
        const Context & context, const ThrottlerPtr & throttler,
        const SelectQueryInfo & query_info,
        Pipes & res) override;

private:
    const Block header;
    QueryProcessingStage::Enum processed_stage;
    StorageID main_table = StorageID::createEmpty();
    ASTPtr table_func_ptr;
    Scalars scalars;
    bool has_virtual_shard_num_column = false;
    Tables external_tables;
};

}

}
