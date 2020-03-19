using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;

namespace ConsoleApp1
{
    class Data1
    {
        public string connString = "Data Source=DESKTOP-L6H201M\\SQLEXPRESS;Database=wer;Trusted_Connection=True;MultipleActiveResultSets=true";
        //Server=(localdb)\\mssqllocaldb;Database=aspnet-WebApplication2-0AC27548-CED7-4363-B6A6-F9C46D5F4CA3;Trusted_Connection=True;MultipleActiveResultSets=true
        //创建连接对象的变量  
        public SqlConnection conn;
        // 执行对数据表中数据的增加、删除、修改操作  
        public int NonQuery(string sql)
        {
            conn = new SqlConnection(connString);
            int a = -1;
            try
            {
                conn.Open();  //打开数据库  
                SqlCommand cmd = new SqlCommand(sql, conn);
                a = cmd.ExecuteNonQuery();
            }
            catch
            {

            }
            finally
            {
                if (conn.State == ConnectionState.Open)
                {
                    conn.Close();    //关闭数据库  
                }
            }
            return a;

        }
        // 执行对数据表中数据的查询操作  
        public DataSet Query(string sql)
        {
            conn = new SqlConnection(connString);
            DataSet ds = new DataSet();
            try
            {
                conn.Open();      //打开数据库  
                SqlDataAdapter adp = new SqlDataAdapter(sql, conn);
                adp.Fill(ds);
            }
            catch
            {

            }
            finally
            {
                if (conn.State == ConnectionState.Open)
                    conn.Close();      //关闭数据库  
            }
            return ds;
        }




        public string DataSetToString(DataSet ds)

        {

            //!@&为表的连接字符串，#$%为行的连接字符串，^&*为字段的连接字符串

            //为了保证连接字符串不在DataSet数据中存在，连接字符串尽量复杂！

            StringBuilder strData = new StringBuilder();

            foreach (DataTable dt in ds.Tables)//遍历ds的表

            {

                if (strData.Length > 0)//从第一个表开始，加上表的连接字符串

                    strData.Append(" ");

                for (int m = 0; m < dt.Rows.Count; m++)//遍历dt的行

                {

                    DataRow row = dt.Rows[m];

                    for (int n = 0; n < dt.Columns.Count; n++)//遍历row的列

                    {

                        if (m > 0)//从第二行数据开始，加上行的连接字符串

                        {

                            strData.Append(" ");

                        }

                        if (n > 0)//从第二个字段开始，加上字段的连接字符串

                        {

                            strData.Append(" ");

                        }

                        strData.Append(Convert.ToString(row[n]));//取数据

                    }

                }

            }

            return strData.ToString();

        }
    }
}
