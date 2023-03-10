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

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include "DatabaseEnvFwd.h"
#include "Field.h"
#include <unordered_map>

template<typename T>
struct ResultIterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;

    explicit ResultIterator(pointer ptr) : _ptr(ptr) { }

    reference operator*() const { return *_ptr; }
    pointer operator->() { return _ptr; }
    ResultIterator& operator++() { if (!_ptr->NextRow()) _ptr = nullptr; return *this; }

    bool operator!=(const ResultIterator& right) { return _ptr != right._ptr; }

private:
    pointer _ptr;
};

class WH_DATABASE_API ResultSet
{
public:
    ResultSet(MySQLResult* result, MySQLField* fields, uint64 rowCount, uint32 fieldCount);
    ~ResultSet();

    bool NextRow();
    [[nodiscard]] uint64 GetRowCount() const { return _rowCount; }
    [[nodiscard]] uint32 GetFieldCount() const { return _fieldCount; }
    [[nodiscard]] std::string GetFieldName(uint32 index) const;

    [[nodiscard]] auto* Fetch() const { return _currRow.get(); }
    Field const& operator[](std::size_t index) const;

    template<typename... Ts>
    inline std::tuple<Ts...> FetchTuple()
    {
        AssertRows(sizeof...(Ts));

        std::tuple<Ts...> theTuple{};

        std::apply([this](Ts&... args)
        {
            uint8 index{};
            ((args = _currRow[index].Get<Ts>(), index++), ...);
        }, theTuple);

        return theTuple;
    }

    auto begin()      { return ResultIterator<ResultSet>(this); }
    static auto end() { return ResultIterator<ResultSet>(nullptr); }

protected:
    std::vector<QueryResultFieldMetadata> _fieldMetadata;
    uint64 _rowCount;
    std::unique_ptr<Field[]> _currRow;
    uint32 _fieldCount;

private:
    void CleanUp();
    void AssertRows(std::size_t sizeRows) const;

    MySQLResult* _result;
    MySQLField* _fields;

    ResultSet(ResultSet const& right) = delete;
    ResultSet& operator=(ResultSet const& right) = delete;
};

class WH_DATABASE_API PreparedResultSet
{
public:
    PreparedResultSet(MySQLStmt* stmt, MySQLResult* result, uint64 rowCount, uint32 fieldCount);
    ~PreparedResultSet();

    bool NextRow();
    [[nodiscard]] uint64 GetRowCount() const { return _rowCount; }
    [[nodiscard]] uint32 GetFieldCount() const { return _fieldCount; }

    [[nodiscard]] Field* Fetch() const;
    Field const& operator[](std::size_t index) const;

    template<typename... Ts>
    inline std::tuple<Ts...> FetchTuple()
    {
        AssertRows(sizeof...(Ts));

        std::tuple<Ts...> theTuple = {};

        std::apply([this](Ts&... args)
        {
            uint8 index{ 0 };
            ((args = _rows[uint32(_rowPosition) * _fieldCount + index].Get<Ts>(), index++), ...);
        }, theTuple);

        return theTuple;
    }

    auto begin()        { return ResultIterator<PreparedResultSet>(this); }
    static auto end()   { return ResultIterator<PreparedResultSet>(nullptr); }

protected:
    std::vector<QueryResultFieldMetadata> _fieldMetadata;
    std::vector<Field> _rows;
    uint64 _rowCount;
    uint64 _rowPosition{};
    uint32 _fieldCount;

private:
    MySQLBind* _rBind{ nullptr };
    MySQLStmt* _stmt;
    MySQLResult* _metadataResult;    ///< Field metadata, returned by mysql_stmt_result_metadata

    void CleanUp();
    bool _NextRow();

    void AssertRows(std::size_t sizeRows) const;

    PreparedResultSet(PreparedResultSet const& right) = delete;
    PreparedResultSet& operator=(PreparedResultSet const& right) = delete;
};

#endif
