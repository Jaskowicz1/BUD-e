/************************************************************************************
 *
 * database.h
 *
 * Copyright 1993,2001,2023 Craig Edwards <brain@ssod.org>
 *
 * Imported from Seven Spells of Destruction.
 *
 ************************************************************************************/
#pragma once
#include <vector>
#include <map>
#include <string>
#include <variant>
#include <dpp/dpp.h>

/**
 * @brief Database abstraction layer
 * Abstracts mysql C connector, supporting prepared statements and caching.
 */
namespace db {

/**
 * @brief Definition of a row in a result set
 */
using row = std::map<std::string, std::string>;

/**
 * @brief Definition of a result set, a vector of maps
 */
using resultset = std::vector<row>;

/**
 * @brief Possible parameter types for SQL parameters
 */
using parameter_type = std::variant<float, std::string, uint64_t, int64_t, bool, int32_t, uint32_t, double>;

/**
 * @brief A list of database query parameters.
 * These will be translated into prepared statement arguments.
 */
using paramlist = std::vector<parameter_type>;

/**
 * @brief Initialise database connection
 *
 * @param bot creating D++ cluster
 */
void init (dpp::cluster& bot);

/**
 * @brief Connect to database and set options
 *
 * @param host Database hostname
 * @param user Database username
 * @param pass Database password
 * @param db Database schema name
 * @param port Database port number
 * @param socket unix socket path
 * @return True if the database connection succeeded
 *
 * @note Unix socket and port number are mutually exclusive. If you set socket to a non-empty string,
 * you should set port to 0 and host to `localhost`. This is a special value in the mysql client and
 * causes a unix socket connection to occur. If you do not want to use unix sockets, keep the value
 * as an empty string.
 */
bool connect(const std::string &host, const std::string &user, const std::string &pass, const std::string &db, int port = 3306, const std::string& socket = "");

/**
 * @brief Disconnect from database and free query cache
 *
 * @return true on successful disconnection
 */
bool close();

/**
 * @brief Run a mysql query, with automatic escaping of parameters to prevent SQL injection.
 *
 * @param format Format string, where each parameter should be indicated by a ? symbol
 * @param parameters Parameters to prepare into the query in place of the ?'s
 *
 * The parameters given should be a vector of strings. You can instantiate this using "{}".
 * The queries are cached as prepared statements and therefore do not need quote symbols
 * to be placed around parameters in the query. These will be automatically added if required.
 *
 * For example:
 *
 * ```cpp
 * 	db::query("UPDATE foo SET bar = ? WHERE id = ?", { "baz", 3 });
 * ```
 *
 * Returns a resultset of the results as rows. Avoid returning massive resultsets if you can.
 */
resultset query(const std::string &format, const paramlist &parameters = {});

/**
 * @brief Run a mysql query, with automatic escaping of parameters to prevent SQL injection.
 *
 * @param format Format string, where each parameter should be indicated by a ? symbol
 * @param parameters Parameters to prepare into the query in place of the ?'s
 * @param lifetime How long to cache this query's resultset in memory for
 *
 * @note If the query is already cached in memory, the cached resultset will be returned instead
 * of querying the database.
 *
 * The parameters given should be a vector of strings. You can instantiate this using "{}".
 * The queries are cached as prepared statements and therefore do not need quote symbols
 * to be placed around parameters in the query. These will be automatically added if required.
 *
 * For example:
 *
 * ```cpp
 * 	db::query("UPDATE foo SET bar = ? WHERE id = ?", { "baz", 3 });
 * ```
 *
 * Returns a resultset of the results as rows. Avoid returning massive resultsets if you can.
 */
resultset query(const std::string &format, const paramlist &parameters, double lifetime);

/**
 * @brief Returns number of affected rows from an UPDATE, INSERT, DELETE
 *
 * @note This value is by any db::query() call. Take a copy!
 * @return size_t Number of affected rows
 */
size_t affected_rows();

/**
 * @brief Returns the last error string.
 *
 * @note This value is by any db::query() call. Take a copy!
 * @return const std::string& Error mesage
 */
const std::string& error();

/**
 * @brief Returns the size of the query cache
 *
 * Prepared statement handles are stored in a std::map along with their metadata, so that
 * they don't have to be re-prepared if they are executed repeatedly. This is a diagnostic
 * and informational function which returns the size of that map.
 *
 * @return size_t Cache size
 */
size_t cache_size();

/**
 * @brief Returns total number of queries executed since connection was established
 *
 * @return size_t Query counter
 */
size_t query_count();

/**
 * @brief Start a transaction
 *
 * @return true if transaction was started
 */
bool transaction();

/**
 * @brief Commit a previously started transaction
 *
 * @return true if transaction was committed
 */
bool commit();

/**
 * @brief Roll back a previously started transaction
 *
 * @return true if transaction was rolled back
 */
bool rollback();

};
