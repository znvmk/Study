using ConsoleApp2.Model;
using System.Data;
using System.Data.Sql;
using System;

namespace ConsoleApp2
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
            using (var db = new BloggingContext())
            {
                db.Blog.Add(new Blog { BlogId = 5, Url = "http://blogs.msdn.com/adonet" });
                var count = db.SaveChanges();
                Console.WriteLine("{0} records saved to database", count);

                Console.WriteLine();
                Console.WriteLine("All blogs in database:");
                foreach (var blog in db.Blog)
                {
                    Console.WriteLine(" - {0}", blog.Url);
                }
            }
            //*/
            



            /*
            using (var db = new aresContext())
            {
                db.are.Add(new are { id = 3,area = "adonet" });
                var count = db.SaveChanges();
                Console.WriteLine("{0} records saved to database", count);

                Console.WriteLine();
                Console.WriteLine("All blogs in database:");
                foreach (var are in db.are)
                {
                    Console.WriteLine(" - {0}",are.id);
                }
            }
            //*/


            //*
            using (var db = new MansContext())
            {
                db.Man.Add(new Man { name = "adonet" });
                var count = db.SaveChanges();
                Console.WriteLine("{0} records saved to database", count);

                Console.WriteLine();
                Console.WriteLine("All blogs in database:");
                foreach (var Man in db.Man)
                {
                    Console.WriteLine(" - {0} - {1}", Man.uid, Man.name);
                   // Console.WriteLine(" - {0}", Man.name);
                }
            }
            //*/








            Console.ReadKey();
        }
    }
}
