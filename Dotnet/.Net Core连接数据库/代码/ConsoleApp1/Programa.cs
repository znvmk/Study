using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;
using Microsoft.EntityFrameworkCore;
using System.Data.Entity;
using ConsoleApp1.Data;
using ConsoleApp1.Models;


namespace ConsoleApp1
{
    class Programa
    {



        //static void Main(string[] args)
        //{
            /*
            Data1 data1 = new Data1();
            //Data1 data1;
            string sql1 = "select *from Movie";
            //string res;
            DataSet ds = new DataSet();
            ds = data1.Query(sql1);
            string d = data1.DataSetToString(ds);


            Console.WriteLine(d);
            */




            /*
            DbEntity db = new DbEntity();
            //创建对象实体，注意，这里需要对所有属性进行赋值（除了自动增长主键外），如果不赋值，则会数据库中会被设置为NULL（注意是否可空）
            var user = new User
            {
                Name = "bomo",
                Age = 21,
                Gender = "male"
            };
            db.User.Add(user);
            db.SaveChanges();
            */
            /*
            MovieData movie=new MovieData();
            var a = movie.GetAll();
            string b = a.ToString();
            Console.WriteLine(b);
            */

           /*
           using (var db = new MovieContext())
           {
               db.Movie.Add(new Movie { id = 3,area = "adonet" });
               var count = db.SaveChanges();
               Console.WriteLine("{0} records saved to database", count);

               Console.WriteLine();
               Console.WriteLine("All blogs in database:");
               foreach (var are in db.Movie)
               {
                   Console.WriteLine(" - {0}",are.id);
               }
           }
           //*/







            //Console.WriteLine("dfasdfasdfd");
           // Console.ReadLine();


      //  }
    }
}
