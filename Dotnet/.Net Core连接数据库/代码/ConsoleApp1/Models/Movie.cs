using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.EntityFrameworkCore;

namespace ConsoleApp1.Models
{
    public class Movie
    {
        public int ID { get; set; }
        public int num { get; set; }
        public int price { get; set; }
    }

    public class MovieContext:DbContext
    {
        //public MovieContext(DbContextOptions<MovieContext> options)
        //    : base(options)
       //// {
       // }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            //配置mariadb连接字符串
            // optionsBuilder.UseMySql("Server=localhost;Port=3306;Database=BloggingDB; User=root;Password=;");
            optionsBuilder.UseSqlServer("Server=DESKTOP-L6H201M\\SQLEXPRESS;Database=wer;Trusted_Connection=True;MultipleActiveResultSets=true");
        }

        public DbSet<ConsoleApp1.Models.Movie> Movie { get; set; }
    }
}
