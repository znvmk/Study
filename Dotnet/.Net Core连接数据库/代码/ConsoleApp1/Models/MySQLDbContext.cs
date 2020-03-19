using System;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Data.Common;
//using MySql.Data.Entity;


namespace ConsoleApp1.Models
{
    //[DbConfigurationType(typeof(MySqlEFConfiguration))]
    public class MySQLDbContext : DbContext
    {
        public MySQLDbContext() : base("Server=localhost;Database=test;uid=root;pwd=123456;")
        { }
        public DbSet<User> Users { get; set; }
    }
}
