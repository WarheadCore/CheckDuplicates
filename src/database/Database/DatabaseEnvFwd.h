/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DatabaseEnvFwd_h__
#define DatabaseEnvFwd_h__

#include "Define.h"
#include <future>
#include <memory>

template<typename T>
class AsyncCallbackProcessor;

enum ConnectionFlags : uint8
{
    CONNECTION_ASYNC    = 0x1,
    CONNECTION_SYNCH    = 0x2,
    CONNECTION_BOTH     = CONNECTION_ASYNC | CONNECTION_SYNCH
};

enum class DatabaseType : uint8
{
    None,
    Auth        = 1,
    Character   = 2,
    World       = 4,
    Hotfix      = 8,
    All   = Auth | Character | World | Hotfix
};

class Field;
class MySQLConnection;
class MySQLPreparedStatement;
class SQLQueryHolderBase;

struct MySQLConnectionInfo;
struct QueryResultFieldMetadata;

class ResultSet;
using QueryResult = std::shared_ptr<ResultSet>;
using QueryResultFuture = std::future<QueryResult>;
using QueryResultPromise = std::promise<QueryResult>;

class PreparedResultSet;
using PreparedQueryResult = std::shared_ptr<PreparedResultSet>;
using PreparedQueryResultFuture = std::future<PreparedQueryResult>;
using PreparedQueryResultPromise = std::promise<PreparedQueryResult>;

class PreparedStatementBase;
using PreparedStatement = std::shared_ptr<PreparedStatementBase>;

class Transaction;
using TransactionFuture = std::future<bool>;
using TransactionPromise = std::promise<bool>;
using SQLTransaction = std::shared_ptr<Transaction>;

class SQLQueryHolderBase;
using QueryResultHolderFuture = std::future<void>;
using QueryResultHolderPromise = std::promise<void>;
using SQLQueryHolder = std::shared_ptr<SQLQueryHolderBase>;

class QueryCallback;
class SQLQueryHolderCallback;
class TransactionCallback;
using QueryCallbackProcessor = AsyncCallbackProcessor<QueryCallback>;
using TransactionCallbackProcessor = AsyncCallbackProcessor<TransactionCallback>;
using QueryHolderCallbackProcessor = AsyncCallbackProcessor<SQLQueryHolderCallback>;

// mysql
struct MySQLHandle;
struct MySQLResult;
struct MySQLField;
struct MySQLBind;
struct MySQLStmt;

#endif // DatabaseEnvFwd_h__
