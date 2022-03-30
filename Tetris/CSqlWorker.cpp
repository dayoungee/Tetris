#include "pch.h"
#include "CSqlWorker.h"

CSqlWorker::sql_value_e CSqlWorker::regist_member(CString id, CString pass)
{
	//mysql_init(&mysql);

	//if (!mysql_real_connect(&mysql, "127.0.0.1", "test", "3306", "member", 3306, NULL, 0))
	//{
	//	return SQL_CONNECT_FAILED;
	//}

	//mysql_query(&mysql, "use member");
	//mysql_query(&mysql, "SELECT * FROM member");
	//res = mysql_store_result(&mysql); // 결과값
	//fields = mysql_num_fields(res); // 필드 갯수
	//int num = mysql_num_rows(res);

	//while (row = mysql_fetch_row(res))//쿼리결과 데이터를 행별로 추출
	//{

	//	if (id == row[0]) {
	//		return SQL_ID_DUPLICATED;
	//	}
	//}

	//CString strSql;
	//strSql.Format(_T("INSERT INTO member(id,pass) VALUES('%s', '%s')"), id, pass);
	////wcstombs_s(&CharactersConverted, astr, strSql.GetLength() + 1, strSql, _TRUNCATE);
	//mysql_query(&mysql, LPSTR(LPCTSTR(strSql)));

	return SQL_RETURN_SUCCESS;
}

CSqlWorker::sql_value_e CSqlWorker::login(CString id, CString pass)
{
	//mysql_init(&mysql);

	//if (!mysql_real_connect(&mysql, "127.0.0.1", "test", "3306", "member", 3306, NULL, 0))
	//{
	//	return SQL_CONNECT_FAILED;
	//}
	//else
	//	mysql_query(&mysql, "set names euckr");

	//mysql_query(&mysql, "use member");
	//mysql_query(&mysql, "SELECT * FROM member");
	//res = mysql_store_result(&mysql); // 결과값
	//res2 = mysql_use_result(&mysql);
	//fields = mysql_num_fields(res); // 필드 갯수
	//int num = mysql_num_rows(res);


	//while (row = mysql_fetch_row(res))//쿼리결과 데이터를 행별로 추출
	//{
	//	if ((id == row[0] && pass == row[1]) || (id == "뉴크" && pass == "123")) {
			return SQL_RETURN_SUCCESS;
	//	}
	//}

	//return SQL_LOGIN_FAILED;
}
