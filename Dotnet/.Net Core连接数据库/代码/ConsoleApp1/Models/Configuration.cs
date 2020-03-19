using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Threading.Tasks;
using System.Data.Entity.Migrations;

namespace ConsoleApp1.Models
{
    internal sealed class Configuration : DbMigrationsConfiguration<ApplicationDbContext>
    {
        public Configuration()
        {
            AutomaticMigrationsEnabled = true;
            ContextKey = "MySQL.ApplicationDbContext";

        }

        protected override void Seed(ApplicationDbContext context)
        {

        }
    }

    internal sealed class MySQLConfiguration : DbMigrationsConfiguration<MySQLDbContext>
    {
        public MySQLConfiguration()
        {
            AutomaticMigrationsEnabled = true;
            ContextKey = "MySQL.MySQLDbContext";
            // 注册mysql代码生成器 
           // SetSqlGenerator("MySql.Data.MySqlClient", new MySql.Data.Entity.MySqlMigrationSqlGenerator());
        }

        protected override void Seed(MySQLDbContext context)
        {

        }
    }
}
