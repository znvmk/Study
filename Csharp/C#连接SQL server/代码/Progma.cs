using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;


namespace ConsoleApp1
{
    class Program
    {

       

        static void Main(string[] args)
        {
            Data1 data1 = new Data1();
            //Data1 data1;
            string sql1 = "select *from Table_1";
            //string res;
            DataSet ds = new DataSet();
            ds =data1.Query(sql1);
            string d = data1.DataSetToString(ds);
            

            Console.WriteLine(d);
            Console.ReadLine();
            

        }
    }
}
