#pragma once
class CSqlWorker
{
public:
	CSqlWorker() {}
	~CSqlWorker() {}

	typedef enum SQLRETURN
	{
		SQL_RETURN_SUCCESS,
		SQL_CONNECT_FAILED,		// 연결 실패
		SQL_ID_DUPLICATED,
		SQL_LOGIN_FAILED,

	} sql_value_e;

	sql_value_e regist_member(CString id, CString pass);
	sql_value_e login(CString id, CString pass);

private:
	//MYSQL mysql;
	//MYSQL_RES* res;
	//MYSQL_ROW row;
	//MYSQL_RES* res2;
	//int fields;
};

