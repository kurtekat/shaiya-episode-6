# Documentation

This library is for the **login** service. It includes two fixes for well-known vulnerabilities.

## Authentication

The library parameterizes the login query and executes a prepared statement. You can use SQL Server Profiler to see the result.

```sql
declare @p1 int
set @p1=1
exec sp_prepexec @p1 output,N'@P1 text,@P2 text,@P3 bigint,@P4 text',N'EXEC usp_Try_GameLogin_Taiwan @P1,@P2,@P3,@P4','a','a',6998436556411240449,'127.0.0.1'
select @p1
```
