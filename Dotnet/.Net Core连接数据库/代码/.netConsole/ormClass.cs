using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.IO;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
//using System.Data.Entity;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.SqlServer;
using Microsoft.EntityFrameworkCore.Tools;

namespace ConsoleApp2
{
    class Class1
    {
    }
    [Table("Blog")]
    public class Blog
    {
        //申明主键：如果字段名称为“ID”"Id"默认为主键，如果为其他，则需明确申明主键  [Key]
        [Key]
        public int BlogId { get; set; }
        public string Url { get; set; }
    }
    public class BloggingContext :DbContext
    {
        public DbSet<Blog> Blog { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            //配置mariadb连接字符串
            // optionsBuilder.UseMySql("Server=localhost;Port=3306;Database=BloggingDB; User=root;Password=;");
            optionsBuilder.UseSqlServer("Server=DESKTOP-L6H201M\\SQLEXPRESS;Database=wer;Trusted_Connection=True;MultipleActiveResultSets=true");
        }
    }
}
