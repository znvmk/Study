using WebApplication1.Model;
using System.Data;
using System.Data.Sql;


static void Main(string[] args)
{
    using (var db = new BloggingContext())
    {
        db.Blog.Add(new Blog { BlogId=1,Url = "http://blogs.msdn.com/adonet" });
        var count = db.SaveChanges();
        Console.WriteLine("{0} records saved to database", count);

        Console.WriteLine();
        Console.WriteLine("All blogs in database:");
        foreach (var blog in db.Blogs)
        {
            Console.WriteLine(" - {0}", blog.Url);
        }
    }
    Console.ReadKey();
}